#pragma once
#include <string>
#include <Windows.h>
#include "DVR_NET_SDK.h"

class DeviceManager {
private:
    bool sdkInitialized;
    bool resourceOpened;
    LONG userID;
    NET_SDK_DEVICEINFO deviceInfo;
    std::string ip;
    int port;
    std::string username;
    std::string password;

public:
    DeviceManager(const std::string& ip, int port, const std::string& username, const std::string& password);

    NET_SDK_ERROR connect();       // 1 - התחברות
    NET_SDK_ERROR openResource();  // 2 - פתיחת משאב
    void disconnect();             // 3 - התנתקות
    void cleanup();                // 4 - ניקוי SDK
    void printDeviceInfo();
    ~DeviceManager();

    // === תוספת: מצב פנימי (לשימוש ב-MasterRunner) ===
    bool isSdkInitialized() const { return sdkInitialized; }
    bool isConnected() const { return userID >= 0; }
    bool isResourceOpened() const { return resourceOpened; }

    // אופציונלי: אם תרצי להחליף פרמטרי חיבור תוך כדי ריצה
    void setCredentials(std::string ip_, int port_, std::string user_, std::string pass_) {
        ip = std::move(ip_); port = port_; username = std::move(user_); password = std::move(pass_);
    }
};
