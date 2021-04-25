#include <systemc.h>
#include "pc/pc.hpp"
#include "pc/pc_tb.hpp"

SC_MODULE(TopPC)
{
  pc_tb pctb;
  pc pc_instance;

  // sc_in<sc_uint<32>> pc_in;
  // sc_in<bool> ld_pc;
  // sc_in<bool> clock;
  // sc_out<sc_uint<32>> pc_out;

  sc_signal<sc_uint<32>> pc_in;
  sc_signal<bool> ld_pc;
  sc_signal<bool> clock;
  sc_signal<sc_uint<32>> pc_out;

  SC_CTOR(TopPC) : pctb("pc_tb"), pc_instance("pc")
  {
    pctb.pc_in(pc_in);
    pctb.ld_pc(ld_pc);
    pctb.clock(clock);
    pctb.pc_out(pc_out);

    pc_instance.pc_in(pc_in);
    pc_instance.ld_pc(ld_pc);
    pc_instance.clock(clock);
    pc_instance.pc_out(pc_out);
  }
};