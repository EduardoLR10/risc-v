#include "pregs/reg_MEM.hpp"

void reg_MEM::load() {
    if (rst == 1) {
        rd_buf = 0; mem_ctrl_buf = 0; wb_ctrl_buf = 0;
        alu_out_buf = mux_alu_b_buf = 0;
   }
    else if (wren == 1) {
        rd_buf = ex_rd.read();
        alu_out_buf = ex_alu_out.read();
        mux_alu_b_buf = ex_mux_alu_b.read();
        wb_ctrl_buf = ex_wb_ctrl.read();
        mem_ctrl_buf = ex_mem_ctrl.read();
    }
    mem_alu_out.write(alu_out_buf);
    mem_mux_alu_b.write(mux_alu_b_buf);
    mem_rd.write(rd_buf);
    mem_wb_ctrl.write(wb_ctrl_buf);
    d_size.write(mem_ctrl_buf.range(4, 2));
    rd_en.write(mem_ctrl_buf[0]);
    wr_en.write(mem_ctrl_buf[1]);
}
