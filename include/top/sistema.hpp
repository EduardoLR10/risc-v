#include <systemc.h>
#include "ula/ula.hpp"
#include "ula/ula_tb.hpp"
#include "adder/adder.hpp"
#include "adder/adder_tb.hpp"

SC_MODULE ( sistema ) {
/*     ula_tb ULA_tb;
    ula ULA;

    sc_signal< sc_int<SIZE> > A_ULA, B_ULA, Z_ULA;
    sc_signal< sc_uint<4> > opcode_ULA;
    sc_signal< bool > zero_ULA; */

    adder_tb ADDER_tb;
    adder ADDER;

    sc_signal< sc_int<SIZE> > A_ADDER, B_ADDER, C_ADDER;
    sc_signal< bool > Cin_ADDER, Cout_ADDER;

    SC_CTOR ( sistema ) : ADDER_tb("ADDER_tb"), ADDER("ADDER") {
        ADDER.A(A_ADDER); ADDER_tb.A(A_ADDER);
        ADDER.B(B_ADDER); ADDER_tb.B(B_ADDER);
        ADDER.C(C_ADDER); ADDER_tb.C(C_ADDER);
        ADDER.Cin(Cin_ADDER); ADDER_tb.Cin(Cin_ADDER);
        ADDER.Cout(Cout_ADDER); ADDER_tb.Cout(Cout_ADDER);
    }

    /* SC_CTOR ( sistema ) : ULA_tb("ULA_tb"), ULA("ULA") {
        ULA.opcode(opcode_ULA); ULA_tb.opcode(opcode_ULA);
        ULA.A(A_ULA); ULA_tb.A(A_ULA);
        ULA.B(B_ULA); ULA_tb.B(B_ULA);
        ULA.Z(Z_ULA); ULA_tb.Z(Z_ULA);
        ULA.zero(zero_ULA); ULA_tb.zero(zero_ULA);
    } */
};