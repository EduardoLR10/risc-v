#ifndef __PC_HPP
#define __PC_HPP

#include <systemc.h>
#include "top/macros.hpp"

SC_MODULE(pc) {
  sc_in<sc_uint<32>> pc_in;
  sc_in<bool> ld_pc;
  sc_in<bool> clock;
  sc_out<sc_uint<32>> pc_out;

  sc_uint<32> count;

  void proc(void);

  SC_CTOR(pc) {
    SC_METHOD(proc);
    sensitive << clock.pos();
    // count = 0;
  }
};

#endif
