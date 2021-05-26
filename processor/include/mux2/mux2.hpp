//
// Created by Ricardo Jacobi on 19/03/21.
//

#ifndef MUX2_HPP
#define MUX2_HPP

#include "systemc.h"
#include "top/macros.hpp"

template <class T>
SC_MODULE(mux2) {
    sc_in< T > in0, in1;
    sc_in<bool> sel;
    sc_out< T > Z;

    SC_CTOR(mux2) {
        SC_METHOD(exec);
        sensitive << in0 << in1 << sel;
    }

    void exec() {
        Z.write(sel.read() ? in1.read() : in0.read());
    }
};
#endif //RISCV_PIPE_MUXES_H
