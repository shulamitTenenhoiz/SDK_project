#pragma once
#include <chrono>
#include <thread>
#include <functional>
#include <string>
#include "DeviceManager.h"
#include "ErrorPolicy.h"  
#include "LogUtils.h"   

// ------------------------------------------------------------
// ������ ������ ������ ������
// ------------------------------------------------------------
struct RetryPolicy {
    int maxImmediateRetries = 3;
    int maxBackoffRetries = 5;
    int maxReLoginRetries = 3;
    int maxReOpenRetries = 3;
    int maxReInitRetries = 2;

    int backoffSeconds = 5;

    // ��� ���� ��� �������� ������
    int permanentRetryWaitMinutes = 3;

    int maxPermanentCycles = 10;          // ������� ������� �� ��� ������
    int maxInitRetryCycles = 5;           // ��� ����� ���� �-main ����� Init ����

    int permanentRetryTotalMinutes = 60;  // ����� ��� ���� ������ (����)
};

// ������ ����� ������ � ������ �� ��� ���������� (�� ? ���)
static inline void logErr(NET_SDK_ERROR err, const char* ctx) {
    logError(std::string(ctx) + " failed", err);
}
static inline void logInf(const std::string& s) {
    logInfo(s);
}

// ------------------------------------------------------------
// �����������: ������ ������ (connect/open), ����� �����,
// ������ ������� ��� �������� ������ �"� classifyError().
// ActionFn:  signature like  NET_SDK_ERROR action(DeviceManager&)
// ------------------------------------------------------------
template<typename ActionFn>
NET_SDK_ERROR runWithRecovery(
    DeviceManager& dev,
    const RetryPolicy& policy,
    ActionFn action)
{
    int imm = 0, bof = 0, rel = 0, reo = 0, rei = 0;

    while (true) {
        // -------- ensureReady ���� ������: �� ������ action �� �� ������ --------
        if (NET_SDK_ERROR prep = [&]() -> NET_SDK_ERROR {
            if (!dev.isConnected()) {
                if (auto e = dev.connect(); e != NET_SDK_SUCCESS) return e;
                logInf("Connected successfully.");
            }
            if (!dev.isResourceOpened()) {
                if (auto e = dev.openResource(); e != NET_SDK_SUCCESS) return e;
                logInf("Resource opened successfully.");
            }
            return NET_SDK_SUCCESS;
            }(); prep != NET_SDK_SUCCESS)
        {
            logErr(prep, "Initial ensureReady");
            RetryDecision dec = classifyError(prep);
            switch (dec) {
            case RetryDecision::RetryImmediate:
                if (imm++ < policy.maxImmediateRetries) { logInf("RetryImmediate�"); continue; }
                [[fallthrough]];

            case RetryDecision::RetryBackoff:
                if (bof++ < policy.maxBackoffRetries) {
                    logInf("RetryBackoff� sleeping " + std::to_string(policy.backoffSeconds) + "s");
                    std::this_thread::sleep_for(std::chrono::seconds(policy.backoffSeconds));
                    continue;
                }
                [[fallthrough]];

            case RetryDecision::ReLogin:
                if (rel++ < policy.maxReLoginRetries) {
                    logErr(prep, "ensureReady -> ReLogin");
                    dev.disconnect();
                    continue; // ����� ���� ������ ����� ������/����� ���
                }
                else {
                    // === ��� ������ � ����� �� ������ ===
                    logInf("Entering permanent retry mode�");
                    auto start = std::chrono::steady_clock::now();
                    int cycles = 0;
                    while (cycles++ < policy.maxPermanentCycles) {
                        auto elapsedMin = std::chrono::duration_cast<std::chrono::minutes>(
                            std::chrono::steady_clock::now() - start).count();
                        if (elapsedMin >= policy.permanentRetryTotalMinutes) {
                            logError("Permanent retry budget exhausted");
                            return NET_SDK_NETWORK_FAIL_CONNECT; // �� ��� ������� ������ ��
                        }

                        logInf("Permanent retry: waiting "
                            + std::to_string(policy.permanentRetryWaitMinutes) + " minutes�");
                        std::this_thread::sleep_for(std::chrono::minutes(policy.permanentRetryWaitMinutes));

                        dev.disconnect();
                        if (dev.connect() == NET_SDK_SUCCESS &&
                            dev.openResource() == NET_SDK_SUCCESS) {
                            logInf("Reconnected & resource reopened. Resuming.");
                            break; // ������ � ����� ��action
                        }
                    }
                    if (cycles > policy.maxPermanentCycles) {
                        logError("Permanent retry cycles exceeded");
                        return NET_SDK_NETWORK_FAIL_CONNECT;
                    }
                    // �� ����� ������� ���� break, ������� ���� ��action
                }
                break;

            case RetryDecision::ReInitSdk:
                if (rei++ < policy.maxReInitRetries) {
                    logErr(prep, "ensureReady -> ReInitSdk");
                    dev.disconnect();
                    dev.cleanup();
                    return NET_SDK_NOINIT; // main ���� DeviceManager ���
                }
                return prep;

            case RetryDecision::Fatal:
            case RetryDecision::Success:
            default:
                return prep;
            }
        }

        // ------------------- ������ �� ������ �� ������ ���� -------------------
        NET_SDK_ERROR rc = action(dev);
        if (rc == NET_SDK_SUCCESS) return NET_SDK_SUCCESS;

        RetryDecision dec = classifyError(rc);
        switch (dec) {
        case RetryDecision::RetryImmediate:
            if (imm++ < policy.maxImmediateRetries) {
                logErr(rc, "Action");
                logInf("RetryImmediate�");
                continue;
            }
            [[fallthrough]];

        case RetryDecision::RetryBackoff:
            if (bof++ < policy.maxBackoffRetries) {
                logErr(rc, "Action");
                logInf("RetryBackoff� sleeping " + std::to_string(policy.backoffSeconds) + "s");
                std::this_thread::sleep_for(std::chrono::seconds(policy.backoffSeconds));
                continue;
            }
            [[fallthrough]];

        case RetryDecision::ReLogin:
            if (rel++ < policy.maxReLoginRetries) {
                logErr(rc, "Action -> ReLogin");
                dev.disconnect();
                continue; // ����� ���� ������, ensureReady ���� connect/open ����
            }
            else {
                // === ��� ������ ���� �-Action � �� ������ ===
                logInf("Entering permanent retry mode (action)�");
                auto start = std::chrono::steady_clock::now();
                int cycles = 0;
                while (cycles++ < policy.maxPermanentCycles) {
                    auto elapsedMin = std::chrono::duration_cast<std::chrono::minutes>(
                        std::chrono::steady_clock::now() - start).count();
                    if (elapsedMin >= policy.permanentRetryTotalMinutes) {
                        logError("Permanent retry budget exhausted (action)");
                        return NET_SDK_NETWORK_FAIL_CONNECT;
                    }

                    logInf("Permanent retry: waiting "
                        + std::to_string(policy.permanentRetryWaitMinutes) + " minutes�");
                    std::this_thread::sleep_for(std::chrono::minutes(policy.permanentRetryWaitMinutes));

                    dev.disconnect();
                    if (dev.connect() == NET_SDK_SUCCESS &&
                        dev.openResource() == NET_SDK_SUCCESS) {
                        logInf("Reconnected & resource reopened. Resuming action.");
                        break; // ���� ��� �� ��action ���� ���������
                    }
                }
                if (cycles > policy.maxPermanentCycles) {
                    logError("Permanent retry cycles exceeded (action)");
                    return NET_SDK_NETWORK_FAIL_CONNECT;
                }
                continue; // ������ ����� action ��� ���� reconnect �����
            }

        case RetryDecision::ReOpenResource:
            if (reo++ < policy.maxReOpenRetries) {
                logErr(rc, "Action -> ReOpenResource");
                dev.disconnect(); // ����� ���: ensureReady ���� connect+open
                continue;
            }
            [[fallthrough]];

        case RetryDecision::ReInitSdk:
            if (rei++ < policy.maxReInitRetries) {
                logErr(rc, "Action -> ReInitSdk");
                dev.disconnect();
                dev.cleanup();
                return NET_SDK_NOINIT; // main ���� ������� ��� ������
            }
            return rc;

        case RetryDecision::Fatal:
        default:
            logErr(rc, "Action -> Fatal");
            return rc;
        }
    }
}
