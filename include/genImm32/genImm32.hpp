#ifndef __GENIMM__
#define __GENIMM__

#include <systemc.h>
#include "top/macros.hpp"

SC_MODULE (genImm32) {
  sc_in<sc_int<SIZE>> instruction;       // inputs
  sc_out<sc_int<SIZE>> imm;         // output

  void proc(void);

  SC_CTOR(genImm32) {
    SC_METHOD(proc);
    sensitive << instruction;
  }
};

#endif
