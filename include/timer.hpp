#pragma once

#include <stdint.h>

class Timer {

public:
  static Timer& instance()
  {
    static Timer* instance = new Timer();
    return *instance;
  }

private:
  Timer() {}
  uint8_t delay;
  uint8_t sound;

public:
  void tick();
  uint8_t getDelay();
  void setDelay(uint8_t value);
  uint8_t getSound();
  void setSound(uint8_t value);
  void reset();
};
