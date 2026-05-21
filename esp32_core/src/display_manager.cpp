#include "display_manager.h"
#include "skull.h"
#include "grim_reaper.h"

DisplayManager::DisplayManager(Adafruit_SSD1306* display) {
  _display = display;
}

// Boot screen
void DisplayManager::bootScreen() {
  _display->clearDisplay();
  _display->setTextSize(1);
  _display->setTextColor(SSD1306_WHITE);
  _display->drawRect(0, 0, 66, 16, SSD1306_WHITE);
  _display->setCursor(4 ,4);
  _display->println("BOOTING <3");
  _display->setCursor(0 ,20);
  _display->println("RavenNode");
  _display->setCursor(0 ,44);
  _display->println("RavenOS by");
  _display->setCursor(0 ,54);
  _display->println("NyxOverflow");
  _display->drawBitmap(
        64,
        0,
        grim_reaper,
        64,
        64,
        SSD1306_WHITE
  );
  _display->display();
}

void DisplayManager::clearDisplay() {
    _display->clearDisplay();
}

//Header
void DisplayManager::drawHeader(const char* text) {
   _display->setTextSize(1);
   _display->setTextColor(SSD1306_WHITE);
   _display->drawRect(0, 0, 128, 16, SSD1306_WHITE);
   _display->setTextColor(SSD1306_WHITE);
   _display->setCursor(4, 4); 
   _display->println(text);
}

//Text position (only used on scan manager for now)
void DisplayManager::drawLine(const char* text, int y) {
    _display->setTextSize(1);
    _display->setTextColor(SSD1306_WHITE);
    _display->setCursor(0, y);
    _display->println(text);
}

void DisplayManager::refresh() {
    _display->display();
}

// Draw menu with option
void DisplayManager::showMenu(const char* options[], int numOptions, int selected) {
  _display->clearDisplay();
  _display->setTextSize(1);
  
  // Yellow part
  _display->drawRect(0, 0, 128, 16, SSD1306_WHITE); 
  _display->setTextColor(SSD1306_WHITE);
  _display->setCursor(8, 4);
  _display->println("#TOOLS AND SCRIPTS#"); 

// Options
    _display->setTextColor(SSD1306_WHITE);
    for(int i = 0; i < numOptions; i++) {
        int y = 16 + i * 10; // Below header
        _display->setCursor(0, y);
        if(i == selected) _display->print("> ");
        else _display->print("  ");
        _display->println(options[i]);
    }

    _display->display();
}

// Show message method
void DisplayManager::showMessage(const char* msg, int line) {
    _display->setCursor(0, line);
    _display->println(msg);
    _display->display();
}