#include "adder/adder.hpp"

void adder::proc() {
	sc_int<SIZE> a, b;
    sc_int<SIZE + 1> c;
    bool c_in;

	a = A.read();
	b = B.read();
    c_in = Cin.read();

    c = ((false,a)) + (sc_uint<SIZE>)((false,b)) + (sc_uint<SIZE>)((sc_int<SIZE>(0),c_in));

	C.write((c(SIZE - 1, 0)).to_uint());
	Cout.write(c[SIZE]);
}
