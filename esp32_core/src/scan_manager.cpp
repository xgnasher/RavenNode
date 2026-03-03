#include "scan_manager.h"
#include <WiFi.h>

ScanManager::ScanManager(DisplayManager* dm) {
    display = dm;  
}

bool ScanManager::scanPort(const char* ip, int port) {
    WiFiClient client;

    if(client.connect(ip, port)) {
        client.stop();
        return true;  // open port
    }

    return false;  // closed port
}

void ScanManager::basicScan(const char* targetIP) {
    const int ports[] = {22, 80, 443, 53};
    const int totalPorts = 4;

    display->clearDisplay();
    display->drawHeader("BASIC SCAN RESULTS");

    for(int i = 0; i < totalPorts; i++) {
        bool open = scanPort(targetIP, ports[i]);
        char buffer[30];
        sprintf(buffer, "Port %d: %s", ports[i], open ? "OPEN" : "CLOSED");
        display->drawLine(buffer, 16 + i*10);
    }

    display->refresh();
}