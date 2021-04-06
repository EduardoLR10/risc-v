#include "pregs/reg_EX.hpp"

void reg_EX::load() {
    if (rst == 1) {
        rs1_buf = rs2_buf = rd_buf = 0;
        imm_buf = regA_buf = regB_buf = 0;
    }
    else if (wren == 1) {
        rs1_buf = id_rs1.read();
        rs2_buf = id_rs2.read();
        rd_buf = id_rd.read();
        imm_buf = id_imm.read();
        regA_buf = id_regA.read();
        regB_buf = id_regB.read();
    }
    ex_imm.write(imm_buf); ex_regA.write(regA_buf); ex_regB.write(regB_buf);
    ex_rs1.write(rs1_buf); ex_rs2.write(rs2_buf); ex_rd.write(rd_buf);
}