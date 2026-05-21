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

#include "display_manager.h"
#include "input_manager.h"
#include "menu_manager.h"
#include "wifi_manager.h"
#include "scan_manager.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define NAV_PIN 17    // navigation button on p17
#define EXEC_PIN 16   // exec button on p16

// screen
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
DisplayManager* dm;
ScanManager* scan;

// buttons
InputManager navButton(NAV_PIN);
InputManager execButton(EXEC_PIN);

// wifi
WiFiManager wifi("SSID", "PASSWORD", 2);

// menu options
const char* options[] = {"Wifi CONNECT", "PORT SCAN","NFC HF 13.56 MHz","RFID LF 125 KHz","VERSION"};

// options funtion
void connectWiFi() {
    if(wifi.connect()) {
        dm->clearDisplay();
        dm->drawHeader("WiFi Status");
        dm->showMessage("Connected", 16);
    } else {
        dm->clearDisplay();
        dm->drawHeader("WiFi Status");
        dm->showMessage("Wrong password", 16);
    }
}

void runBasicScan() {
    if(wifi.isConnected()) {
        scan->basicScan("192.168.1.81"); // target ip
    } else {
        dm->clearDisplay();
        dm->drawHeader("ERROR");
        dm->showMessage("No WiFi :(", 16);
    }
}

void NFCtools(){
    dm->clearDisplay();
    dm->drawHeader("NFC HF 13.56 MHz");
    dm->showMessage("Still working \non it", 16);
}

void RFIDtools(){
    dm->clearDisplay();
    dm->drawHeader("RFID LF 125 KHz");
    dm->showMessage("Working on it", 16);
}

void displayVersion(){
    dm->clearDisplay();
    dm->drawHeader("RavenOS");
    dm->showMessage("Version 0.2", 16);
    dm->showMessage("2026 NyxOverflow", 50);
}

// function signaler
MenuAction actions[] = {connectWiFi, runBasicScan, NFCtools, RFIDtools, displayVersion};
MenuManager* menu;

void setup() {
  Serial.begin(115200);

  // init screen first
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("Display failed");
    while(true);
  }

  dm = new DisplayManager(&display);
  scan = new ScanManager(dm);
  dm->bootScreen();
  delay(4000);

  // start buttons
  navButton.begin();
  execButton.begin();

  // start menu
  menu = new MenuManager(dm, &navButton, &execButton, options, actions, 5);
}

void loop() {
  // update
  menu->update();
}