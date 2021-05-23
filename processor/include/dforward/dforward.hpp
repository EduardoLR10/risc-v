#ifndef __DFORWARD__
#define __DFORWARD__

#include <systemc.h>
#include "top/macros.hpp"

SC_MODULE (dforward) {
    sc_in< sc_uint<5> > rs1, rs2, rd;
    sc_in< bool > mem_wr_en;
    sc_out<bool> rAOut, rBOut;

    void proc(void);

    SC_CTOR(dforward) {
        SC_METHOD(proc);
        sensitive << rs1 << rs2 << rd;
    }
};

#endif
