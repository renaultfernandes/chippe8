#pragma once

#include <stdint.h>
#include <SDL2/SDL.h>
#include <iostream>

#define NUM_KEYS 16

class Input {

public:
  static Input& instance()
  {
    static Input* instance = new Input();
    return *instance;
  }

private:
  bool pressed[NUM_KEYS] = {false};

  Input() {}
  void toggleKey(uint8_t keyCode);

public:
  bool isPressed(uint8_t keyCode);
  void pressKey(uint8_t keyCode);
  void unpressKey(uint8_t keyCode);
  void handleInput(SDL_Event event, bool keyDown);
};
