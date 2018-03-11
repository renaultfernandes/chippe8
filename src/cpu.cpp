#include "cpu.hpp"
#include "fonts.hpp"
#include <iostream>
#include <sstream>

void Cpu::reset()
{
  for (int i = 0; i < NUM_REGS; i++) {
    v[i] = 0;
  }
  for (int i = 0; i < NUM_STACK_LEVELS; i++) {
    stack[i] = 0;
  }
  pc = PROGRAM_START_ADDRESS;
  ri = sp = 0;

  // Initialize the random number generator (used in instr opcode 0xCXNN)
  srand(time(0));
}

void Cpu::runStep()
{
  instr = fetchInstr();
  try {
    executeInstr();
  }
  catch (std::string ex) {
    std::cout << "Caught Exception: " << ex << std::endl;
  }

  // dumpState();
  // int32_t x;
  // std::cin >> x;
}

uint16_t Cpu::fetchInstr()
{
  uint16_t b1 = memory.read(pc);
  uint8_t b2 = memory.read(pc + 1);
  pc += 2;

  return (b1 << 8) | b2;
}

void Cpu::executeInstr()
{
  switch ((instr & 0xf000) >> 12) {

  case 0:
    switch (instr & 0x0fff) {
    case 0x0e0: // 00E0 Display clear
      graphics.clear();
      break;

    case 0x0ee: // 00EE Return
      if (sp > 0) { sp--; }
      pc = stack[sp];
    }
    break;

  case 1: // 1NNN Jump to address at NNN
    pc = instr & 0xfff;
    break;

  case 2: // 2NNN Call subroutine at NNN
    stack[sp++] = pc;
    pc = instr & 0xfff;
    break;

  case 3: { // 3XNN Skip the next instr if vX equals NN
    uint8_t x = (instr & 0x0f00) >> 8;
    uint8_t nn = instr & 0x00ff;
    if (v[x] == nn) { pc += 2; }
    break;
  }

  case 4: { // 4XNN Skip the next instr if vX does not equals NN
    uint8_t x = (instr & 0x0f00) >> 8;
    uint8_t nn = instr & 0x00ff;
    if (v[x] != nn) { pc += 2; }
    break;
  }

  case 5: { // 5XY0 Skip the next instr if vX equals vY
    uint8_t x = (instr & 0x0f00) >> 8;
    uint8_t y = (instr & 0x00f0) >> 4;
    if (v[x] == v[y]) { pc += 2; }
    break;
  }

  case 6: { // 6XNN Set vX to NN
    uint8_t x = (instr & 0x0f00) >> 8;
    uint8_t nn = instr & 0x00ff;
    v[x] = nn;
    break;
  }

  case 7: { // 7XNN Add NN to vX
    uint8_t x = (instr & 0x0f00) >> 8;
    uint8_t nn = instr & 0x00ff;
    v[x] += nn;
    break;
  }

  case 8: {
    uint8_t x = (instr & 0x0f00) >> 8;
    uint8_t y = (instr & 0x00f0) >> 4;
    switch (instr & 0x000f) {

    case 0: // 8XY0 Set vX to the value of vY
      v[x] = v[y];
      break;

    case 1: // 8XY1 Set vX to vX OR vY
      v[x] |= v[y];
      break;

    case 2: // 8XY2 Set vX to vX AND vY
      v[x] &= v[y];
      break;

    case 3: // 8XY3 Set vX to vX XOR vY
      v[x] ^= v[y];
      break;

    case 4: // 8XY4 Set vX to vX + vY, set vF if carry
      v[0xF] = v[y] > 0xff - v[x] ? 1 : 0;
      v[x] += v[y];
      break;

    case 5: // 8XY5 Set vX to vX - vY, unset vF if borrow
      v[0xF] = v[y] > v[x] ? 0 : 1;
      v[x] -= v[y];
      break;

    case 6: // 8XY6 Set vX and vY to vY >> 1, vF to lsb of vY
      v[0xf] = v[y] & 0x1;
      v[x] = v[y] = v[y] >> 1;
    break;

    case 7: // 8XY7 Set vX to vY - vX, unset vF if borrow
      v[0xF] = v[x] > v[y] ? 0 : 1;
      v[x] = v[y] - v[x];
      break;

    case 8: // 8XY8 Set vX and vY to vY << 1, vF to msb of vY
      v[0xf] = v[y] >> 7;
      v[x] = v[y] = v[y] << 1;
      break;
    }
    break;
  }

  case 9: { // 9XY0 Skip the next instr if vX is not equal to vY
    uint8_t x = (instr & 0x0f00) >> 8;
    uint8_t y = (instr & 0x00f0) >> 4;
    if (v[x] != v[y]) { pc += 2; }
    break;
  }

  case 0xa: // ANNN Set ri to NNN
    ri = instr & 0x0fff;
    break;

  case 0xb: // BNNN Jump to the address NNN + v0
    pc = (instr & 0x0fff) + v[0];
    break;

  case 0xc: { // CXNN Set vX to rand() AND NN
    uint8_t x = (instr & 0x0f00) >> 8;
    uint8_t nn = instr & 0x00ff;
    v[x] = (rand() % 256) & nn;
    break;
  }

  case 0xd: { // DXYN Draw ri indexed sprite of width 8 and height N at coordinat (X,Y)
    uint8_t x = (instr & 0x0f00) >> 8;
    uint8_t y = (instr & 0x00f0) >> 4;
    uint8_t n = instr & 0x000f;
    uint8_t* spriteData = memory.readN(ri, n);
    v[0xf] = graphics.drawSprite(v[x], v[y], n, spriteData);
    break;
  }

  case 0xe: {
    uint8_t x = (instr & 0x0f00) >> 8;
    switch (instr & 0x00ff) {

    case 0x9e: // EX9E Skip the next instr if the key in vX is pressed
      if (input.isPressed(x)) { pc += 2; }
      break;

    case 0xa1: // EXA1 Skip the next instr if the key in vX is not pressed
      if (!input.isPressed(x)) { pc += 2; }
      break;
    }
    break;
  }

  case 0xf: {
    uint8_t x = (instr & 0x0f00) >> 8;
    switch (instr & 0x00ff) {
    case 0x07: // FX07 Set vX to the value of the delay timer
      v[x] = timer.getDelay();
      break;

    case 0x0a: // FX0A Block until key in vX is pressed
      if (!input.isPressed(v[x])) {
        pc -= 2;
      }
      break;

    case 0x15: // FX15 Set the delay timer to vX
      timer.setDelay(v[x]);
      break;

    case 0x18: // FX18 Set the sound timer to vX
      timer.setSound(v[x]);
      break;

    case 0x1e: // FX1E Add vX to ri
      ri += v[x];
      break;

    case 0x29: // FX29 Set ri to the address of the font for character in vX
      ri = FONTS_START_ADDRESS + (FONT_BYTE_COUNT * v[x]);
      break;

    case 0x33: // FX33 Store the BCD representation of vX at memory locations [ri, ri+1, ri+2]
      memory.set(ri, v[x] / 100);
      memory.set(ri + 1, v[x] / 10 % 10);
      memory.set(ri + 2, v[x] % 10);
      break;

    case 0x55: { // FX55 Dump all register v0-vF to memory location starting at ri
      uint16_t end = ri + NUM_REGS;
      while (ri < end) {
        memory.set(ri, v[ri]);
        ri++;
      }
      break;
    }

    case 0x65: { // FX65 Load registers v0-vF with values from memory starting at ri
      uint16_t end = ri + NUM_REGS;
      while (ri < end) {
        v[ri - (end - NUM_REGS)] = memory.read(ri);
        ri++;
      }
      break;
    }
    }
    break;
  }

  default:
    throwUnrecognizedInstr();
  }
}

void Cpu::throwUnrecognizedInstr()
{
  std::stringstream ss;
  ss << "Unrecognized instruction opcode " << std::hex << instr << std::endl;
  throw ss.str();
}

void Cpu::dumpState()
{
  std::cout << "Executed instr: " << std::hex << instr << std::endl;
  std::cout << "Cpu State:" << std::endl;
  std::cout << "PC=" << std::hex << pc << " I=" << ri << std::endl;
  std::cout << "Registers: ";
  for (uint8_t i = 0; i < NUM_REGS; i++) {
    std::cout << "v[" << std::hex << uint16_t(i) << "]=" << uint16_t(v[i]) << " ";
  }
  std::cout << std::endl;
}
