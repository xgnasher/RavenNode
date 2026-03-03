#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include <Arduino.h>

class InputManager {
  public:
    InputManager(uint8_t pin);  // Constructor pin status recived
    void begin();               // start pin
    bool isPressed();           // pin pressed if
  private:
    uint8_t _pin;               // save pin
};

#endif