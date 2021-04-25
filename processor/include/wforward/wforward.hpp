#ifndef __WFORWARD__
#define __WFORWARD__

#include <systemc.h>
#include "top/macros.hpp"

SC_MODULE (wforward) {
    sc_in< sc_uint<5> > rs1, rs2, rd;
    sc_out<bool> rAOut, rBOut;

    void proc(void);

    SC_CTOR(wforward) {
        SC_METHOD(proc);
        sensitive << rs1 << rs2 << rd;
    }
};

#endif
