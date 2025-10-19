#pragma once
#include <string>
#include <stdexcept>
#include <regex>

namespace DeviceValidation {
    constexpr size_t DEFAULT_USERNAME_MIN = 3;
    constexpr size_t DEFAULT_PASSWORD_MIN = 6;
    constexpr unsigned short PORT_MIN = 1;
    constexpr unsigned short PORT_MAX = 65535;

    inline void validateNotEmpty(const std::string& value, const std::string& name) {
        if (value.empty()) throw std::invalid_argument(name + " cannot be empty");
    }

    inline void validateIPFormat(const std::string& ip) {
        static const std::regex ipRegex(R"(^((25[0-5]|2[0-4]\d|1?\d{1,2})\.){3}(25[0-5]|2[0-4]\d|1?\d{1,2})$)");
        if (!std::regex_match(ip, ipRegex)) {
            throw std::invalid_argument("IP format invalid (expected: xxx.xxx.xxx.xxx, each 0-255)");
        }
    }

    inline void validateIPAndLength(const std::string& ip) {
        validateNotEmpty(ip, "IP");
        if (ip.size() > 15) throw std::invalid_argument("IP too long (>15 chars)");
        validateIPFormat(ip);
    }

    inline void validatePort(int port) {
        if (port < static_cast<int>(PORT_MIN) || port > static_cast<int>(PORT_MAX)) {
            throw std::out_of_range("Port out of range (1-65535)");
        }
    }

    inline void validateMinLength(const std::string& value, size_t minLen, const std::string& name) {
        if (value.size() < minLen) {
            throw std::invalid_argument(name + " must be at least " + std::to_string(minLen) + " characters");
        }
    }

    inline void validateUsername(const std::string& username, size_t minLen = DEFAULT_USERNAME_MIN) {
        validateNotEmpty(username, "Username");
        validateMinLength(username, minLen, "Username");
        static const std::regex userRegex(R"(^[A-Za-z0-9_.-]+$)");
        if (!std::regex_match(username, userRegex)) {
            throw std::invalid_argument("Username contains invalid characters. Allowed: letters, digits, underscore, dot, hyphen");
        }
    }

    inline void validatePassword(const std::string& password, size_t minLen = DEFAULT_PASSWORD_MIN) {
        validateNotEmpty(password, "Password");
        validateMinLength(password, minLen, "Password");
    }
}
