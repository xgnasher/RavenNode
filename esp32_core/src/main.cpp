#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include "display_manager.h"
#include "input_manager.h"
#include "menu_manager.h"

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define NAV_PIN 15    // navigation button on p15 
#define EXEC_PIN 16   // exec button on p16
#define LED_PIN 2     // LED 

// screen
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
DisplayManager* dm;

// buttons
InputManager navButton(NAV_PIN);
InputManager execButton(EXEC_PIN);

// menu options
const char* options[] = {"LED ON", "LED OFF", "Test"};

// options funtion
void ledOn() {
  digitalWrite(LED_PIN, HIGH);
  dm->showMessage("LED ON", 50);
}

void ledOff() {
  digitalWrite(LED_PIN, LOW);
  dm->showMessage("LED OFF", 50);
}

void testMode() {
  dm->showMessage("this is a open source project", 50);
}

// function signaler
MenuAction actions[] = {ledOn, ledOff, testMode};
MenuManager* menu;

void setup() {
  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);

  // init screen first
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("Display failed");
    while(true);
  }

  dm = new DisplayManager(&display);
  dm->bootScreen();
  delay(3000);

  // start buttons
  navButton.begin();
  execButton.begin();

  // start menu
  menu = new MenuManager(dm, &navButton, &execButton, options, actions, 3);
}

void loop() {
  // update
  menu->update();
}