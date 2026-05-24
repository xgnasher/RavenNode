#include "nfc_manager.h"

NFCManager::NFCManager(Adafruit_PN532* nfc) {
    this->nfc = nfc;
}

// ================= SCAN =================
bool NFCManager::scan(DisplayManager* dm) {

    if(hasTag) return true; 

    dm->clearDisplay();
    dm->drawHeader("NFC Scan");
    dm->showMessage("Tap tag...", 20);

    if (nfc->readPassiveTargetID(PN532_MIFARE_ISO14443A, uid, &uidLength)) {

        hasTag = true; 

        return true;
    }

    return false;
}
// ================= RESULT =================
void NFCManager::showResult(DisplayManager* dm) {

    dm->clearDisplay();
    dm->drawHeader("Tag Found");

    String uidStr = "";

    for(int i = 0; i < uidLength; i++) {
        if(uid[i] < 0x10) uidStr += "0";
        uidStr += String(uid[i], HEX);
        uidStr += " ";
    }

    uidStr.toUpperCase();

    String msg = "UID:\n" + uidStr;

    dm->showMessage(msg.c_str(), 20);
}

bool NFCManager::tagAvailable() {
    return hasTag;
}

void NFCManager::clearTag() {
    hasTag = false;
    uidLength = 0;
}