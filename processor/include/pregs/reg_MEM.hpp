#ifndef __REG_MEM_H__
#define __REG_MEM_H__

#include <systemc.h>
#include "top/macros.hpp"

// ************************** EX/MEM
SC_MODULE (reg_MEM){
    sc_in< sc_uint<5> > ex_rd;
    sc_in< sc_uint<SIZE> > ex_alu_out, ex_mux_alu_b;
    sc_in<bool> clk, wren, rst;
    sc_out< sc_uint<5> > mem_rd;
    sc_out< sc_uint<SIZE> > mem_alu_out, mem_mux_alu_b;
    sc_out< sc_uint<SIZE> > id_pc, id_inst;

    void load();

    SC_CTOR(reg_MEM) {
        SC_METHOD(load);
        sensitive << clk.pos();
    }

private:
    sc_uint<SIZE> pc_buf, inst_buf;
    sc_uint<SIZE> alu_out_buf, mux_alu_b_buf;
    sc_uint<5> rd_buf;
};

#endif