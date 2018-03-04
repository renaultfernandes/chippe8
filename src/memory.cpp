#include "memory.hpp"
#include <string>
#include <iostream>
#include <iomanip>

uint8_t Memory::read(const uint16_t address)
{
  return memory[address];
}

uint8_t* Memory::readN(const uint16_t address, uint16_t n)
{
  uint8_t* buffer = new uint8_t[n];
  for (uint16_t i = 0; i < n; i++) {
    buffer[i] = memory[address + i];
  }
  return buffer;
}

void Memory::set(const uint16_t address, const uint8_t value)
{
  memory[address] = value;
}

void Memory::reset()
{
  std::fill_n(memory, MEMORY_SIZE, 0);
}

void Memory::dump()
{
  std::cout << "Memory dump" << std::endl;
  for (uint16_t i = 0; i < MEMORY_SIZE; i++) {
    std::cout << std::hex << memory[i];
  }
}
