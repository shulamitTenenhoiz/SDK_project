#include "DeviceManager.h"
#include "DeviceValidator.h"
#include <iostream>
#include "LogUtils.h"


// Constructor
DeviceManager::DeviceManager(const std::string& ip, int port, const std::string& username, const std::string& password)
    : sdkInitialized(false), resourceOpened(false), userID(-1), ip(ip), port(port), username(username), password(password)
{
    // Validate
    DeviceValidation::validateIPAndLength(ip);
    DeviceValidation::validatePort(port);
    DeviceValidation::validateUsername(username);
    DeviceValidation::validatePassword(password);

    // Initialize SDK
    if (!NET_SDK_Init()) {
        throw std::runtime_error("SDK init failed, error code: " + std::to_string(NET_SDK_GetLastError()));
    }
    sdkInitialized = true;
}

// Connect
NET_SDK_ERROR DeviceManager::connect() {
    if (!sdkInitialized) return NET_SDK_NOINIT;

    if (userID >= 0) {
        return NET_SDK_USER_ERROR_ALREDAY_LOGIN; // כבר מחוברים
    }

    userID = NET_SDK_Login(const_cast<char*>(ip.c_str()), port,
        const_cast<char*>(username.c_str()),
        const_cast<char*>(password.c_str()),
        &deviceInfo);

    if (userID < 0) return static_cast<NET_SDK_ERROR>(NET_SDK_GetLastError());
    return NET_SDK_SUCCESS;
}

// Open Resource
NET_SDK_ERROR DeviceManager::openResource() {
    if (userID < 0) return NET_SDK_NOINIT;

    // STRICT: אם כבר פתוח – החזרי שגיאה ברורה
    if (resourceOpened) {
        return NET_SDK_ORDER_ERROR; // “ניסיון פתיחה כפול”
    }

    // כאן פתיחת המשאב בפועל מול ה-SDK...
    resourceOpened = true;
    return NET_SDK_SUCCESS;
}


// Disconnect
void DeviceManager::disconnect() {
    if (userID >= 0) {
        NET_SDK_Logout(userID);
        userID = -1;
        resourceOpened = false;
    }
}

// Cleanup SDK
void DeviceManager::cleanup() {
    if (sdkInitialized) {
        NET_SDK_Cleanup();
        sdkInitialized = false;
    }
}

// Print info
void DeviceManager::printDeviceInfo() {
    if (!resourceOpened) throw std::runtime_error("Resource not opened");
    std::string serial(deviceInfo.szSN);
    std::cout << "=== Device Information ===\n";
    std::cout << "Device Serial: " << serial << "\n";
    std::cout << "Device Name:   " << deviceInfo.deviceName << "\n";
    std::cout << "Device Model:  " << deviceInfo.deviceProduct << "\n";
    std::cout << "Device Type:   " << (int)deviceInfo.deviceType << "\n";
    std::cout << "==========================\n";
}

// Destructor
DeviceManager::~DeviceManager() {
    disconnect();
    cleanup();
}
