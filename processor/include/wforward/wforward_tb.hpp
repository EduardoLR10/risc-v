#ifndef __WFORWARD_TB__
#define __WFORWARD_TB__

#include <systemc.h>
#include "top/macros.hpp"
#include <string>
#include <iomanip>

SC_MODULE (wforward_tb) {
    sc_out< sc_uint<5> > rs1, rs2, rd;
    sc_in<bool> rAOut, rBOut;

    void aciona();

    SC_CTOR(wforward_tb) {
        SC_THREAD(aciona);
    }
};

#endif
