#ifndef __GENIMM32__
#define __GENIMM32__

#include <systemc.h>
#include "top/macros.hpp"

SC_MODULE (genImm32) {
  sc_in<sc_uint<SIZE>> instruction;       // inputs
  sc_out<sc_uint<SIZE>> imm;         // output

  void proc(void);

  SC_CTOR(genImm32) {
    SC_METHOD(proc);
    sensitive << instruction;
  }
};

#endif
