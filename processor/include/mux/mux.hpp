#ifndef __MUX__
#define __MUX__

#include <systemc.h>
#include "top/macros.hpp"

template <int N>
SC_MODULE (mux) {
	sc_vector<sc_in<sc_int<SIZE>>> inputs{"inputs", N};
	sc_in<int> sel;
	sc_out<sc_int<SIZE>> Z;

	void proc();

	SC_CTOR(mux){
		SC_METHOD(proc);
		sensitive << sel;
		for(int i = 0; i < (int)inputs.size(); i++){
			sensitive << inputs.at(i);
		}
	}

};

template <int N>
void mux<N>::proc() {
    sc_int<SIZE> z = inputs.at(sel.read()).read();
	Z.write(z);
}

#endif
