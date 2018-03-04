#include "input.hpp"

uint8_t Input::isPressed(uint8_t keyCode)
{
  return pressed[keyCode];
}
