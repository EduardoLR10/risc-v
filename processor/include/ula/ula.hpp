#ifndef ULA_H
#define ULA_H

#include <systemc.h>
#include "top/macros.hpp"


SC_MODULE(ula)
{
  sc_in< sc_uint<SIZE> > a, b;
  sc_in< sc_uint<4> > ula_op;
  sc_out< sc_uint<SIZE> > z;
  sc_out<bool> zero;

  SC_CTOR(ula)
  {
    SC_METHOD(proc);
    sensitive << a << b << ula_op;
    SC_METHOD(check_zero);
    sensitive << z;
  }

  void proc();
  void check_zero();
};

#endif