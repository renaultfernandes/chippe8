#include "timer.hpp"

void Timer::tick()
{
  delay = delay > 0 ? delay - 1 : 0;
  sound = sound > 0 ? sound - 1 : 0;
}

uint8_t Timer::getDelay()
{
  return delay;
}

void Timer::setDelay(uint8_t value)
{
  delay = value;
}

uint8_t Timer::getSound()
{
  return sound;
}

void Timer::setSound(uint8_t value)
{
  sound = value;
}

void Timer::reset()
{
  delay = 0;
  sound = 0;
}
