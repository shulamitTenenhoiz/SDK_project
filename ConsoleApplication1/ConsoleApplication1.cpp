#include <iostream>
#include <Windows.h>
#include "DVR_NET_SDK.h"

// אתחול ה-SDK
bool initSDK() {
    if (!NET_SDK_Init()) {
        std::cout << "SDK init failed, error code: "
            << NET_SDK_GetLastError() << std::endl;
        return false;
    }
    return true;
}

// התחברות למכשיר
LONG loginToDevice(char* ip, int port, char* username, char* password, NET_SDK_DEVICEINFO& deviceInfo) {
    LONG userID = NET_SDK_Login(ip, port, username, password, &deviceInfo);
    if (userID < 0) {
        std::cout << "Login failed, error code: "
            << NET_SDK_GetLastError() << std::endl;
    }
    return userID;
}
// הצגת פרטי המכשיר
void printDeviceInfo(const NET_SDK_DEVICEINFO& deviceInfo) {
    std::string serial(deviceInfo.szSN, deviceInfo.szSN + sizeof(deviceInfo.szSN));

    std::cout << "=== Device Information ===" << std::endl;
    std::cout << "Device Serial: " << serial << std::endl;
    std::cout << "Device Name:   " << deviceInfo.deviceName << std::endl;
    std::cout << "Device Model:  " << deviceInfo.deviceProduct << std::endl;
    std::cout << "Device Type:   " << (int)deviceInfo.deviceType << std::endl;
    std::cout << "==========================" << std::endl;
}

// התנתקות מהמכשיר
void logoutFromDevice(LONG userID) {
    NET_SDK_Logout(userID);
}

// ניקוי SDK
void cleanupSDK() {
    NET_SDK_Cleanup();
}

int main() {
    if (!initSDK()) {
        return -1;
    }

    // פרטי החיבור למכשיר
    char ip[] = "83.229.63.118";
    int port = 6036;
    char username[] = "testing";
    char password[] = "testing1234";

    NET_SDK_DEVICEINFO deviceInfo;

    LONG userID = loginToDevice(ip, port, username, password, deviceInfo);
    if (userID < 0) {
        cleanupSDK();
        return -1;
    }

    std::cout << "Login successful!" << std::endl;
    printDeviceInfo(deviceInfo);

    logoutFromDevice(userID);
    cleanupSDK();

    return 0;
}