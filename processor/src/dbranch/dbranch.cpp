#include "dbranch/dbranch.hpp"

void dbranch::proc() {
	sc_int<SIZE> a, b;
    sc_bv<3> op;

	a = ra.read();
	b = rb.read();
    op = opcode.read();

    switch(op.to_uint()){
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
        // case NO_BRANCH:
        default:
            Bout.write(false);
            break;
    }

}
