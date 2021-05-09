#include "dbranch/dbranch.hpp"

void dbranch::proc() {
	sc_int<SIZE> a, b;

	a = ra.read();
	b = rb.read();

    switch(opcode.read()){
        case BEQ:
            Bout.write(a == b);
            break;
        case BNE:
            Bout.write(a != b);
            break;
        case BLT:
            Bout.write(a < b);
            break;
        case BGE:
            Bout.write(a >= b);
            break;
    }

}
