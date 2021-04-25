#ifndef __MUX__
#define __MUX__

#include <systemc.h>
#include "top/macros.hpp"

template <class T, int N>
SC_MODULE (mux) {
	sc_vector<sc_in<T>> inputs{"inputs", N};
	sc_in<int> sel;
	sc_out<T> Z;

	void proc();

	SC_CTOR(mux){
		SC_METHOD(proc);
		sensitive << sel;
		for(int i = 0; i < (int)inputs.size(); i++){
			sensitive << inputs.at(i);
		}
	}

};

template <class T, int N>
void mux<T, N>::proc() {
    T z = inputs.at(sel.read()).read();
	Z.write(z);
}

#endif
