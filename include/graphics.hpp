#pragma once

#include <stdint.h>
#include <SDL2/SDL.h>

#define RES_X 64
#define RES_Y 32
#define SPRITE_WIDTH 8

class Graphics {

public:
  static Graphics& instance()
  {
    static Graphics* instance = new Graphics();
    return *instance;
  }

private:
  Graphics()
  {
    sdl_init();
  }

  ~Graphics()
  {
    sdl_destroy();
  }

  uint8_t buffer[RES_X * RES_Y];
  SDL_Renderer* renderer;
  SDL_Window* window;

  void sdl_init();
  void sdl_destroy();

public:
  void clear();
  uint16_t drawSprite(uint8_t x, uint8_t y, uint8_t n, uint8_t* spriteData);
  void render();
};
