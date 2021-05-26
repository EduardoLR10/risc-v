#ifndef __SIGNALS_H__
#define __SIGNALS_H__

#include <systemc.h>
#include "top/macros.hpp"

sc_signal< sc_uint<SIZE> > K_FOUR;

sc_signal<bool> TRUE;
sc_signal<bool> FALSE;
sc_signal<sc_uint<SIZE> > K_ZERO;
sc_signal<sc_uint<SIZE> > K_ONE;


sc_signal< sc_uint<SIZE> >
        // Fetch stage
        program_counter,        // riscv pc
        pc_in,                  // pc input, from mux
        next_pc,                // output of pc adder
        pc_branch,              // output of branch adder
        ft_instruction,         // output of instruction

        // Decode stage
        id_pc,
        id_ra,
        id_rb,
        id_instruction,
        id_imm,
        id_next_pc;

sc_signal< sc_uint<7> >
        id_ins_code;            // opcode of RV instruction

sc_signal< sc_uint<SIZE> >
        // Execute stage
        ex_pc,                  // pc in execute stage
        ex_ra,                  // breg a output at execution stage
        ex_rb,                  // breg b output at execution stage
        ex_imm,                 // immediate at execution stage
        alu_out,                // ALU output
        ex_alu_B,               // ALU input B
        // Memory stage
        mem_alu_out,            // ALU output at memory stage
        mem_mux_alu_b,          // ALU input B at mem stage
        mdata,                  // Mux Mem output
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
        mem_rs2,                // rs2 field in memory stage
        // Memory stage
        wb_rd;                  // rd field in memory stage


sc_signal< sc_uint<3> >
        ex_funct3;              // funct3 in execute stage

sc_signal< bool >
        ex_funct7;              // funct7 in execute stage   

sc_signal< bool >
        // Execute
        zero_alu;

        // Control Signals

        // Fetch -----------------------------------------------------------
sc_signal< bool > sel_mux_pc;       // select pc input
sc_signal<bool> fetch_sel_in;
sc_signal<bool>
        wren_reg_ID,                // enable write on reg IF/ID - hazard_rv
        rst_reg_ID,                 // reset reg_ID
        wren_pc;                    // enable write PC

        // Decode ----------------------------------------------------------
sc_signal< sc_uint<2> >
        ex_wb_ctrl,                 // WB in ID/EX
        ex_to_mem_wb,               // WB from ID/EX to EX/MEM
        mem_to_wb,                  // WB from EX/MEM to MEM/WB
        b_opcode;                   // 0: beq  1: bne  2: blt  3: bge
sc_signal< sc_uint<5> >
        ex_mem_ctrl,                // M in ID/EX
        ex_to_mem_m;                // M from ID/EX to EX/MEM
sc_signal< sc_uint<4> >
        ex_ctrl;                    // EX in ID/EX
sc_signal< sc_uint<3> >
        mem_mem_ctrl;
sc_signal<bool>
        b_cond,                     // condition for branch (output dbranch)
        is_jal,                     // identifies jal and jalr
        is_jalr,                    //
        is_jalx,                    //
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
sc_signal< sc_uint<3> >
        mem_data_size;              // Bit 0: 1 - signed, 0 - unsigned / Bit 1-2: 0 - byte; 1 - half; 2 - word
sc_signal< bool >
        mem_breg_wren,                 // breg write enable on MEM
        mem_rd_en,                     // 0: disable, 1: enable
        mem_wr_en,                     // 0: disable, 1: enable
        sel_mux_mem;                   // Select Mux Mem input


        // WriteBack -------------------------------------------------------
sc_signal< bool >
        f_breg_wr,
        wb_sel_mux;                  // 0: memory, 1: ALU
        
#endif //__SIGNALS_H__
