#ifndef __DBRANCH__
#define __DBRANCH__

#include <systemc.h>
#include "top/macros.hpp"

SC_MODULE (dbranch) {
    sc_in< sc_uint<SIZE> > ra, rb;
    sc_in< sc_uint<2>> opcode;
    sc_out<bool> Bout;      

    void proc(void);

    SC_CTOR(dbranch) {
        SC_METHOD(proc);
        sensitive << ra << rb << opcode;
    }
};

#endif
