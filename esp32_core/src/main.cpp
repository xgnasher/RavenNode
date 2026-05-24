/*
Copyright (c) 2026 NyxOverflow 

Permission is granted to anyone to use, copy, modify, and distribute this software, 
for educational and personal purposes only, provided that this notice is included. 

THIS SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND. 
THE AUTHOR IS NOT RESPONSIBLE FOR ANY DAMAGE, MISUSE, OR LEGAL CONSEQUENCES 
RESULTING FROM THE USE OF THIS SOFTWARE.

Use responsibly and ethically. This software is intended for learning, experimentation, 
and personal development purposes only.
*/
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_PN532.h>

#include "display_manager.h"
#include "input_manager.h"
#include "menu_manager.h"
#include "wifi_manager.h"
#include "scan_manager.h"
#include "nfc_manager.h"

// ================= DISPLAY =================
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
DisplayManager* dm;

// ================= INPUT =================
#define NAV_PIN 17
#define EXEC_PIN 16

InputManager navButton(NAV_PIN);
InputManager execButton(EXEC_PIN);

// ================= MODULES =================
WiFiManager wifi("SSID", "PASSWORD", 2);
ScanManager* scan;

Adafruit_PN532 nfcHardware(21, 22);
NFCManager* nfc;

// ================= MENU =================
MenuManager* menu;

// ================= STATE =================
enum AppState {
    STATE_MAIN,
    STATE_NFC,
    STATE_RFID
};

AppState state = STATE_MAIN;
int selectedIndex = 0;

// ================= BUTTON CONTROL =================
unsigned long lastNavTime = 0;
unsigned long lastExecTime = 0;

const int NAV_DEBOUNCE_MS = 180;
const int EXEC_DEBOUNCE_MS = 250;

// ================= MENU OPTIONS =================
const char* mainOptions[] = {
    "WiFi CONNECT",
    "PORT SCAN",
    "NFC HF 13.56 MHz",
    "RFID LF 125 KHz",
    "VERSION"
};

const char* nfcOptions[] = {
    "SCAN TAG",
    "BACK"
};

const char* rfidOptions[] = {
    "READ UID",
    "BACK"
};

// ================= MAIN ACTIONS =================
void connectWiFi() {
    dm->clearDisplay();
    dm->drawHeader("WiFi");

    if(wifi.connect()) {
        dm->showMessage("Connected", 16);
    } else {
        dm->showMessage("Failed", 16);
    }
}
// wifi module
void runScan() {
    dm->clearDisplay();
    dm->drawHeader("Scanner");

    if(wifi.isConnected()) {
        scan->basicScan("192.168.1.81");
    } else {
        dm->showMessage("No WiFi", 16);
    }
}
// basic scan
void openNFC() {
    state = STATE_NFC;
    selectedIndex = 0;

    dm->clearDisplay();
}
//NFC module, changes to nfc state and clear display
void openRFID() {
    state = STATE_RFID;
    selectedIndex = 0;

    dm->clearDisplay();
}

void showVersion() {
    dm->clearDisplay();
    dm->drawHeader("RavenOS");
    dm->showMessage("v0.3 unstable\n2026 NyxOverflow", 16);
}

// ================= ACTION TABLE =================
MenuAction actions[] = {
    connectWiFi,
    runScan,
    openNFC,
    openRFID,
    showVersion
};
//order the classes to use on the menu
// ================= NFC =================

void handleNFC() {

    if(!nfc->tagAvailable()) {

        if(nfc->scan(dm)) {
            nfc->showResult(dm);
        }

        return;
    }

    
    dm->clearDisplay();
    nfc->showResult(dm);

    dm->showMessage("EXEC=WRITE\nNAV=BACK", 40);
//if the nfc module detects a tag, a read command is send
    if(execButton.isPressed()) {

        // Future write addition
        dm->clearDisplay();
        dm->drawHeader("WRITE NFC");
        dm->showMessage("Experimental", 20);

        delay(2000); //Modify this delay, 1000 = 1s
    }

    if(navButton.isPressed()) {
        nfc->clearTag();  
        state = STATE_MAIN;
        selectedIndex = 0;
        dm->clearDisplay();
    }
}
// Press navigation button to go back 
// ================= RFID =================
void handleRFID() {

    dm->clearDisplay();
    dm->drawHeader("RFID Tools");
    dm->showMenu(rfidOptions, 2, selectedIndex);

    if(navButton.isPressed()) {
        if(millis() - lastNavTime > NAV_DEBOUNCE_MS) {
            selectedIndex++;
            if(selectedIndex >= 2) selectedIndex = 0;
            lastNavTime = millis();
        }
    }

    if(execButton.isPressed()) {
        if(millis() - lastExecTime > EXEC_DEBOUNCE_MS) {

            dm->clearDisplay();

            if(selectedIndex == 0) {
                dm->drawHeader("RFID");
                dm->showMessage("Experimental", 20);
            }

            if(selectedIndex == 1) {
                state = STATE_MAIN;
                selectedIndex = 0;
                dm->clearDisplay();
            }

            lastExecTime = millis();
        }
    }
}
//RFID module for future addition
// ================= SETUP =================
void setup() {

    Serial.begin(115200);

    Wire.begin(21, 22);

    if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
        while(true);
    }

    dm = new DisplayManager(&display);
    scan = new ScanManager(dm);

    nfcHardware.begin();
    nfcHardware.SAMConfig();
    nfc = new NFCManager(&nfcHardware);

    dm->bootScreen();
    delay(2000);

    navButton.begin();
    execButton.begin();

    menu = new MenuManager(dm, &navButton, &execButton, mainOptions, actions, 5);
}

// ================= LOOP =================
void loop() {

    if(state == STATE_MAIN) {
        menu->update();
    }
    else if(state == STATE_NFC) {
        handleNFC();
    }
    else if(state == STATE_RFID) {
        handleRFID();
    }

    delay(10);
}