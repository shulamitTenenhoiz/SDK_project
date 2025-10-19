#pragma once
#include "DVR_NET_SDK.h"
#include "LogUtils.h"

// ���� ������� �����: ������ ��� ����� ���� -> ����� �������� �����
enum class RetryDecision {
    Success,        // ����� ������
    RetryImmediate, // ����� ���� ��� (����� �����/���)
    RetryBackoff,   // ����� ���� ���� ���� (Busy/NoResource)
    ReLogin,        // ������ ���� (Session/Auth/Offline)
    ReOpenResource, // ����� ���� ���� (�����/���)
    ReInitSdk,      // ����� SDK ���� (��� �����/����)
    Fatal           // ��� ���� (�� ����������� ��)
};

// ����� ���� SDK -> �����
inline RetryDecision classifyError(NET_SDK_ERROR err) {
    switch (err) {
    case NET_SDK_SUCCESS:
        return RetryDecision::Success;

        // ���/����
    case NET_SDK_NETWORK_FAIL_CONNECT:
    case NET_SDK_NETWORK_NOT_CONNECT:
    case NET_SDK_NETWORK_SEND_ERROR:
    case NET_SDK_NETWORK_RECV_ERROR:
    case NET_SDK_NETWORK_RECV_TIMEOUT:
    case NET_SDK_NETWORK_ERRORDATA:
    case NET_SDK_TRY_LATER:
    case NET_SDK_CHANNEL_OFFLINE:
        return RetryDecision::RetryImmediate;

        // ����/��� ������
    case NET_SDK_USER_ERROR_SYSTEM_BUSY:
    case NET_SDK_DVR_NORESOURCE:
    case NET_SDK_NORESOURCE:
    case NET_SDK_BUSY:
    case NET_SDK_MAX_USERNUM:
    case NET_SDK_OVER_MAXLINK:
        return RetryDecision::RetryBackoff;

        // �������/���/����� � ����� ���� �������
    case NET_SDK_DEVICE_OFFLINE:
    case NET_SDK_USERID_ISUSING:
        return RetryDecision::ReLogin;

        // === �������� �� ���� (�� ���� ���) ===
    case NET_SDK_PASSWORD_ERROR:
    case NET_SDK_USER_ERROR_NO_USER:
    case NET_SDK_USER_ERROR_USER_OR_PASSWORD_IS_NULL:
    case NET_SDK_LOGIN_REFUSED:
    case NET_SDK_IPMISMATCH:
    case NET_SDK_MACMISMATCH:
    case NET_SDK_USERNOTEXIST:
        return RetryDecision::Fatal;

        // �����/��� ���������
    case NET_SDK_OPERNOTFINISH:
    case NET_SDK_COMMAND_TIMEOUT:
        return RetryDecision::ReOpenResource;

        // SDK �� ������/����/�� ����
    case NET_SDK_NOINIT:
    case NET_SDK_PROGRAM_EXCEPTION:
    case NET_SDK_VERSION_NOMATCH:
    case NET_SDK_DSSDK_ERROR:
    case NET_SDK_LOADPLAYERSDKFAILED:
    case NET_SDK_LOADDSSDKFAILED:
        return RetryDecision::ReInitSdk;

    default:
        return RetryDecision::Fatal;
    }
}
