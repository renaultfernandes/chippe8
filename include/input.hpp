#pragma once

#include <stdint.h>

#define NUM_KEYS 16

class Input {

public:
  static Input& instance()
  {
    static Input* instance = new Input();
    return *instance;
  }

private:
  Input() {}
  uint8_t pressed[NUM_KEYS];

public:
  uint8_t isPressed(uint8_t keyCode);
};
