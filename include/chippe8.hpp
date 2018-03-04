#pragma once

#include "cpu.hpp"
#include "memory.hpp"
#include "timer.hpp"
#include <string>

#define PROGRAM_START_ADDRESS 512

class Chippe8 {

  Cpu& cpu;
  Memory& memory;
  Timer& timer;

 public:
  Chippe8() : cpu(Cpu::instance()), memory(Memory::instance()), timer(Timer::instance()) {}
  void loadGame(const std::string& path);
  void run();
  void reset();
  void dumpState();
};
