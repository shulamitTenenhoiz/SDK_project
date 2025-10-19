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

    NET_SDK_ERROR connect();       // 1 - �������
    NET_SDK_ERROR openResource();  // 2 - ����� ����
    void disconnect();             // 3 - �������
    void cleanup();                // 4 - ����� SDK
    void printDeviceInfo();
    ~DeviceManager();

    // === �����: ��� ����� (������ �-MasterRunner) ===
    bool isSdkInitialized() const { return sdkInitialized; }
    bool isConnected() const { return userID >= 0; }
    bool isResourceOpened() const { return resourceOpened; }

    // ���������: �� ���� ������ ������ ����� ��� ��� ����
    void setCredentials(std::string ip_, int port_, std::string user_, std::string pass_) {
        ip = std::move(ip_); port = port_; username = std::move(user_); password = std::move(pass_);
    }
};
