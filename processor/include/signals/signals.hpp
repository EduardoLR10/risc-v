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
        // Execute stage
        ex_ra,                  // breg a output at execution stage
        ex_rb,                  // breg b output at execution stage
        mux_alu_a,              // ALU input A
        mux_alu_b,              // ALU input B
        alu_out,                // ALU output
        // Memory stage
        mem_alu_out,            // ALU output at memory stage
        mem_mux_alu_b,          // ALU input B at mem stage
        dm_out,                 // Data memory output
        // Writeback stage
        wb_md_out,              // Data mem ouput at writeback stage
        wb_alu_out,             // ALU out at writeback stage
        wb_mux_data;            // Writeback data

sc_signal< sc_uint<5> >
        // Decode stage
        id_ra,                  // breg ra instruction field
        id_rb,                  // breg rb instruction field
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

sc_signal< sc_uint<2> >
        sel_mux_pc;             // select pc input
        
#endif //__SIGNALS_H__
