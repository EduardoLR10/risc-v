#ifndef __MUX__
#define __MUX__

#include <systemc.h>
#include "top/macros.hpp"

template <int N>
SC_MODULE (mux) {
	sc_vector<sc_in<sc_int<SIZE>>> inputs{"inputs", N};
	sc_in<sc_bv<N - 1>> sel;
	sc_out<sc_int<SIZE>> Z;

	void proc();

	SC_CTOR(mux){
		SC_METHOD(proc);
		if(inputs.size() == 3){
			sensitive << sel << inputs.at(0) << inputs.at(1) << inputs.at(2);
		} else {
			sensitive << sel << inputs.at(0) << inputs.at(1);
		}
	}

};

template <int N>
void mux<N>::proc() {
    sc_int<SIZE> z = inputs.at(sel.read().to_uint()).read();
	Z.write(z);
}

#endif
