#include "pregs/reg_WB.hpp"

void reg_WB::load() {
    if (rst == 1) {
        rd_buf = 0;
        alu_out_buf = mdata_buf = 0;
        wb_ctrl_buf = 0;
    }
    else if (wren == 1) {
        rd_buf = mem_rd.read();
        alu_out_buf = mem_alu_out.read();
        mdata_buf = mem_mdata_out.read();
        wb_ctrl_buf = wb_ctrl.read();
    }
    wb_rd.write(rd_buf);
    wb_alu_out.write(alu_out_buf);
    wb_mdata_out.write(mdata_buf);
    breg_wr.write(wb_ctrl_buf[0]);
    mux_data.write(wb_ctrl_buf[1]);
}