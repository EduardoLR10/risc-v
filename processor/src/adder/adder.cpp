#include "adder/adder.hpp"

void adder::proc() {
	sc_int<SIZE> a, b;

	a = A.read();
	b = B.read();

	Z.write(a + b);
}
