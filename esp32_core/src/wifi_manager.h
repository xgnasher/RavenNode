#ifndef WIFI_MANAGER_H
#define WIFI_MANAGER_H

#include <WiFi.h>

class WiFiManager {
public:
    WiFiManager(const char* ssid, const char* password, int ledPin);
    bool connect();
    bool isConnected();
private:
    const char* _ssid;
    const char* _password;
    int _ledPin;
};

#endif