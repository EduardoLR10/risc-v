#include <systemc.h>
#include "adder/adder.hpp"
#include "adder/adder_tb.hpp"

SC_MODULE ( topADDER ) {

    adder_tb ADDER_tb;
    adder ADDER;

    sc_signal< sc_int<SIZE> > A_ADDER, B_ADDER, C_ADDER;
    sc_signal< bool > Cin_ADDER, Cout_ADDER;

    SC_CTOR ( topADDER ) : ADDER_tb("ADDER_tb"), ADDER("ADDER") {
        ADDER.A(A_ADDER); ADDER_tb.A(A_ADDER);
        ADDER.B(B_ADDER); ADDER_tb.B(B_ADDER);
        ADDER.C(C_ADDER); ADDER_tb.C(C_ADDER);
        ADDER.Cin(Cin_ADDER); ADDER_tb.Cin(Cin_ADDER);
        ADDER.Cout(Cout_ADDER); ADDER_tb.Cout(Cout_ADDER);
    }
};