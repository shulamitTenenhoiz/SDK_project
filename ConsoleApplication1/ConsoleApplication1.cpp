#include <iostream>
#include <thread>
#include <chrono>
#include "DeviceManager.h"
#include "LogUtils.h"
#include "ErrorPolicy.h"
#include "MasterRunner.h"

int main() {
    const std::string ip = "83.229.63.118";
    const int port = 6037;
    const std::string username = "admin";
    const std::string password = "shabatkosher";

    RetryPolicy policy;
    policy.maxImmediateRetries = 3;
    policy.maxBackoffRetries = 5;
    policy.maxReLoginRetries = 3;
    policy.maxReOpenRetries = 3;
    policy.maxReInitRetries = 2;
    policy.backoffSeconds = 5;
    policy.permanentRetryWaitMinutes = 3;

    // ✅ חשוב: המקדמים החדשים למניעת אינסוף
    policy.maxPermanentCycles = 10;
    policy.permanentRetryTotalMinutes = 60;
    policy.maxInitRetryCycles = 5;

    int initCycles = 0;

    while (initCycles++ < policy.maxInitRetryCycles) {
        try {
            DeviceManager dev(ip, port, username, password);

            auto action = [](DeviceManager& d) -> NET_SDK_ERROR {
                try {
                    d.printDeviceInfo();
                    return NET_SDK_SUCCESS;
                }
                catch (...) {
                    return NET_SDK_OPERNOTFINISH;
                }
                };

            NET_SDK_ERROR rc = runWithRecovery(dev, policy, action);

            if (rc == NET_SDK_NOINIT) {
                DeviceManager dev2(ip, port, username, password);
                rc = runWithRecovery(dev2, policy, action);
            }

            if (rc != NET_SDK_SUCCESS) {
                logError("Run failed", rc);
                return 1;
            }

            logInfo("Program finished successfully.");
            return 0;
        }
        catch (const std::exception& ex) {
            logError(std::string("SDK init failed in constructor: ") + ex.what());
            if (initCycles >= policy.maxInitRetryCycles) {
                logError("Max SDK init retries reached – exiting.");
                return 2;
            }
            logInfo("Will retry SDK init in 3 minutes...");
            std::this_thread::sleep_for(std::chrono::minutes(3));
        }
    }

    logError("Init retry loop exhausted – exiting.");
    return 2;
}