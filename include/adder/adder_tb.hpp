#ifndef __ADDER_TB
#define __ADDER_TB

#include <systemc.h>

#include "adder/adder.hpp"
#include <iostream>
#include <iomanip>

SC_MODULE (adder_tb) {
    sc_out<sc_int<SIZE>> A, B;
    sc_out<bool> Cin;
    sc_in<sc_int<SIZE>> C;
    sc_in<bool> Cout;   

    void aciona();
    
    SC_CTOR (adder_tb) {
        SC_THREAD(aciona);
    }

};

#endif