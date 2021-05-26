//
// Created by Ricardo Jacobi on 25/04/21.
//

#ifndef RISCV_PIPE_ALU_CONTROL_H
#define RISCV_PIPE_ALU_CONTROL_H

#include <systemc.h>
#include "top/macros.hpp"

SC_MODULE(aluControl) {
    sc_in< bool > ex_funct7;
    sc_in< sc_uint<3> > ex_funct3;
    sc_in< bool > alu_op;
    sc_out< sc_uint<4> > opcode_alu;

    void proc(void);

    SC_CTOR(aluControl) {
        SC_METHOD(proc);
        sensitive << ex_funct7 << ex_funct3 << alu_op;
    }
};


#endif //RISCV_PIPE_ALU_CONTROL_H
