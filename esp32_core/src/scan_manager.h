#ifndef SCAN_MANAGER_H
#define SCAN_MANAGER_H

#include "display_manager.h"

class ScanManager {
private:
    DisplayManager* display;  

public:
    ScanManager(DisplayManager* dm);  
    void basicScan(const char* targetIP);

private:
    bool scanPort(const char* ip, int port);
};

#endif