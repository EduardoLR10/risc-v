#include <systemc.h>
#include "adder/adder.hpp"
#include "breg/breg.hpp"
#include "dbranch/dbranch.hpp"
#include "wforward/wforward.hpp"
#include "genImm32/genImm32.hpp"
#include "pc/pc.hpp"
#include "mux/mux.hpp"
#include "control/control.hpp"
#include "dataMem/dataMem.hpp"
#include "ula/ula.hpp"
#include "forward/forward.hpp"
#include "instruction_memory/instruction_memory.hpp"
#include "aluControl/aluControl.hpp"
#include "pregs/reg_EX.hpp"
#include "pregs/reg_ID.hpp"
#include "pregs/reg_MEM.hpp"
#include "pregs/reg_WB.hpp"


#include "signals/signals.hpp"
#include "top/macros.hpp"

SC_MODULE(RISCV)
{
  // stage 1 : FETCH
  adder FETCH_ADDER;
  pc FETCH_PC;
  mux<sc_int<SIZE>, 2> FETCH_MUX;
  InstructionMemory FETCH_INSTRUCTION_MEMORY;
  reg_ID IF_ID;
  // stage 2 : DECODE
  genImm32 DECODE_GENIMM32;
  adder DECODE_ADDER;
  breg DECODE_BREG;
  dbranch DECODE_DBRANCH;
  mux<sc_int<SIZE>, 2> DECODE_MUX_DBRANCH_A;
  mux<sc_int<SIZE>, 2> DECODE_MUX_DBRANCH_B;
  mux<sc_int<SIZE>, 2> DECODE_MUX_BREG;
  mux<sc_int<SIZE>, 2> DECODE_MUX_ADDER;
  wforward DECODE_WFORWARD;
  reg_EX ID_EX;

  // stage 3 : EXECUTE
  ula EXECUTE_ULA;
  forward EXECUTE_FORWARD;
  aluControl EXECUTE_ALUCONTROL;
  mux<sc_int<SIZE>, 3> EXECUTE_MUX_FORWARDA;
  mux<sc_int<SIZE>, 3> EXECUTE_MUX_FORWARDB;
  mux<sc_int<SIZE>, 3> EXECUTE_MUX_ALUA;
  mux<sc_int<SIZE>, 2> EXECUTE_MUX_ALUB;
  reg_MEM EX_MEM;

  // stage 4 : MEMORY
  dataMem DATA_MEMORY;
  reg_WB MEM_WB;

  // stage 5 : WRITEBACK
  mux<sc_int<SIZE>, 2> WB_MUX;

  // CONTROL
  control CONTROLLER;
  mux<sc_uint<2>, 2> CONTROL_MUX_1;
  mux<sc_uint<3>, 2> CONTROL_MUX_2;

  // UNIVERSAL SIGNALS
  sc_signal<bool> clock;
  
  SC_CTOR(RISCV) :
    // stage 1
    FETCH_ADDER("FETCH_ADDER"), FETCH_PC("FETCH_PC"), FETCH_MUX("FETCH_MUX"), FETCH_INSTRUCTION_MEMORY("FETCH_INSTRUCTION_MEMORY"), IF_ID("IF_ID"),
    // stage 2
    DECODE_GENIMM32("DECODE_GENIMM32"), DECODE_ADDER("DECODE_ADDER"), DECODE_BREG("DECODE_BREG"), DECODE_DBRANCH("DECODE_DBRANCH"),
    DECODE_MUX_DBRANCH_A("DECODE_MUX_DBRANCH_A"), DECODE_MUX_DBRANCH_B("DECODE_MUX_DBRANCH_B"), DECODE_MUX_BREG("DECODE_MUX_BREG"),
    DECODE_MUX_ADDER("DECODE_MUX_ADDER"), DECODE_WFORWARD("DECODE_WFORWARD"), ID_EX("ID_EX"),
    // stage 3
    EXECUTE_ULA("EXECUTE_ULA"), EXECUTE_FORWARD("EXECUTE_FORWARD"), EXECUTE_ALUCONTROL("EXECUTE_ALUCONTROL"),
    EXECUTE_MUX_FORWARDA("EXECUTE_MUX_FORWARDA"), EXECUTE_MUX_FORWARDB("EXECUTE_MUX_FORWARDB"),
    EXECUTE_MUX_ALUA("EXECUTE_MUX_ALUA"), EXECUTE_MUX_ALUB("EXECUTE_MUX_ALUB"), EX_MEM("EX_MEM"),
    // stage 4
    DATA_MEMORY("DATA_MEMORY"), MEM_WB("MEM_WB"),
    // stage 5
    WB_MUX("WB_MUX"),
    // controller
    CONTROLLER("CONTROLLER"), CONTROL_MUX_1("CONTROL_MUX_1"), CONTROL_MUX_2("CONTROL_MUX_2")
  {
    // stage 1
    FETCH_ADDER.A(4);
    FETCH_ADDER.B(program_counter);
    FETCH_ADDER.Cin(false);
    FETCH_ADDER.C(next_pc);
    // FETCH_ADDER.Cout();  // ignore

    FETCH_PC.pc_in(pc_in);
    FETCH_PC.ld_pc(wren_pc);
    FETCH_PC.clock(clock);
    FETCH_PC.pc_out(program_counter);

    FETCH_MUX.inputs.at(0)(next_pc);
    FETCH_MUX.inputs.at(1)(pc_branch);
    FETCH_MUX.sel((is_branch.read() && b_cond.read()) || (is_jal.read()));
    FETCH_MUX.Z(pc_in);

    // TODO: load IM contents from binary file
    FETCH_INSTRUCTION_MEMORY.address(program_counter);
    FETCH_INSTRUCTION_MEMORY.out(ft_instruction);

    IF_ID.pc_cur(program_counter);
    IF_ID.inst(ft_instruction);
    IF_ID.next_pc(next_pc);
    IF_ID.clk(clock);
    IF_ID.wren(wren_reg_ID);
    IF_ID.rst(rst_reg_ID);
    
    // stage 2

    IF_ID.id_pc(id_pc);
    IF_ID.id_inst(id_instruction);
    IF_ID.id_next_pc(id_next_pc);
    IF_ID.id_rs1(id_rs1);
    IF_ID.id_rs2(id_rs2);
    IF_ID.id_rd(id_rd);
    IF_ID.id_ins_code(id_ins_code);

    DECODE_BREG.rs1(id_rs1);
    DECODE_BREG.rs2(id_rs2);
    DECODE_BREG.rd(id_rd);
    DECODE_BREG.d_in(data_breg);
    DECODE_BREG.ra(breg_ra);
    DECODE_BREG.rb(breg_rb);
    DECODE_BREG.wren(wren_breg);
    DECODE_BREG.clk(clock);
    DECODE_MUX_BREG.inputs.at(0)(wb_mux_data);
    DECODE_MUX_BREG.inputs.at(1)(id_next_pc);
    DECODE_MUX_BREG.sel(is_jal);
    DECODE_MUX_BREG.Z(data_breg);

    DECODE_MUX_ADDER.inputs.at(0)(id_pc);
    DECODE_MUX_ADDER.inputs.at(1)(breg_ra);
    DECODE_MUX_ADDER.sel(is_jalr);
    DECODE_MUX_ADDER.Z(jump_addr);
    DECODE_ADDER.A(jump_addr);
    DECODE_ADDER.B(id_imm_ws);

    DECODE_GENIMM32.instruction(id_instruction);
    DECODE_GENIMM32.imm(id_imm_ws);

    DECODE_MUX_DBRANCH_A.inputs.at(0)(breg_ra);
    DECODE_MUX_DBRANCH_A.inputs.at(1)(wb_rd);
    DECODE_MUX_DBRANCH_A.sel(sel_mux_ra_dbranch);
    DECODE_MUX_DBRANCH_A.Z(mux_dbranch_ra);

    DECODE_MUX_DBRANCH_B.inputs.at(0)(breg_rb);
    DECODE_MUX_DBRANCH_B.inputs.at(1)(wb_rd);
    DECODE_MUX_DBRANCH_B.sel(sel_mux_rb_dbranch);
    DECODE_MUX_DBRANCH_B.Z(mux_dbranch_rb);

    DECODE_WFORWARD.rs1(id_rs1);
    DECODE_WFORWARD.rs2(id_rs2);
    DECODE_WFORWARD.rd(mem_rd);
    DECODE_WFORWARD.rAOut(sel_mux_ra_dbranch);
    DECODE_WFORWARD.rBOut(sel_mux_rb_dbranch);

    DECODE_DBRANCH.ra(mux_dbranch_ra);
    DECODE_DBRANCH.rb(mux_dbranch_rb);
    DECODE_DBRANCH.Bout(b_cond);

    ID_EX.id_rs1(id_rs1);
    ID_EX.id_rs2(id_rs2);
    ID_EX.id_rd(id_rd);
    ID_EX.id_imm(id_imm_ws);
    ID_EX.id_regA(breg_ra);
    ID_EX.id_regB(breg_rb);
    ID_EX.id_pc(id_pc);
    ID_EX.id_clk(clock);
    ID_EX.wren(1);
    ID_EX.rst(0);
    ID_EX.id_funct7(id_instruction(31, 25));
    ID_EX.id_funct3(id_instruction(14, 12));

    // stage 3

    ID_EX.ex_rs1(ex_rs1);
    ID_EX.ex_rs2(ex_rs2);
    ID_EX.ex_rd(ex_rd);
    ID_EX.ex_imm(ex_imm);
    ID_EX.ex_regA(ex_ra);
    ID_EX.ex_regB(ex_rb);
    ID_EX.ex_pc(ex_pc);
    ID_EX.ex_funct7(ex_funct7);
    ID_EX.ex_funct7(ex_funct3);
    
    EXECUTE_MUX_FORWARDA.inputs.at(0)(ex_ra);
    EXECUTE_MUX_FORWARDA.inputs.at(1)(wb_mux_data);
    EXECUTE_MUX_FORWARDA.inputs.at(2)(mem_alu_out);
    EXECUTE_MUX_FORWARDA.sel(forward_a);
    EXECUTE_MUX_FORWARDA.Z(mux_forward_a);
    
    EXECUTE_MUX_FORWARDB.inputs.at(0)(ex_rb);
    EXECUTE_MUX_FORWARDB.inputs.at(1)(wb_mux_data);
    EXECUTE_MUX_FORWARDB.inputs.at(2)(mem_alu_out);
    EXECUTE_MUX_FORWARDB.sel(forward_b);
    EXECUTE_MUX_FORWARDB.Z(mux_forward_b);

    EXECUTE_MUX_ALUA.inputs.at(0)(sc_uint<SIZE>(0));
    EXECUTE_MUX_ALUA.inputs.at(1)(ex_pc);
    EXECUTE_MUX_ALUA.inputs.at(2)(mux_forward_a);
    EXECUTE_MUX_ALUA.sel(sel_alu_A);
    EXECUTE_MUX_ALUA.Z(mux_alu_a);
    
    EXECUTE_MUX_ALUB.inputs.at(0)(mux_forward_b);
    EXECUTE_MUX_ALUB.inputs.at(1)(ex_imm);
    EXECUTE_MUX_ALUB.sel(sel_alu_B);
    EXECUTE_MUX_ALUB.Z(mux_alu_b);

    EXECUTE_FORWARD.ID_EX_rs1(ex_rs1);
    EXECUTE_FORWARD.ID_EX_rs2(ex_rs2);
    EXECUTE_FORWARD.EX_MEM_rd(ex_rd);
    EXECUTE_FORWARD.MEM_WB_rd(wb_rd);
    EXECUTE_FORWARD.EX_MEM_write(wren_breg);
    EXECUTE_FORWARD.MEM_WB_write(f_breg_wr);
    EXECUTE_FORWARD.forwardA(forward_a);
    EXECUTE_FORWARD.forwardB(forward_b);

    EXECUTE_ALUCONTROL.ex_funct7(funct7);
    EXECUTE_ALUCONTROL.ex_funct3(funct3);
    EXECUTE_ALUCONTROL.alu_op(alu_op);
    EXECUTE_ALUCONTROL.opcode_alu(opcode_alu);

    EXECUTE_ULA.A_ULA(mux_alu_a);
    EXECUTE_ULA.B_ULA(mux_alu_b);
    EXECUTE_ULA.Z_ULA(alu_out);
    EXECUTE_ULA.opcode_ULA(opcode_alu);
    EXECUTE_ULA.zero_ULA(zero_alu);

    EX_MEM.ex_rd(ex_rd);
    EX_MEM.ex_alu_out(alu_out);
    EX_MEM.ex_mux_alu_b(mux_alu_b);
    EX_MEM.clk(clock);
    EX_MEM.wren(1);
    EX_MEM.rst(0);

    // stage 4

    EX_MEM.rd_en(mem_rd_en);
    EX_MEM.wr_en(mem_wr_en);
    EX_MEM.d_size(mem_data_size);
    EX_MEM.mem_wb_ctrl(mem_wb_ctrl);
    EX_MEM.mem_rd(mem_rd);
    EX_MEM.mem_alu_out(mem_alu_out);
    EX_MEM.mem_mux_alu_b(mem_mux_alu_b);

    DATA_MEMORY.rd_en(mem_rd_en);
    DATA_MEMORY.wr_en(mem_wr_en);
    DATA_MEMORY.d_size(mem_data_size);
    DATA_MEMORY.mem_addr(mem_mux_alu_b);
    DATA_MEMORY.imm(0);
    DATA_MEMORY.wr_data(mem_alu_out);
    DATA_MEMORY.mem_out(dm_out);
    DATA_MEMORY.clk(clock);

    MEM_WB.wb_ctrl(wb_sel_mux, wren_breg);
    MEM_WB.mem_rd(mem_rd);
    MEM_WB.mem_alu_out(mem_alu_out);
    MEM_WB.mem_mdata_out(dm_out);
    MEM_WB.clk(clock);
    MEM_WB.wren(1);
    MEM_WB.rst(0);

    // stage 5

    MEM_WB.mux_data(wb_mux_data);
    MEM_WB.breg_wr(f_breg_wr);
    MEM_WB.wb_rd(wb_rd);
    MEM_WB.wb_alu_out(wb_alu_out);
    MEM_WB.wb_mdata_out(wb_md_out);

    WB_MUX.inputs.at(0)(wb_md_out);
    WB_MUX.inputs.at(1)(wb_alu_out);
    WB_MUX.sel(wb_sel_mux);
    WB_MUX.Z(wb_mux_data);

    // controller

    CONTROLLER.instruction(id_instruction);
    CONTROLLER.rst_reg_ID(rst_reg_ID);
    CONTROLLER.id_flush(id_flush);
    CONTROLLER.is_jal(is_jal);
    CONTROLLER.is_jalx(is_jalx);
    CONTROLLER.is_jalr(is_jalr);
    CONTROLLER.is_branch(is_branch);
    CONTROLLER.b_code(b_opcode);
    CONTROLLER.ex_flush(ex_flush);
    CONTROLLER.ex_ctrl(alu_op, sel_alu_B, sel_alu_A);
    CONTROLLER.mem_ctrl(mem_data_size, mem_wr_en, mem_rd_en);
    CONTROLLER.wb_ctrl(wb_sel_mux, wren_breg);
    
    ID_EX.id_ex_ctrl(alu_op, sel_alu_B, sel_alu_A);
    ID_EX.id_mem_ctrl(mem_data_size, mem_wr_en, mem_rd_en);
    ID_EX.id_wb_ctrl(wb_sel_mux, wren_breg);
    
    CONTROL_MUX_1.inputs.at(0)(sc_uint<2>(0));
    CONTROL_MUX_1.inputs.at(1)(ex_wb_ctrl);
    CONTROL_MUX_1.sel(ex_flush);
    CONTROL_MUX_1.Z(mem_wb_ctrl);
    
    CONTROL_MUX_2.inputs.at(0)(sc_uint<3>(0));
    CONTROL_MUX_2.inputs.at(1)(ex_mem_ctrl);
    CONTROL_MUX_2.sel(ex_flush);
    CONTROL_MUX_2.Z(mem_mem_ctrl);
  }
};