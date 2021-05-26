#ifndef __REG_MEM_H__
#define __REG_MEM_H__

#include <systemc.h>
#include "top/macros.hpp"

// ************************** EX/MEM
SC_MODULE (reg_MEM){
// Control
    sc_in< sc_uint<5> > ex_mem_ctrl;
    sc_in< sc_uint<2> > ex_wb_ctrl;
    
// Mem control
    sc_out< bool > rd_en, wr_en;  // 0 - disable; 1 - enable
    sc_out< sc_uint<3> > d_size; // Bit 2: 1 - signed, 0 - unsigned / Bit 1-0: 0 - byte; 1 - half; 2 - word
// WB control
    sc_out< sc_uint<2> > mem_wb_ctrl;

// Data
    sc_in< sc_uint<5> > ex_rd, ex_rs2;
    sc_in< sc_uint<SIZE> > ex_alu_out, ex_mux_alu_b;
    sc_in<bool> clk, wren, rst;
    sc_out< sc_uint<5> > mem_rd, mem_rs2;
    sc_out< sc_uint<SIZE> > mem_alu_out, mem_mux_alu_b;

    void load();

    SC_CTOR(reg_MEM) {
        SC_METHOD(load);
        sensitive << clk.pos();
    }

private:
    sc_uint<SIZE> alu_out_buf, mux_alu_b_buf;
    sc_uint<5> rd_buf;
    sc_uint<5> mem_ctrl_buf;
    sc_uint<2> wb_ctrl_buf;
};

#endif
