#pragma once

#include <stdint.h>

#define MEMORY_SIZE 4096

class Memory {

public:
  static Memory& instance()
  {
    static Memory* instance = new Memory();
    return *instance;
  }

private:
  Memory()
  {
    init();
  }

  void init();
  uint8_t memory[MEMORY_SIZE];

public:
  uint8_t read(const uint16_t address);
  uint8_t* readN(const uint16_t address, uint16_t n);
  void set(const uint16_t address, const uint8_t value);
  void reset();
  void dump();
};
