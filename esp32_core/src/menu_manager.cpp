#include "menu_manager.h"
#include <Arduino.h>

MenuManager::MenuManager(DisplayManager* dm, InputManager* navBtn, InputManager* execBtn,
                         const char* opts[], MenuAction actions[], int numOpts) {
  _dm = dm;
  _navBtn = navBtn;
  _execBtn = execBtn;
  _options = opts;
  _actions = actions;
  _numOptions = numOpts;
  _selected = 0;
  _lastNavState = false;
  _lastExecState = false;

  _dm->showMenu(_options, _numOptions, _selected);
}

void MenuManager::update() {
  bool currentNav = _navBtn->isPressed();
  bool currentExec = _execBtn->isPressed();

  if(currentNav && !_lastNavState) {
    _selected++;
    if(_selected >= _numOptions) _selected = 0;
    _dm->showMenu(_options, _numOptions, _selected);
    delay(150);
  }
  _lastNavState = currentNav;

  if(currentExec && !_lastExecState) {
    if(_actions[_selected] != nullptr) {
      _actions[_selected]();
    }
    delay(150);
  }
  _lastExecState = currentExec;
}