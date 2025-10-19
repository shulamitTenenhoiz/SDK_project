#pragma once
#include <iostream>
#include <string>
#include "DVR_NET_SDK.h"

// שם קריא לקוד שגיאה
inline const char* sdkErrName(NET_SDK_ERROR e) {
    switch (e) {
    case NET_SDK_SUCCESS:                return "SUCCESS";
    case NET_SDK_PASSWORD_ERROR:         return "PASSWORD_ERROR";
    case NET_SDK_NOENOUGH_AUTH:          return "NOENOUGH_AUTH";
    case NET_SDK_NOINIT:                 return "NOINIT";
    case NET_SDK_CHANNEL_ERROR:          return "CHANNEL_ERROR";
    case NET_SDK_OVER_MAXLINK:           return "OVER_MAXLINK";
    case NET_SDK_LOGIN_REFUSED:          return "LOGIN_REFUSED";
    case NET_SDK_VERSION_NOMATCH:        return "VERSION_NOMATCH";
    case NET_SDK_NETWORK_FAIL_CONNECT:   return "NETWORK_FAIL_CONNECT";
    case NET_SDK_NETWORK_NOT_CONNECT:    return "NETWORK_NOT_CONNECT";
    case NET_SDK_NETWORK_SEND_ERROR:     return "NETWORK_SEND_ERROR";
    case NET_SDK_NETWORK_RECV_ERROR:     return "NETWORK_RECV_ERROR";
    case NET_SDK_NETWORK_RECV_TIMEOUT:   return "NETWORK_RECV_TIMEOUT";
    case NET_SDK_NETWORK_ERRORDATA:      return "NETWORK_ERRORDATA";
    case NET_SDK_ORDER_ERROR:            return "ORDER_ERROR";
    case NET_SDK_OPER_BY_OTHER:          return "OPER_BY_OTHER";
    case NET_SDK_OPER_NOPERMIT:          return "OPER_NOPERMIT";
    case NET_SDK_COMMAND_TIMEOUT:        return "COMMAND_TIMEOUT";
    case NET_SDK_PARAMETER_ERROR:        return "PARAMETER_ERROR";
    case NET_SDK_NOSUPPORT:              return "NOSUPPORT";
    case NET_SDK_BUSY:                   return "BUSY";
    case NET_SDK_DVR_NORESOURCE:         return "DVR_NORESOURCE";
    case NET_SDK_TRY_LATER:              return "TRY_LATER";
    case NET_SDK_DEVICE_OFFLINE:         return "DEVICE_OFFLINE";
    case NET_SDK_USER_ERROR_NO_USER:     return "NO_USER";
    case NET_SDK_USER_ERROR_USER_OR_PASSWORD_IS_NULL: return "USER_OR_PASSWORD_IS_NULL";
    case NET_SDK_USER_ERROR_ALREDAY_LOGIN: return "ALREADY_LOGIN";
    case NET_SDK_USER_ERROR_SYSTEM_BUSY: return "SYSTEM_BUSY";
    case NET_SDK_NORESOURCE:             return "NORESOURCE";
    case NET_SDK_PROGRAM_EXCEPTION:      return "PROGRAM_EXCEPTION";
    case NET_SDK_OPERNOTFINISH:          return "OPERNOTFINISH";
    default: return "UNKNOWN_ERROR";
    }
}

// לוגים אחידים
inline void logInfo(const std::string& msg) {
    std::cout << "[LOG] " << msg << "\n";
}
inline void logWarn(const std::string& msg) {
    std::cout << "[WARN] " << msg << "\n";

}

inline void logError(const std::string& msg) {
    std::cerr << "[ERROR] " << msg << "\n";
}
inline void logError(const std::string& msg, NET_SDK_ERROR err) {
    std::cerr << "[ERROR] " << msg
        << " (" << sdkErrName(err) << " / " << static_cast<int>(err) << ")\n";
}
