#include "pregs/reg_MEM.hpp"

void reg_MEM::load() {
    if (rst == 1) {
        rd_buf = 0;
        alu_out_buf = mux_alu_b_buf = 0;
    }
    else if (wren == 1) {
        rd_buf = ex_rd;
        alu_out_buf = ex_alu_out.read();
        mux_alu_b_buf = ex_mux_alu_b.read();
    }
    id_pc.write(pc_buf);
    id_inst.write(inst_buf);
}