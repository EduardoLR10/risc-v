#include <systemc.h>
#include "instruction_memory/instruction_memory.h"
#include "instruction_memory/instruction_memory_tb.hpp"

#include TESTFILE "test.bin"

SC_MODULE(TopInstructionMemory)
{
  InstructionMemoryTB imtb;
  InstructionMemory im;

  sc_signal<sc_int<8>> address;
  sc_signal<bool> clock;
  sc_signal<sc_int<32>> out;

  SC_CTOR(TopInstructionMemory) : InstructionMemoryTB("InstructionMemoryTB"), InstructionMemory("InstructionMemory")
  {
    InstructionMemoryTB.address(address);
    InstructionMemory.address(address);
    InstructionMemoryTB.clock(clock);
    InstructionMemory.clock(clock);
    InstructionMemoryTB.out(out);
    InstructionMemory.out(out);
    InstructionMemory.load_contents(TESTFILE);
  }
};