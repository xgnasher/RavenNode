#ifndef MENU_MANAGER_H
#define MENU_MANAGER_H

#include "display_manager.h"
#include "input_manager.h"

typedef void (*MenuAction)(); // option signaler

class MenuManager {
  public:
    MenuManager(DisplayManager* dm, InputManager* navBtn, InputManager* execBtn,
                const char* opts[], MenuAction actions[], int numOpts);
    void update(); // call on loop()
  private:
    DisplayManager* _dm;
    InputManager* _navBtn;
    InputManager* _execBtn;
    const char** _options;
    MenuAction* _actions;
    int _numOptions;
    int _selected;
    bool _lastNavState;
    bool _lastExecState;
};

#endif