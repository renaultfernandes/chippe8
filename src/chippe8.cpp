#include "chippe8.hpp"
#include <fstream>
#include <iostream>
#include <chrono>
#include <thread>

void Chippe8::run()
{
  auto msPerFrame = std::chrono::milliseconds(MS_PER_FRAME);
  while (true) {
    auto startTime = std::chrono::steady_clock::now();

    cpu.runStep();
    timer.tick();
    graphics.render();

    auto endTime = std::chrono::steady_clock::now();
    std::this_thread::sleep_for(startTime + msPerFrame - endTime);
  }
}

void Chippe8::reset()
{
  memory.reset();
  timer.reset();
}

void Chippe8::loadGame(const std::string& path)
{
  std::ifstream gameFile(path.c_str(), std::ios::binary);

  // Get the filesize of the game
  gameFile.seekg(0, gameFile.end);
  int fileSize = gameFile.tellg();
  gameFile.seekg(0, gameFile.beg);

  // Read the game file
  char* buffer = new char[fileSize];
  gameFile.read(buffer, fileSize);

  memory.reset();

  // Load the game file to the memory
  for (uint16_t i = 0; i < fileSize; i++) {
    memory.set(i + PROGRAM_START_ADDRESS, buffer[i]);
  }
}

void Chippe8::dumpState()
{
  std::cout << "Chippe8 State" << std::endl;
  memory.dump();
}
