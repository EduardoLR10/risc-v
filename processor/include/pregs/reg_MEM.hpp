#ifndef __REG_MEM_H__
#define __REG_MEM_H__

#include <systemc.h>
#include "top/macros.hpp"

// ************************** EX/MEM
SC_MODULE (reg_MEM){
// Control
    sc_in< sc_uint<3> > ex_mem_ctrl;
    sc_in< sc_uint<2> > ex_wb_ctrl;
// Mem control
    sc_out< bool > rd_wr;  // 0 - read; 1 - write
    sc_out< sc_uint<2> > d_size; // 00 - byte; 01 - half; 10 - word
// WB control
    sc_out< sc_uint<2> > mem_wb_ctrl;

// Data
    sc_in< sc_uint<5> > ex_rd;
    sc_in< sc_uint<WSIZE> > ex_alu_out, ex_mux_alu_b;
    sc_in<bool> clk, wren, rst;
    sc_out< sc_uint<5> > mem_rd;
    sc_out< sc_uint<WSIZE> > mem_alu_out, mem_mux_alu_b;

    void load();

    SC_CTOR(reg_MEM) {
        SC_METHOD(load);
        sensitive << clk.pos();
    }

private:
    sc_uint<SIZE> alu_out_buf, mux_alu_b_buf;
    sc_uint<5> rd_buf;
};

#endif
