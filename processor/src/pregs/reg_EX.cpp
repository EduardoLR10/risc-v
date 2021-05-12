#include "pregs/reg_EX.hpp"

void reg_EX::load() {
    if (rst == 1) {
        rs1_buf = rs2_buf = rd_buf = 0;
        imm_buf = regA_buf = regB_buf = 0;
        pc_buf = 0;
        funct3_buf = 0;
        funct7_buf = 0;
    }
    else if (wren == 1) {
        rs1_buf = id_rs1.read();
        rs2_buf = id_rs2.read();
        rd_buf = id_rd.read();
        imm_buf = id_imm.read();
        regA_buf = id_regA.read();
        regB_buf = id_regB.read();
        pc_buf = id_pc.read();
        funct3_buf = id_funct3.read();
        funct7_buf = id_funct7.read();
        ex_ctrl_buf = id_ex_ctrl.read();
    }
    alu_op.write(ex_ctrl_buf[3]);
    alu_src_A.write(ex_ctrl_buf(0, 1));
    alu_src_B.write(ex_ctrl_buf[2]);
    mem_ctrl.write(id_mem_ctrl.read());
    wb_ctrl.write(id_wb_ctrl.read());
    ex_imm.write(imm_buf); ex_regA.write(regA_buf); ex_regB.write(regB_buf);
    ex_rs1.write(rs1_buf); ex_rs2.write(rs2_buf); ex_rd.write(rd_buf);
    ex_pc.write(pc_buf); ex_funct3.write(funct3_buf); ex_funct7.write(funct7_buf);
}
