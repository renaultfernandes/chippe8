#include "input.hpp"
#include <SDL2/SDL.h>
#include <iostream>

bool Input::isPressed(uint8_t keyCode)
{
  return pressed[keyCode];
}

void Input::toggleKey(uint8_t keyCode)
{
  std::cout << "Ts Key code " << uint16_t(keyCode) << " = " << (isPressed(keyCode) ? 1 : 0) << std::endl;
  pressed[keyCode] = !pressed[keyCode];
  std::cout << "Te Key code " << uint16_t(keyCode) << " = " << (isPressed(keyCode) ? 1 : 0) << std::endl;
}

void Input::pressKey(uint8_t keyCode)
{
  pressed[keyCode] = true;
}

void Input::unpressKey(uint8_t keyCode)
{
  pressed[keyCode] = false;
}

void Input::handleInput(SDL_Event event, bool keyDown)
{
  switch (event.key.keysym.sym) {
  case SDLK_1:
    toggleKey(0x1);
    std::cout << "Pressed key 1" << (isPressed(0x1) ? 1 : 0) << std::endl;
    break;
  case SDLK_2:
    toggleKey(0x2);
    break;
  case SDLK_3:
    toggleKey(0x3);
    break;
  case SDLK_q:
    toggleKey(0x4);
    break;
  case SDLK_w:
    toggleKey(0x5);
    break;
  case SDLK_e:
    toggleKey(0x6);
    break;
  case SDLK_a:
    toggleKey(0x7);
    break;
  case SDLK_s:
    toggleKey(0x8);
    break;
  case SDLK_d:
    toggleKey(0x9);
    break;
  case SDLK_z:
    toggleKey(0xA);
    break;
  case SDLK_x:
    toggleKey(0x0);
    break;
  case SDLK_c:
    toggleKey(0xb);
    break;
  case SDLK_4:
    toggleKey(0xc);
    break;
  case SDLK_r:
    toggleKey(0xd);
    break;
  case SDLK_f:
    toggleKey(0xe);
    break;
  case SDLK_v:
    toggleKey(0xf);
    break;
  }
}
