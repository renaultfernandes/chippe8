#include "chippe8.hpp"
#include <iostream>

int main(int argc, char** argv)
{
  if (argc <= 1) {
    std::cout << "Usage: " << argv[0] << " <game_file> " << std::endl;
  }
  else {
    Chippe8 chippe8;
    chippe8.loadGame(argv[1]);
    chippe8.run();
  }
}
