#ifndef DISPLAY_MANAGER_H
#define DISPLAY_MANAGER_H

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

class DisplayManager {
  public:
    DisplayManager(Adafruit_SSD1306* display);
    void bootScreen();

    void showMenu(const char* options[], int numOptions, int selected);
    void showMessage(const char* msg, int line);
    void clearDisplay(); 
    void drawHeader(const char* text);
    void drawLine(const char* text, int y);
    void refresh();
  private:
    Adafruit_SSD1306* _display;
};

#endif