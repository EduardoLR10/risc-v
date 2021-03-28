#ifndef __MUX_TB
#define __MUX_TB

#include <systemc.h>
#include <iostream>
#include <iomanip>
#include "top/macros.hpp"

template <class T, int N>
SC_MODULE (mux_tb) {
    sc_vector<sc_out<T>> inputs{"inputs", N};
    sc_out<int> sel;
    sc_in<T> Z;   

    void aciona();

    SC_CTOR(mux_tb){
		SC_THREAD(aciona);
	}

};

template <class T, int N>
void mux_tb<T, N>::aciona() {
    inputs.at(0) = 0x0000ffff;
    inputs.at(1) = 0xffff0000;
    if(N == 3){
        inputs.at(2) = 0x0f0f0f0f;
    }
    sel = 1;
    wait(1, SC_NS);
    std::cout << "Mux 0 = " << std::setw(W) << std::hex << inputs.at(0).read() << std::endl;
    std::cout << "Mux 1 = " << std::setw(W) << inputs.at(1).read() << std::endl;
    if(N == 3){
        std::cout << "Mux 2 = " << std::setw(W) << inputs.at(2).read() << std::endl;
    }
    std::cout << "Sel = " << std::setw(W) << sel.read() << std::endl;
    std::cout << "Z = " << std::dec << Z.read() << std::endl << std::endl;

}

#endif