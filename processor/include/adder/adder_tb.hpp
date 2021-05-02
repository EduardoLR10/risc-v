#ifndef __ADDER_TB
#define __ADDER_TB

#include <systemc.h>
#include <iostream>
#include <iomanip>
#include "top/macros.hpp"

SC_MODULE (adder_tb) {
    sc_out<sc_uint<SIZE>> A, B;
    sc_out<bool> Cin;
    sc_in<sc_uint<SIZE>> C;
    sc_in<bool> Cout;   

    void aciona();
    
    SC_CTOR (adder_tb) {
        SC_THREAD(aciona);
    }

};

#endif