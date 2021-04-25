#include "pregs/reg_ID.hpp"

void reg_ID::load() {
    if (rst == 1) {
        pc_buf = inst_buf = next_pc_buf = 0;
        rs1_buf = rs2_buf = rd_buf = 0;
        ins_code_buf = 0;
    }
    else if (wren == 1) {
        pc_buf = pc_cur.read();
        inst_buf = inst.read();
        next_pc_buf = next_pc.read();
        rs1_buf = inst_buf.range(19, 15);
        rs2_buf = inst_buf.range(24, 20);
        rd_buf = inst_buf.range(11, 7);
        ins_code_buf = inst_buf.range(6, 0);
    }
    id_pc.write(pc_buf);        id_rs2.write(rs2_buf);
    id_inst.write(inst_buf);    id_rd.write(rd_buf);
    id_rs1.write(rs1_buf);      id_next_pc.write(next_pc_buf);
    id_ins_code.write(ins_code_buf);
}
