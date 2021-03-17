#ifndef __GENIMM32_TB
#define __GENIMM32_TB

#include <systemc.h>
#include <iostream>
#include <iomanip>
#include "top/macros.hpp"

SC_MODULE (genImm32_tb) {
    sc_out<sc_int<SIZE>> instruction;
    sc_in<sc_int<SIZE>> imm;                

    void aciona();
    
    SC_CTOR (genImm32_tb) {
        SC_THREAD(aciona);
    }
};

#endif