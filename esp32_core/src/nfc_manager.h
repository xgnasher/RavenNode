#pragma once
#include <Adafruit_PN532.h>
#include "display_manager.h"

class NFCManager {
private:
    Adafruit_PN532* nfc;

    uint8_t uid[7];
    uint8_t uidLength = 0;
    bool hasTag = false;
    

public:
    NFCManager(Adafruit_PN532* nfc);

    bool scan(DisplayManager* dm);
    void showResult(DisplayManager* dm);
    
    bool tagAvailable();
    void clearTag();
};