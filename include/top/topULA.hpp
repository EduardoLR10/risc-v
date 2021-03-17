#include <systemc.h>
#include "ula/ula.hpp"
#include "ula/ula_tb.hpp"

SC_MODULE ( topULA ) {
    ula_tb ULA_tb;
    ula ULA;

    sc_signal< sc_int<SIZE> > A_ULA, B_ULA, Z_ULA;
    sc_signal< sc_uint<4> > opcode_ULA;
    sc_signal< bool > zero_ULA;

    SC_CTOR ( topULA ) : ULA_tb("ULA_tb"), ULA("ULA") {
        ULA.opcode(opcode_ULA); ULA_tb.opcode(opcode_ULA);
        ULA.A(A_ULA); ULA_tb.A(A_ULA);
        ULA.B(B_ULA); ULA_tb.B(B_ULA);
        ULA.Z(Z_ULA); ULA_tb.Z(Z_ULA);
        ULA.zero(zero_ULA); ULA_tb.zero(zero_ULA);
    }
};