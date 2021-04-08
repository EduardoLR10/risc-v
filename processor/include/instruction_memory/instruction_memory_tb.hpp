#ifndef __INSTRUCTION_MEMORY_TB
#define __INSTRUCTION_MEMORY_TB

#include <systemc.h>

#include "instruction_memory/instruction_memory.hpp"
#include <iostream>
#include <iomanip>

SC_MODULE(InstructionMemoryTB)
{
  sc_out<sc_int<8> > address;
  sc_out<bool> clock;
  sc_in<sc_int<32> > out;

  void activate();

  SC_CTOR(InstructionMemoryTB)
  {
    SC_THREAD(activate);
  }
};

#endif