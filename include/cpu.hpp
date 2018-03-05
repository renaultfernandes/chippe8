#pragma once

#include "memory.hpp"
#include "graphics.hpp"
#include "input.hpp"
#include "timer.hpp"
#include <stdint.h>
#include <cstdlib>
#include <ctime>

#define NUM_REGS 16
#define NUM_STACK_LEVELS 16

class Cpu {

public:
  static Cpu& instance()
  {
    static Cpu* instance = new Cpu();
    return *instance;
  }

private:
  uint8_t v[NUM_REGS];
  uint16_t pc;
  uint16_t ri;
  uint16_t stack[NUM_STACK_LEVELS];
  uint16_t sp;
  uint16_t instr;

  Memory& memory;
  Graphics& graphics;
  Input& input;
  Timer& timer;

  Cpu() : memory(Memory::instance()), graphics(Graphics::instance()), input(Input::instance()), timer(Timer::instance())
  {
    // Initialize the random number generator (used in instr opcode 0xCXNN)
    srand(time(0));
  }

  uint16_t fetchInstr();
  void executeInstr();
  void throwUnrecognizedInstr();

public:
  void runStep();
  void dumpState();
};
