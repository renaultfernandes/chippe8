#pragma once

#include "cpu.hpp"
#include "memory.hpp"
#include "timer.hpp"
#include "graphics.hpp"
#include <string>

#define PROGRAM_START_ADDRESS 512
#define FPS 60
#define MS_PER_FRAME 1000 / FPS

class Chippe8 {

  Cpu& cpu;
  Memory& memory;
  Timer& timer;
  Graphics& graphics;

 public:
  Chippe8() : cpu(Cpu::instance()), memory(Memory::instance()), timer(Timer::instance()), graphics(Graphics::instance()) {}
  void loadGame(const std::string& path);
  void run();
  void reset();
  void dumpState();
};
