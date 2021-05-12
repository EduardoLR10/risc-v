#ifndef __REG_EX_H__
#define __REG_EX_H__

#include <systemc.h>
#include "top/macros.hpp"

// ************************** ID/EX
SC_MODULE (reg_EX){
    // control
    sc_in< sc_uint<4> > id_ex_ctrl;
    sc_in< sc_uint<5> > id_mem_ctrl;
    sc_in< sc_uint<2> > id_wb_ctrl;
    sc_out< bool > alu_op, alu_src_B;
    sc_out< sc_uint<2> > alu_src_A;
    sc_out< sc_uint<5> > mem_ctrl;
    sc_out< sc_uint<2> > wb_ctrl;

    // data
    sc_in< sc_uint<5> > id_rs1, id_rs2, id_rd;
    sc_in< sc_uint<SIZE> > id_imm, id_regA, id_regB, id_pc;
    sc_in<bool> clk, wren, rst;
    sc_in< sc_uint<7> > id_funct7;
    sc_in< sc_uint<3> > id_funct3;
    sc_out< sc_uint<5> > ex_rs1, ex_rs2, ex_rd;
    sc_out< sc_uint<SIZE> > ex_imm, ex_regA, ex_regB, ex_pc;
    sc_out< sc_uint<7> > ex_funct7;
    sc_out< sc_uint<3> > ex_funct3;

    void load();

    SC_CTOR(reg_EX) {
        SC_METHOD(load);
        sensitive << clk.pos();
    }

private:
    sc_uint<SIZE> imm_buf, regA_buf, regB_buf, pc_buf;
    sc_uint<5> rs1_buf, rs2_buf, rd_buf;
    sc_uint<4> ex_ctrl_buf;
    sc_uint<7> funct7_buf;
    sc_uint<3> funct3_buf;
};

#endif
