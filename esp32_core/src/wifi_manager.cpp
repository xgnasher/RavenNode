#include "wifi_manager.h"
#include <Arduino.h>

WiFiManager::WiFiManager(const char* ssid, const char* password, int ledPin) {
    _ssid = ssid;
    _password = password;
    _ledPin = ledPin;
}

bool WiFiManager::connect() {
    pinMode(_ledPin, OUTPUT);
    WiFi.begin(_ssid, _password);

    unsigned long start = millis();

    while(WiFi.status() != WL_CONNECTED) {
        if(millis() - start > 10000) { // timeout 10s
            digitalWrite(_ledPin, LOW);
            return false;
        }
        delay(500);
    }

    digitalWrite(_ledPin, HIGH); // LED ON if connected
    return true;
}

bool WiFiManager::isConnected() {
    return WiFi.status() == WL_CONNECTED;
}