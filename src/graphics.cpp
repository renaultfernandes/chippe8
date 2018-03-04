#include "graphics.hpp"

void Graphics::clear()
{
  for (int i = 0; i < RES_X * RES_Y; i++) {
    buffer[i] = 0;
  }
}

uint16_t Graphics::drawSprite(uint8_t x, uint8_t y, uint8_t n, uint8_t *spriteData)
{
  uint8_t pixelFlippedToUnset = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < SPRITE_WIDTH; j++) {
      uint8_t currentPixelIsSet = 0;
      if (buffer[(i + y) * RES_X + (j + x)] == 1) {
        currentPixelIsSet = 1;
      }
      buffer[(i + y) * RES_X + (j + x)] ^= spriteData[i * SPRITE_WIDTH + j];
      if (currentPixelIsSet && buffer[(i + y) * RES_X + (j + x)] == 0) {
        pixelFlippedToUnset = 1;
      }
    }
  }
  return pixelFlippedToUnset;
}
