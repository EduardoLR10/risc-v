#ifndef RISCV_H
#define RISCV_H

#include <iomanip>
#include <systemc.h>
#include "top/macros.hpp"
#include "signals/signals.hpp"
#include "Fetch/Fetch.hpp"
#include "Decode/Decode.hpp"
#include "Execute/Execute.hpp"
#include "pregs/reg_ID.hpp"
#include "pregs/reg_EX.hpp"
#include "pregs/reg_MEM.hpp"
#include "pregs/reg_WB.hpp"
#include "control/control.hpp"
#include "dataMem/dataMem.hpp"
#include "mforward/mforward.hpp"



SC_MODULE(RISCV){
  // INPUTS
    sc_in < bool > clock;

    void dump_breg() {
        decode_stg.dump_breg();
    }

    SC_CTOR(RISCV):
    fetch_stg("fetch_stg"), IF_ID("IF_ID"), decode_stg("decode_stg"), ID_EX("ID_EX"),
    execute_stg("execute_stg"), CONTROLLER("CONTROLLER"), EX_MEM("EX_MEM"), MUX_MEM("MUX_MEM"),
    DATA_MEMORY("DATA_MEMORY"), MEM_MFORWARD("MEM_MFORWARD"), MEM_WB("MEM_WB"), WB_MUX("WB_MUX"),
    fet_dbg(true)
    {
    SC_METHOD(update);
      sensitive << is_branch << b_cond << is_jalx << id_instruction;
    SC_THREAD(debug);
      sensitive << clock.neg();
      dont_initialize();
    // Fetch stage
    fetch_stg.clock(clock);
    fetch_stg.pc_branch_in(pc_branch);
    fetch_stg.fetch_sel_in(fetch_sel_in);
    fetch_stg.wren_pc_in(wren_pc);
    fetch_stg.next_pc_out(next_pc);
    fetch_stg.instruction_out(ft_instruction);
    fetch_stg.pc_out(program_counter);
    // Reg_FT_ID - inputs
    IF_ID.pc_cur(program_counter);
    IF_ID.inst(ft_instruction);
    IF_ID.next_pc(next_pc);
    IF_ID.clk(clock);
    IF_ID.wren(TRUE);
    IF_ID.rst(FALSE);
    // Reg_FT_ID - outputs
    IF_ID.id_pc(id_pc);
    IF_ID.id_inst(id_instruction);
    IF_ID.id_next_pc(id_next_pc);
    IF_ID.id_rs1(id_rs1);
    IF_ID.id_rs2(id_rs2);
    IF_ID.id_rd(id_rd);
    IF_ID.id_ins_code(id_ins_code);
    // Decode stage - inputs
    decode_stg.id_pc_i(id_pc);
    decode_stg.id_inst(id_instruction);
    decode_stg.id_next_pc(id_next_pc);
    decode_stg.wb_mux_data(wb_mux_data);
    decode_stg.mem_reg_data(mem_alu_out);
    decode_stg.id_rs1_i(id_rs1);
    decode_stg.id_rs2_i(id_rs2);
    decode_stg.id_rd_i(id_rd);
    decode_stg.mem_rd_i(mem_rd);
    decode_stg.wb_rd_i(wb_rd);
    decode_stg.is_jalr(is_jalr);
    decode_stg.is_jalx(is_jalx);
    decode_stg.f_breg_wr(f_breg_wr);
    decode_stg.clock(clock);
    decode_stg.mem_breg_wren(mem_breg_wren);
    decode_stg.b_opcode(b_opcode);
    // Decode stage - outputs
    decode_stg.b_cond(b_cond);
    decode_stg.pc_branch(pc_branch);
    decode_stg.id_imm(id_imm);
    decode_stg.breg_ra_o(id_ra);
    decode_stg.breg_rb_o(id_rb);
    // Reg ID_EX - inputs
    ID_EX.id_rs1(id_rs1);
    ID_EX.id_rs2(id_rs2);
    ID_EX.id_rd(id_rd);
    ID_EX.id_imm(id_imm);
    ID_EX.id_regA(id_ra);
    ID_EX.id_regB(id_rb);
    ID_EX.id_pc(id_pc);
    ID_EX.clk(clock);
    ID_EX.wren(TRUE);
    ID_EX.rst(FALSE);
    ID_EX.id_funct3(id_funct3);
    ID_EX.id_funct7(id_funct7);
    ID_EX.id_ex_ctrl(ex_ctrl);
    ID_EX.id_mem_ctrl(ex_mem_ctrl);
    ID_EX.id_wb_ctrl(ex_wb_ctrl);
    // Reg ID_EX - outputs
    ID_EX.ex_rs1(ex_rs1);
    ID_EX.ex_rs2(ex_rs2);
    ID_EX.ex_rd(ex_rd);
    ID_EX.ex_imm(ex_imm);
    ID_EX.ex_regA(ex_ra);
    ID_EX.ex_regB(ex_rb);
    ID_EX.ex_pc(ex_pc);
    ID_EX.ex_funct7(ex_funct7);
    ID_EX.ex_funct3(ex_funct3);
    ID_EX.ex_mem_ctrl(ex_to_mem_m);
    ID_EX.ex_wb_ctrl(ex_to_mem_wb);
    ID_EX.alu_op(alu_op);
    ID_EX.alu_src_A(sel_alu_A);
    ID_EX.alu_src_B(sel_alu_B);
    // Execute stage - inputs
    execute_stg.ex_pc(ex_pc);
    execute_stg.ex_ra(ex_ra);
    execute_stg.ex_rb(ex_rb);
    execute_stg.ex_imm(ex_imm);
    execute_stg.wb_mux_data(wb_mux_data);
    execute_stg.mem_alu_out(mem_alu_out);
    execute_stg.alu_src_B(sel_alu_B);
    execute_stg.funct7(ex_funct7);
    execute_stg.funct3(ex_funct3);
    execute_stg.alu_op(alu_op);
    execute_stg.mem_breg_wren(mem_breg_wren);
    execute_stg.wb_breg_wren(f_breg_wr);
    execute_stg.ex_rs1(ex_rs1);
    execute_stg.ex_rs2(ex_rs2);
    execute_stg.ex_rd(ex_rd);
    execute_stg.mem_rd(mem_rd);
    execute_stg.wb_rd(wb_rd);
    execute_stg.alu_src_A(sel_alu_A);
    // Execute stage - outputs
    execute_stg.alu_out(alu_out);
    execute_stg.alu_in_B(ex_alu_B);
    // Control RV
    CONTROLLER.instruction(id_instruction);
    //CONTROLLER.rst_reg_ID(rst_reg_ID);
    CONTROLLER.id_flush(id_flush);
    CONTROLLER.is_jalx(is_jalx);
    CONTROLLER.is_jalr(is_jalr);
    CONTROLLER.is_branch(is_branch);
    CONTROLLER.b_code(b_opcode);
    CONTROLLER.ex_flush(ex_flush);
    CONTROLLER.ex_ctrl(ex_ctrl);
    CONTROLLER.mem_ctrl(ex_mem_ctrl);
    CONTROLLER.wb_ctrl(ex_wb_ctrl);
    // Reg EX_MEM - inputs
    EX_MEM.ex_rd(ex_rd);
    EX_MEM.ex_rs2(ex_rs2);
    EX_MEM.ex_alu_out(alu_out);
    EX_MEM.ex_mux_alu_b(ex_alu_B);
    EX_MEM.ex_mem_ctrl(ex_to_mem_m);
    EX_MEM.ex_wb_ctrl(ex_to_mem_wb);
    EX_MEM.clk(clock);
    EX_MEM.wren(TRUE);
    EX_MEM.rst(FALSE);
    // Reg EX_MEM - outputs
    EX_MEM.rd_en(mem_rd_en);
    EX_MEM.wr_en(mem_wr_en);
    EX_MEM.d_size(mem_data_size);
    EX_MEM.mem_wb_ctrl(mem_to_wb);
    EX_MEM.mem_rd(mem_rd);
    EX_MEM.mem_rs2(mem_rs2);
    EX_MEM.mem_alu_out(mem_alu_out);
    EX_MEM.mem_mux_alu_b(mem_mux_alu_b);
    // Mux Data Mem in
    MUX_MEM.in0(mem_mux_alu_b);
    MUX_MEM.in1(wb_mux_data);
    MUX_MEM.sel(sel_mux_mem);
    MUX_MEM.Z(mdata);
    // DATA MEMORY
    DATA_MEMORY.rd_en(mem_rd_en);
    DATA_MEMORY.wr_en(mem_wr_en);
    DATA_MEMORY.d_size(mem_data_size);
    DATA_MEMORY.mem_addr(mem_alu_out);
    DATA_MEMORY.wr_data(mdata);
    DATA_MEMORY.mem_out(dm_out);
    DATA_MEMORY.clk(clock);
    // Forward Memory
    MEM_MFORWARD.mem_rs2(mem_rs2);
    MEM_MFORWARD.mem_wr_en(mem_wr_en);
    MEM_MFORWARD.wb_rd(wb_rd);
    MEM_MFORWARD.f_breg_wr(f_breg_wr);
    MEM_MFORWARD.sel_mux_mem(sel_mux_mem);
    // Reg MEM_WB
    MEM_WB.wb_ctrl(mem_to_wb);
    MEM_WB.mux_data(wb_sel_mux);
    MEM_WB.breg_wr(f_breg_wr);
    MEM_WB.mem_rd(mem_rd);
    MEM_WB.mem_alu_out(mem_alu_out);
    MEM_WB.mem_mdata_out(dm_out);
    MEM_WB.wb_rd(wb_rd);
    MEM_WB.wb_alu_out(wb_alu_out);
    MEM_WB.wb_mdata_out(wb_md_out);
    MEM_WB.clk(clock);
    MEM_WB.rst(FALSE);
    MEM_WB.wren(TRUE);
    // MUX WB Data
    WB_MUX.in0(wb_alu_out);
    WB_MUX.in1(wb_md_out);
    WB_MUX.sel(wb_sel_mux);
    WB_MUX.Z(wb_mux_data);
    }

    void update() {
        fetch_sel_in.write((is_branch && b_cond) || is_jalx);
        id_funct3.write(id_instruction.read().range(14, 12));
        id_funct7.write(id_instruction.read()[30]);
    }

    void debug() {
       for (;;) {
// CONTROL
//            std::cout
//            << std::setw(7) << sc_time_stamp()
//            << std::setw(7) << "PC : "      << std::setw(8) << hex << id_pc.read()
//            << std::setw(7) << "I = "       << std::setw(10) << hex << id_instruction.read()
//            << std::setw(7) << "rs1 = "     << std::setw(2) << dec << id_rs1.read()
//            << std::setw(7) << "rs2 = "     << std::setw(2) << dec << id_rs2.read()
//            << std::setw(7) << "rd = "      << std::setw(2) << dec << id_rd.read()
//            << std::setw(7) << "imm = "     << std::setw(4) << dec << id_imm.read()
//            << std::setw(7) << "alu = "     << std::setw(4) << dec << alu_out.read()
//            << std::setw(10) << "ex_ctrl: "  << std::setw(6) << ex_ctrl.read().to_string(SC_BIN)
//            << std::setw(12) << "mem_ctrl: "  << std::setw(6) << ex_mem_ctrl.read().to_string(SC_BIN)
//            << std::setw(10) << "wb_ctrl: "  << std::setw(6) << ex_wb_ctrl.read().to_string(SC_BIN)
//            << std::setw(10) << "jx/r/br: "  << std::setw(6) << is_jalx << is_jalr << is_branch
//            << endl;
// FETCH - debug
//            if (false && fet_dbg && DEBUG_INSTRUCTION == ft_instruction.read().range(6,0)) {
//                fet_dbg = false;
//                dec_dbg = true;
//                std::cout << std::setw(7) << "Ftch:  "
//                          << std::setw(7) << sc_time_stamp()
//                          << " PC : "  << std::setw(8) << hex << program_counter.read()
//                          << "\tInst = \t" << hex << ft_instruction.read()
//                          << endl;
//            }
//
// REG_IF_ID - debug
//            std::cout   << std::setw(7) << sc_time_stamp()
//                        << "\t\t PC : " << id_pc.read()
//                        << "\t\tInstruction = \t" << hex << id_instruction.read() << dec
//                        << endl
// Decode
//            if (false && dec_dbg) {
//                dec_dbg = false; exe_dbg = true;
//                std::cout << std::setw(7) << "Dec:   "
//                          << std::setw(7) << sc_time_stamp()
//                          << " PC : "  << std::setw(8) << hex << id_pc.read()
//                          << "\tInst = \t" << std::setw(8) << hex << id_instruction.read()
//                          << std::setw(8) << "rs1 = "    << std::setw(4) << dec << id_rs1.read()
//                          << std::setw(8) << "\trs2 = "  << std::setw(4) << dec << id_rs2.read()
//                          << std::setw(8) << "\trd = "   << std::setw(4) << dec << id_rd.read()
//                          << std::setw(8) << "\timm = "  << std::setw(4) << dec << id_imm.read()
//                          << std::setw(8) << "\tra = "  << std::setw(4) << dec << id_ra.read()
//                          << std::setw(8) << "\trb = "  << std::setw(4) << dec << id_rb.read()
//                          << endl;
//            }
// Execute
//            if (false && exe_dbg) {
//                exe_dbg = false; mem_dbg = true;
//                std::cout << std::setw(7) << "Exec:  "
//                          << std::setw(7) << sc_time_stamp()
//                          << std::setw(6) << "PC : " << std::setw(8) << hex << ex_pc.read()
//                          << std::setw(6) << "\trs1 = " << std::setw(4) << dec << ex_rs1.read()
//                          << std::setw(6) << "\trs2 = " << std::setw(4) << dec << ex_rs2.read()
//                          << std::setw(6) << "\trd = " << std::setw(4) << dec << ex_rd.read()
//                          << std::setw(6) << "\timm = " << std::setw(4) << dec << ex_imm.read()
//                          << std::setw(6) << "\talu = " << std::setw(4) << dec << alu_out.read()
//                          << endl;
//            }
// Memory
//            if (false && mem_dbg) {
//                wb_dbg = true;
//                mem_dbg = false;
//                std::cout << std::setw(7) << "Mem:   "
//                          << std::setw(7) << sc_time_stamp()
//                          << std::setw(6) << "\trs2 = " << std::setw(4) << dec << mem_rs2.read()
//                          << std::setw(6) << "\trd = " << std::setw(4) << dec << mem_rd.read()
//                          << std::setw(6) << "\talu = " << std::setw(4) << dec << mem_alu_out.read()
//                          << std::setw(6) << "\trb = " << std::setw(4) << dec << mem_mux_alu_b.read()
//                          << std::setw(6) << "\tmdata = " << std::setw(4) << dec << dm_out.read()
//                          << endl;
//            }
// WriteBack
            if (false) {
                fet_dbg = true;
                wb_dbg = false;
                std::cout << std::setw(7) << "WB:    "
                          << std::setw(7) << sc_time_stamp()
                          << std::setw(6) << "\tbreg_wren = " << std::setw(4) << dec << f_breg_wr.read()
                          << std::setw(6) << "\trd = " << std::setw(4) << dec << wb_rd.read()
                          << std::setw(6) << "\tmdata = " << std::setw(4) << dec << wb_md_out.read()
                          << std::setw(6) << "\talu = " << std::setw(4) << dec << wb_alu_out.read()
                          << endl;
                wait();
            }
        }
    }

    void start_of_simulation( void ) {
        std::cout << "Start simulation" << endl;
        TRUE.write(true);
        FALSE.write(false);
        K_ZERO.write(0);
        K_ONE.write(1);
        is_jalx = 0;
        is_branch = 0;
        b_cond = 0;
        wren_pc = 1;
        pc_branch = 0;
    }

    void  end_of_simulation ( void ) {
//        decode_stg.dump_breg();
    }

private:
    // stage 1 : FETCH
    Fetch fetch_stg;                    // fetch stage
    reg_ID IF_ID;
    Decode decode_stg;                  // decode stage
    reg_EX ID_EX;
    Execute execute_stg;                // execute stage
    control CONTROLLER;
    reg_MEM EX_MEM;
    mux2< sc_uint<WSIZE> > MUX_MEM;
    dataMem DATA_MEMORY;
    MForward MEM_MFORWARD;
    reg_WB MEM_WB;
    mux2< sc_uint<WSIZE> > WB_MUX;
    sc_signal<bool> id_funct7;
    sc_signal< sc_uint<3> > id_funct3;

    bool dec_dbg, exe_dbg, mem_dbg, wb_dbg;
    bool fet_dbg;
};

#endif