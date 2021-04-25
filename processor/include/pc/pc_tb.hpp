#ifndef __PC_TB_HPP
#define __PC_TB_HPP

#include <systemc.h>

#include "pc/pc.hpp"
#include <iostream>
#include <iomanip>

SC_MODULE (pc_tb) {
  sc_in<sc_uint<32>> pc_out;

  sc_out<sc_uint<32>> pc_in;
  sc_out<bool> ld_pc;
  sc_out<bool> clock;

  void activate();

  SC_CTOR (pc_tb) {
      SC_THREAD(activate);
  }

};

#endif