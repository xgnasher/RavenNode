#include "display_manager.h"

DisplayManager::DisplayManager(Adafruit_SSD1306* display) {
  _display = display;
}

// Boot screen
void DisplayManager::bootScreen() {
  _display->setTextSize(1);
  _display->setTextColor(SSD1306_WHITE);
  _display->drawRect(0, 0, 128, 16, SSD1306_WHITE);
  _display->setCursor(4 ,4);
  _display->println("BOOTING <3");
  _display->drawRect(0, 16, 128, 48, SSD1306_WHITE);
  _display->setCursor(4 ,20);
  _display->println("ESP32 PenTest tool");
  _display->setCursor(4 ,52);
  _display->println("Dev by NyxOverflow");
  _display->display(); // Refresh buffer
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
  _display->setCursor(4, 4);
  _display->println("TOOLS AND SCRIPTS"); 

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