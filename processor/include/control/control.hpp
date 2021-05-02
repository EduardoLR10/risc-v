//
// Created by Ricardo Jacobi on 29/03/21.
//

#ifndef CONTROL__H
#define CONTROL__H

#include <systemc.h>
#include "top/macros.hpp"

SC_MODULE(control) {
    sc_in< sc_uint<SIZE> > instruction;
    // Fetch
    sc_out<bool> rst_reg_ID;
    // Decode
    sc_out<bool> id_flush;
    sc_out<bool> is_jal, is_jalx, is_jalr, is_branch;
    sc_out< sc_uint<2> > b_code;
    // Execute
    sc_out<bool> ex_flush;
    // ex_ctrl[0-1]: sel_alu_A; ex_ctrl[2]: sel_alu_B; ex_ctrl[3]: alu_op
    sc_out< sc_uint<4> > ex_ctrl;
    // Memory
    // mem_ctrl[0]: read_memory;
    // mem_ctrl[1]: write memory;
    // mem_ctrl[2]: data type: 0-unsigned, 1-signed
    // mem_ctrl[3-4]: size 00-byte 01-half 10-word
    sc_out< sc_uint<5> > mem_ctrl;
    // WriteBack
    // wb_ctrl[0]: wren breg; wb_ctrl[1]: mux_mem
    sc_out< sc_uint<2> > wb_ctrl;

    INSTRUCTIONS get_instr_code(uint32_t, uint32_t, uint32_t);

    void decode();

    SC_CTOR(control): ALU_A_ZERO(0), ALU_A_PC(1), ALU_A_RA(2),
    ALU_B_RB(false),  ALU_B_IMM(true), SEL_MEM_DATA(true), SEL_ALU_DATA(false),
    WRITE_BREG(true), NO_WRITE(false), SIGNED_DATA(true),  UNSIGNED_DATA(false),
    BYTE_SIZE(0),  HALF_SIZE(1), WORD_SIZE(2), NO_READ(0), MEM_READ(true),
    MEM_WRITE(true)
    {
        SC_METHOD(decode);
          sensitive << instruction;
    }
private:
    const sc_uint<2> ALU_A_ZERO = 0; // 0
    const sc_uint<2> ALU_A_PC = 1;   // 1
    const sc_uint<2> ALU_A_RA = 2;      // 2
    const bool ALU_B_RB = false;        // false
    const bool ALU_B_IMM = true;        // true
    const bool NO_WRITE = false;        // false
    const bool NO_READ = false;         // false
    const bool MEM_READ = true;         // true
    const bool MEM_WRITE = true;        // true
    const bool SEL_MEM_DATA = true;     // true
    const bool SEL_ALU_DATA = true;     // false
    const bool WRITE_BREG = true;       // true
    const bool SIGNED_DATA = true;      // true
    const bool UNSIGNED_DATA = false;   // false
    const sc_uint<2> BYTE_SIZE = 0;     // 0
    const sc_uint<2> HALF_SIZE = 1;     // 1
    const sc_uint<2> WORD_SIZE = 2;     // 2
};

#endif //RISCV_PIPE_CONTROL_RV_H
