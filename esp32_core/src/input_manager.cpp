#include "input_manager.h"

// Constructor: save pin on button
InputManager::InputManager(uint8_t pin) {
  _pin = pin;
}

// pin as input
void InputManager::begin() {
  pinMode(_pin, INPUT_PULLUP); // HIGH non-pressed, LOW pressed
}

// true if button pressed
bool InputManager::isPressed() {
  return digitalRead(_pin) == LOW; // LOW = pressed button
}