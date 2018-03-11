#include "graphics.hpp"
#include <iostream>
#include <SDL2/SDL.h>

void Graphics::clear()
{
  for (int i = 0; i < RES_X * RES_Y; i++) {
    buffer[i] = 0;
  }
}

uint16_t Graphics::drawSprite(uint8_t x, uint8_t y, uint8_t n, uint8_t *spriteData)
{
  uint8_t collisionDetected = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < SPRITE_WIDTH; j++) {
      if (spriteData[i] & (0x80 >> j)) {
        collisionDetected = buffer[(y + i) * RES_X + (x + j)];
        buffer[(y + i) * RES_X + (x + j)] ^= 1;
      }
    }
  }
  return collisionDetected;
}

void Graphics::sdl_init()
{
  SDL_Init(SDL_INIT_VIDEO);
  SDL_CreateWindowAndRenderer(RES_X, RES_Y, 0, &window, &renderer);
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
}

void Graphics::sdl_destroy()
{
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
}

void Graphics::render()
{
  SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
  SDL_RenderClear(renderer);
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  for (int i = 0; i < RES_Y; i++) {
    for (int j = 0; j < RES_X; j++) {
      if (buffer[i * RES_X + j] == 1) {
        SDL_RenderDrawPoint(renderer, j, i);
      }
    }
  }
  SDL_RenderPresent(renderer);
}
