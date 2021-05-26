#ifndef MUX3_HPP
#define MUX3_HPP

#include "systemc.h"
#include "top/macros.hpp"

template <class T>
SC_MODULE(mux3)
{
  sc_in<T> in0, in1, in2;
  sc_in<sc_uint<2>> sel;
  sc_out<T> Z;

  SC_CTOR(mux3)
  {
    SC_METHOD(exec);
    sensitive << in0 << in1 << in2 << sel;
  }

  void exec()
  {
    T i0 = in0.read(), i1 = in1.read(), i2 = in2.read(), outw = 0;

    switch (sel.read())
    {
    case 0:
      outw = i0;
      break;
    case 1:
      outw = i1;
      break;
    default:
      outw = i2;
      break;
    }
    Z.write(outw);
  }
};

#endif