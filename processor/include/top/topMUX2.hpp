#include <systemc.h>
#include "mux/mux.hpp"
#include "mux/mux_tb.hpp"

SC_MODULE ( topMUX2 ) {

    mux_tb<2> MUX_tb;
    mux<2> MUX;

    sc_vector<sc_signal<sc_int<SIZE>>> inputs{"inputs", 2};
    sc_signal<int> sel;
    sc_signal<sc_int<SIZE>> Z;

    SC_CTOR ( topMUX2 ) : MUX_tb("MUX_tb"), MUX("MUX") {
        MUX.inputs.at(0)(inputs.at(0)); MUX_tb.inputs.at(0)(inputs.at(0));
        MUX.inputs.at(1)(inputs.at(1)); MUX_tb.inputs.at(1)(inputs.at(1));
        MUX.sel(sel); MUX_tb.sel(sel);
        MUX.Z(Z); MUX_tb.Z(Z);
    }
};