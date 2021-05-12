#include <systemc.h>
#include "riscv/riscv.hpp"
#include "macros.hpp"

SC_MODULE(topRISCV)
{
  RISCV processor;

  sc_clock clk;
  
  SC_CTOR(topRISCV) : processor("RISCV"), clk("clk", 10.0, SC_NS)
  {
    processor.clock(clk);
  }

};