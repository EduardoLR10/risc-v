#ifndef __SIGNALS_H__
#define __SIGNALS_H__

#include <systemc.h>
#include "top/macros.hpp"

sc_signal< sc_uint<SIZE> > PC_INC;

sc_signal< sc_uint<SIZE> >
        // Fetch stage
        pc,                     // riscv pc
        pc_in,                  // pc input, from mux
        next_pc,                // output of pc adder
        pc_branch,              // output of branch adder
        ft_instruction,         // output of instruction
        // Decode stage
        jump_addr,              // (PC or BREG[rs1]) + Imm32
        id_pc,                  // pc in decode stage
        id_instruction,         // instruction memory output
        id_imm_ws,              // immediate generated at IF/ID
        breg_ra,                // first breg output - a
        breg_rb,                // second breg output - b

sc_signal< sc_uint<7> >
        id_ins_code;            // opcode of RV instruction

sc_signal< sc_uint<WSIZE> >
        // Execute stage
        ex_ra,                  // breg a output at execution stage
        ex_rb,                  // breg b output at execution stage
        ex_imm,                 // immediate at execution stage
        mux_alu_a,              // ALU input A
        mux_alu_b,              // ALU input B
        alu_out,                // ALU output
        // Memory stage
        mem_alu_out,            // ALU output at memory stage
        mem_mux_alu_a,          // ALU input B at mem stage
        mem_mux_alu_b,          // ALU input B at mem stage
        dm_out,                 // Data memory output
        // Writeback stage
        wb_md_out,              // Data mem ouput at writeback stage
        wb_alu_out,             // ALU out at writeback stage
        wb_mux_data;            // Writeback data

sc_signal< sc_uint<5> >
        // Decode stage
        id_rs1,                 // rs1 instruction field in IF/ID
        id_rs2,                 // rs2 instruction field in IF/ID
        id_rd,                  // rd instruction field in IF/ID
        // Execute stage
        ex_rs1,                 // rs1 field in execute stage
        ex_rs2,                 // rs2 field in execute stage
        ex_rd,                  // rd  field in execute stage
        // Memory stage
        mem_rd,                 // rd field in memory stage
        // Memory stage
        wb_rd;                  // rd field in memory stage


        // Control Signals

        // Fetch -----------------------------------------------------------
sc_signal< bool > sel_mux_pc;       // select pc input
sc_signal<bool>
        wren_reg_ID,                // enable write on reg IF/ID - hazard_rv
        rst_reg_ID,                 // reset reg_ID
        wren_pc;                    // enable write PC

        // Decode ----------------------------------------------------------
sc_signal< sc_uint<2> >
        id_wb_cntr,
        b_opcode;                   // 0: beq  1: bne  2: blt  3: bge
sc_signal< sc_uint<5> >
        id_ex_cntr;
sc_signal< sc_uint<3> >
        id_mem_cntr;
sc_signal<bool>
        b_cond,                     // condition for branch (output dbranch)
        is_jal,                     // identifies jal and jalr
        is_jalr,                    //
        is_branch,                  // identifies branches
        id_flush,                   // insert bubble at decode stage
        wren_breg;                  // enable write on breg

        // Execute ---------------------------------------------------------
sc_signal< bool >
        sel_alu_B,                  // select ALU B input
                                    // 0: ex_rb; 1: ex_imm
        ex_flush;                   // insert bubble at execute stage

sc_signal< sc_uint<2> >
        sel_alu_A;                  // select ALU A input
                                    // 0: zero; 1: ex_pc; 2: ex_ra

sc_signal< bool >
        alu_op;                     // instruction type:
                                    // 0: memory access
                                    // 1: arith-logic operations
        // Memory ----------------------------------------------------------
sc_signal< sc_uint<2> >
        mem_data_size;              // 0: byte, 1: half, 2: word
sc_signal< bool >
        mem_rw;                     // 0: read, 1: write

        // WriteBack -------------------------------------------------------
sc_signal< bool >
        wb_sel_mux;                  // 0: memory, 1: ALU
        
#endif //__SIGNALS_H__
