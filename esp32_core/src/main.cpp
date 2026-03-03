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
#define NAV_PIN 15    // navigation button on p15 
#define EXEC_PIN 16   // exec button on p16

// screen
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
DisplayManager* dm;
ScanManager* scan;

// buttons
InputManager navButton(NAV_PIN);
InputManager execButton(EXEC_PIN);

// wifi
WiFiManager wifi("WIFI_SSID", "PASSWORD", 2);

// menu options
const char* options[] = {"BASIC SCAN", "Wifi CONNECT"};

// options funtion
void connectWiFi() {
    if(wifi.connect()) {
        dm->showMessage("WiFi OK", 50);
    } else {
        dm->showMessage("WiFi FAIL", 50);
    }
}

void runBasicScan() {
    if(wifi.isConnected()) {
        scan->basicScan("IP_HERE"); // target ip
    } else {
        dm->showMessage("No WiFi", 50);
    }
}

// function signaler
MenuAction actions[] = {runBasicScan, connectWiFi};
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
  delay(2000);

  // start buttons
  navButton.begin();
  execButton.begin();

  // start menu
  menu = new MenuManager(dm, &navButton, &execButton, options, actions, 2);
}

void loop() {
  // update
  menu->update();

}
