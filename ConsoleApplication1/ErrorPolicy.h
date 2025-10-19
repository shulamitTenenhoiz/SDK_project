#pragma once
#include "DVR_NET_SDK.h"
#include "LogUtils.h"

// שכבת מדיניות דקיקה: מתרגמת קוד שגיאה טכני -> החלטת התאוששות עסקית
enum class RetryDecision {
    Success,        // פעולה הצליחה
    RetryImmediate, // נסיון נוסף מיד (שגיאה זמנית/רשת)
    RetryBackoff,   // נסיון נוסף אחרי דילי (Busy/NoResource)
    ReLogin,        // להתחבר מחדש (Session/Auth/Offline)
    ReOpenResource, // לפתוח משאב מחדש (פקודה/סשן)
    ReInitSdk,      // לאתחל SDK מחדש (שבר מערכת/גרסה)
    Fatal           // כשל סופי (לא בר־התאוששות פה)
};

// מיפוי קודי SDK -> החלטה
inline RetryDecision classifyError(NET_SDK_ERROR err) {
    switch (err) {
    case NET_SDK_SUCCESS:
        return RetryDecision::Success;

        // רשת/זמני
    case NET_SDK_NETWORK_FAIL_CONNECT:
    case NET_SDK_NETWORK_NOT_CONNECT:
    case NET_SDK_NETWORK_SEND_ERROR:
    case NET_SDK_NETWORK_RECV_ERROR:
    case NET_SDK_NETWORK_RECV_TIMEOUT:
    case NET_SDK_NETWORK_ERRORDATA:
    case NET_SDK_TRY_LATER:
    case NET_SDK_CHANNEL_OFFLINE:
        return RetryDecision::RetryImmediate;

        // עומס/אין משאבים
    case NET_SDK_USER_ERROR_SYSTEM_BUSY:
    case NET_SDK_DVR_NORESOURCE:
    case NET_SDK_NORESOURCE:
    case NET_SDK_BUSY:
    case NET_SDK_MAX_USERNUM:
    case NET_SDK_OVER_MAXLINK:
        return RetryDecision::RetryBackoff;

        // התחברות/סשן/ניתוק — עדיין שווה רילוגין
    case NET_SDK_DEVICE_OFFLINE:
    case NET_SDK_USERID_ISUSING:
        return RetryDecision::ReLogin;

        // === קרדנציאל לא תקין (לא ננסה שוב) ===
    case NET_SDK_PASSWORD_ERROR:
    case NET_SDK_USER_ERROR_NO_USER:
    case NET_SDK_USER_ERROR_USER_OR_PASSWORD_IS_NULL:
    case NET_SDK_LOGIN_REFUSED:
    case NET_SDK_IPMISMATCH:
    case NET_SDK_MACMISMATCH:
    case NET_SDK_USERNOTEXIST:
        return RetryDecision::Fatal;

        // פקודה/סשן תלוי־משאב
    case NET_SDK_OPERNOTFINISH:
    case NET_SDK_COMMAND_TIMEOUT:
        return RetryDecision::ReOpenResource;

        // SDK לא מאותחל/שבור/לא תואם
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
