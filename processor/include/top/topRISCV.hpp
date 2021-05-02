#include <systemc.h>
#include "riscv/riscv.hpp"
#include "macros.hpp"

SC_MODULE(topRISCV)
{
  RISCV processor;

  sc_clock clk;
  
  SC_CTOR(topRISCV) : processor("RISCV"), clk("clk", 10.0, SC_NS)
  {
    SC_THREAD(Up);
    sensitive << clk.negedge_event();
    SC_METHOD(Down);
    sensitive << clk.posedge_event();
  }

  void Up(){}

  void Down(){}

};