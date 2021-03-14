#include <systemc.h>
#include "ula.hpp"
#include "ula_tb.hpp"

SC_MODULE ( sistema ) {
    ula_tb tb;
    ula u;

    sc_signal< sc_int<SIZE> > A, B, Z;
    sc_signal< sc_uint<4> > opcode;
    sc_signal< bool > zero;

    SC_CTOR ( sistema ) : tb("tb"), u("u") {
        u.opcode(opcode); tb.opcode(opcode);
        u.A(A); tb.A(A);
        u.B(B); tb.B(B);
        u.Z(Z); tb.Z(Z);
        u.zero(zero); tb.zero(zero);
    }
};