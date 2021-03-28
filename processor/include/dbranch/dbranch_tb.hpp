#ifndef __DBRANCH_TB__
#define __DBRANCH_TB__

#include <systemc.h>
#include <iostream>
#include <iomanip>
#include "top/macros.hpp"

SC_MODULE (dbranch_tb) {
    sc_out< sc_int<SIZE> > ra, rb;
    sc_out< sc_bv<2>> opcode;
    sc_in<bool> Bout; 

    void aciona();

    SC_CTOR(dbranch_tb) {
        SC_THREAD(aciona);
    }
};

#endif
