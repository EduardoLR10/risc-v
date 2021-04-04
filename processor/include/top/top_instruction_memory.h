#include <systemc.h>
#include "instruction_memory/instruction_memory.h"
#include "instruction_memory/instruction_memory_tb.h"

SC_MODULE(TopInstructionMemory)
{
  InstructionMemoryTB imtb;
  InstructionMemory im;

  sc_signal<sc_int<8>> address;
  sc_signal<bool> clock;
  sc_signal<sc_int<32>> out;

  SC_CTOR(TopInstructionMemory) : imtb("InstructionMemoryTB"), im("InstructionMemory")
  {
    imtb.address(address);
    imtb.clock(clock);
    imtb.out(out);

    im.address(address);
    im.clock(clock);
    im.out(out);
    im.load_contents("instruction_memory.bin");
  }
};