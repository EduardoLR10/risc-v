#include <systemc.h>
#include "instruction_memory/instruction_memory.hpp"
#include "instruction_memory/instruction_memory_tb.hpp"

SC_MODULE(TopInstructionMemory)
{
  InstructionMemoryTB imtb;
  InstructionMemory im;

  sc_signal<sc_uint<32>> address;
  sc_signal<sc_uint<32>> out;

  SC_CTOR(TopInstructionMemory) : imtb("InstructionMemoryTB"), im("InstructionMemory")
  {
    imtb.address(address);
    imtb.out(out);

    im.address(address);
    im.out(out);
    im.load_contents("instruction_memory.bin");
  }
};