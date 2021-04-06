#include "pregs/reg_ID.hpp"

void reg_ID::load() {
    if (rst == 1)
        pc_buf = inst_buf = 0;
    else if (wren == 1) {
        pc_buf = pc_cur.read();
        inst_buf = inst.read();
    }
    id_pc.write(pc_buf);
    id_inst.write(inst_buf);
}