#ifndef __MFORWARD_H
#define __MFORWARD_H

#include <systemc.h>
#include "top/macros.hpp"

SC_MODULE(MForward) {
  sc_in<sc_uint<5>> mem_rs2;
  sc_in<sc_uint<5>> wb_rd;
  sc_in<bool> f_breg_wr;
  sc_out<bool> sel_mux_mem;

  void proc();

  SC_CTOR(MForward) {
    SC_METHOD(proc);
    sensitive << mem_rs2 << wb_rd << f_breg_wr;
  }
};

#endif
