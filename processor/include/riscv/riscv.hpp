#include <systemc.h>
#include "adder/adder.hpp"
#include "breg/breg.hpp"
#include "dbranch/dbranch.hpp"
#include "dforward/dforward.hpp"
#include "genImm32/genImm32.hpp"
#include "pc/pc.hpp"
#include "mux/mux.hpp"
#include "control/control.hpp"
#include "dataMem/dataMem.hpp"
#include "ula/ula.hpp"
#include "eforward/eforward.hpp"
#include "instruction_memory/instruction_memory.hpp"
#include "aluControl/aluControl.hpp"
#include "pregs/reg_EX.hpp"
#include "pregs/reg_ID.hpp"
#include "pregs/reg_MEM.hpp"
#include "pregs/reg_WB.hpp"
#include "mforward/mforward.hpp"


#include "signals/signals.hpp"
#include "top/macros.hpp"

SC_MODULE(RISCV)
{
  // stage 1 : FETCH
  adder FETCH_ADDER;
  pc FETCH_PC;
  mux<sc_uint<SIZE>, 2> FETCH_MUX;
  InstructionMemory FETCH_INSTRUCTION_MEMORY;
  reg_ID IF_ID;
  // stage 2 : DECODE
  genImm32 DECODE_GENIMM32;
  adder DECODE_ADDER;
  breg DECODE_BREG;
  dbranch DECODE_DBRANCH;
  mux<sc_uint<SIZE>, 2> DECODE_MUX_DBRANCH_A;
  mux<sc_uint<SIZE>, 2> DECODE_MUX_DBRANCH_B;
  mux<sc_uint<SIZE>, 2> DECODE_MUX_RETURN_ADDRESS;
  mux<sc_uint<SIZE>, 2> DECODE_MUX_ADDER;
  dforward DECODE_DFORWARD;
  reg_EX ID_EX;

  // stage 3 : EXECUTE
  ula EXECUTE_ULA;
  eforward EXECUTE_EFORWARD;
  aluControl EXECUTE_ALUCONTROL;
  mux<sc_uint<SIZE>, 3> EXECUTE_MUX_FORWARDA;
  mux<sc_uint<SIZE>, 3> EXECUTE_MUX_FORWARDB;
  mux<sc_uint<SIZE>, 3> EXECUTE_MUX_ALUA;
  mux<sc_uint<SIZE>, 2> EXECUTE_MUX_ALUB;
  reg_MEM EX_MEM;

  // stage 4 : MEMORY
  dataMem DATA_MEMORY;
  reg_WB MEM_WB;
  mux<sc_uint<SIZE>, 2> MUX_MEM;
  MForward MEM_MFORWARD;

  // stage 5 : WRITEBACK
  mux<sc_uint<SIZE>, 2> WB_MUX;

  // CONTROL
  control CONTROLLER;

  // UNIVERSAL SIGNALS
  sc_in< bool > clock;
  
  SC_CTOR(RISCV) :
    // stage 1
    FETCH_ADDER("FETCH_ADDER"), FETCH_PC("FETCH_PC"), FETCH_MUX("FETCH_MUX"), FETCH_INSTRUCTION_MEMORY("FETCH_INSTRUCTION_MEMORY"), IF_ID("IF_ID"),
    // stage 2
    DECODE_GENIMM32("DECODE_GENIMM32"), DECODE_ADDER("DECODE_ADDER"), DECODE_BREG("DECODE_BREG"), DECODE_DBRANCH("DECODE_DBRANCH"),
    DECODE_MUX_DBRANCH_A("DECODE_MUX_DBRANCH_A"), DECODE_MUX_DBRANCH_B("DECODE_MUX_DBRANCH_B"), DECODE_MUX_RETURN_ADDRESS("DECODE_MUX_BREG"),
    DECODE_MUX_ADDER("DECODE_MUX_ADDER"), DECODE_DFORWARD("DECODE_WFORWARD"), ID_EX("ID_EX"),
    // stage 3
    EXECUTE_ULA("EXECUTE_ULA"), EXECUTE_EFORWARD("EXECUTE_FORWARD"), EXECUTE_ALUCONTROL("EXECUTE_ALUCONTROL"),
    EXECUTE_MUX_FORWARDA("EXECUTE_MUX_FORWARDA"), EXECUTE_MUX_FORWARDB("EXECUTE_MUX_FORWARDB"),
    EXECUTE_MUX_ALUA("EXECUTE_MUX_ALUA"), EXECUTE_MUX_ALUB("EXECUTE_MUX_ALUB"), EX_MEM("EX_MEM"),
    // stage 4
    DATA_MEMORY("DATA_MEMORY"), MEM_WB("MEM_WB"), MUX_MEM("MUX_MEM"), MEM_MFORWARD("mforward"),
    // stage 5
    WB_MUX("WB_MUX"),
    // controller
    CONTROLLER("CONTROLLER")
  {

    // CONSTANTS
    sc_signal<bool> true_sig;
    true_sig.write(true);

    sc_signal<bool> false_sig;
    false_sig.write(false);

    sc_signal<sc_uint<SIZE>> four;
    four.write(4);

    sc_signal<sc_uint<SIZE>> zero;
    zero.write(0);

    sc_signal<sc_uint<SIZE>> one;
    one.write(1);

    // stage 1
    FETCH_INSTRUCTION_MEMORY.load_contents("add.bin");
    FETCH_ADDER.A(four);
    FETCH_ADDER.B(program_counter);
    FETCH_ADDER.Cin(false_sig);
    FETCH_ADDER.C(next_pc);
    // FETCH_ADDER.Cout();  // ignore

    FETCH_PC.pc_in(pc_in);
    FETCH_PC.ld_pc(wren_pc);
    FETCH_PC.clock(clock);
    FETCH_PC.pc_out(program_counter);

    FETCH_MUX.inputs.at(0)(next_pc);
    FETCH_MUX.inputs.at(1)(pc_branch);
    sc_signal<int> fetch_sel_in;
    fetch_sel_in.write((int) (is_branch.read() && b_cond.read()) || (is_jalx.read()));
    FETCH_MUX.sel(fetch_sel_in);
    FETCH_MUX.Z(pc_in);

    // TODO: load IM contents from binary file
    FETCH_INSTRUCTION_MEMORY.address(program_counter);
    FETCH_INSTRUCTION_MEMORY.out(ft_instruction);

    IF_ID.pc_cur(program_counter);
    IF_ID.inst(ft_instruction);
    IF_ID.next_pc(next_pc);
    IF_ID.clk(clock);
    IF_ID.wren(wren_reg_ID);
    IF_ID.rst(id_flush);
    
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
    DECODE_BREG.rd(wb_rd);
    DECODE_BREG.d_in(wb_mux_data);
    DECODE_BREG.ra(breg_ra);
    DECODE_BREG.rb(breg_rb);
    DECODE_BREG.wren(f_breg_wr);
    DECODE_BREG.clk(clock);
    DECODE_MUX_RETURN_ADDRESS.inputs.at(0)(id_imm_ws);
    DECODE_MUX_RETURN_ADDRESS.inputs.at(1)(id_next_pc);
    sc_signal<int> decode_mux_ra_sel;
    decode_mux_ra_sel.write((int) is_jal.read());
    DECODE_MUX_RETURN_ADDRESS.sel(decode_mux_ra_sel);
    DECODE_MUX_RETURN_ADDRESS.Z(return_addr);

    DECODE_MUX_ADDER.inputs.at(0)(id_pc);
    DECODE_MUX_ADDER.inputs.at(1)(breg_ra);
    sc_signal<int> decode_mux_adder_sel;
    decode_mux_adder_sel.write((int) is_jalr.read());
    DECODE_MUX_ADDER.sel(decode_mux_adder_sel);
    DECODE_MUX_ADDER.Z(jump_addr);

    DECODE_ADDER.A(jump_addr);
    DECODE_ADDER.B(id_imm_ws);
    DECODE_ADDER.C(pc_branch);
    DECODE_ADDER.Cin(false_sig);

    DECODE_GENIMM32.instruction(id_instruction);
    DECODE_GENIMM32.imm(id_imm_ws);

    DECODE_MUX_DBRANCH_A.inputs.at(0)(breg_ra);
    DECODE_MUX_DBRANCH_A.inputs.at(1)(wb_mux_data);
    sc_signal<int> decode_mux_dbranch_ra_sel;
    decode_mux_dbranch_ra_sel.write((int) sel_mux_ra_dbranch.read());
    DECODE_MUX_DBRANCH_A.sel(decode_mux_dbranch_ra_sel);
    DECODE_MUX_DBRANCH_A.Z(mux_dbranch_ra);

    DECODE_MUX_DBRANCH_B.inputs.at(0)(breg_rb);
    DECODE_MUX_DBRANCH_B.inputs.at(1)(wb_mux_data);
    sc_signal<int> decode_mux_dbranch_rb_sel;
    decode_mux_dbranch_rb_sel.write((int) sel_mux_rb_dbranch.read());
    DECODE_MUX_DBRANCH_B.sel(decode_mux_dbranch_rb_sel);
    DECODE_MUX_DBRANCH_B.Z(mux_dbranch_rb);

    DECODE_DFORWARD.rs1(id_rs1);
    DECODE_DFORWARD.rs2(id_rs2);
    DECODE_DFORWARD.rd(mem_rd);
    DECODE_DFORWARD.rAOut(sel_mux_ra_dbranch);
    DECODE_DFORWARD.rBOut(sel_mux_rb_dbranch);

    DECODE_DBRANCH.ra(mux_dbranch_ra);
    DECODE_DBRANCH.rb(mux_dbranch_rb);
    DECODE_DBRANCH.opcode(b_opcode);
    DECODE_DBRANCH.Bout(b_cond);

    ID_EX.id_rs1(id_rs1);
    ID_EX.id_rs2(id_rs2);
    ID_EX.id_rd(id_rd);
    ID_EX.id_imm(return_addr);
    ID_EX.id_regA(breg_ra);
    ID_EX.id_regB(breg_rb);
    ID_EX.id_pc(id_pc);
    ID_EX.clk(clock);
    // ID_EX.wren(one);
    // ID_EX.rst(zero);
    ID_EX.wren(true_sig);
    ID_EX.rst(ex_flush);
    sc_signal<sc_uint<7>> id_ex_funct7;
    sc_signal<sc_uint<3>> id_ex_funct3;
    id_ex_funct7.write(((id_instruction.read())(31, 25)));
    id_ex_funct3.write(((id_instruction.read())(14, 12)));
    ID_EX.id_funct7(id_ex_funct7);
    ID_EX.id_funct3(id_ex_funct3);
    ID_EX.id_ex_ctrl(ex_ctrl);
    ID_EX.id_mem_ctrl(ex_mem_ctrl);
    ID_EX.id_wb_ctrl(ex_wb_ctrl);
    // stage 3

    ID_EX.ex_rs1(ex_rs1);
    ID_EX.ex_rs2(ex_rs2);
    ID_EX.ex_rd(ex_rd);
    ID_EX.ex_imm(ex_imm);
    ID_EX.ex_regA(ex_ra);
    ID_EX.ex_regB(ex_rb);
    ID_EX.ex_pc(ex_pc);
    ID_EX.ex_funct7(ex_funct7);
    ID_EX.ex_funct3(ex_funct3);
    ID_EX.mem_ctrl(ex_to_mem_m);
    ID_EX.wb_ctrl(ex_to_mem_wb);
    ID_EX.alu_op(alu_op);
    ID_EX.alu_src_A(sel_alu_A);
    ID_EX.alu_src_B(sel_alu_B);
    
    EXECUTE_MUX_FORWARDA.inputs.at(0)(ex_ra);
    EXECUTE_MUX_FORWARDA.inputs.at(1)(wb_mux_data);
    EXECUTE_MUX_FORWARDA.inputs.at(2)(mem_alu_out);
    sc_signal<int> execute_mux_forwarda_sel;
    execute_mux_forwarda_sel.write((forward_a).read());
    EXECUTE_MUX_FORWARDA.sel(execute_mux_forwarda_sel);
    EXECUTE_MUX_FORWARDA.Z(mux_forward_a);
    
    EXECUTE_MUX_FORWARDB.inputs.at(0)(ex_rb);
    EXECUTE_MUX_FORWARDB.inputs.at(1)(wb_mux_data);
    EXECUTE_MUX_FORWARDB.inputs.at(2)(mem_alu_out);
    sc_signal<int> execute_mux_forwardb_sel;
    execute_mux_forwarda_sel.write((forward_b).read());
    EXECUTE_MUX_FORWARDB.sel(execute_mux_forwardb_sel);
    EXECUTE_MUX_FORWARDB.Z(mux_forward_b);

    EXECUTE_MUX_ALUA.inputs.at(0)(zero);
    EXECUTE_MUX_ALUA.inputs.at(1)(ex_pc);
    EXECUTE_MUX_ALUA.inputs.at(2)(mux_forward_a);
    sc_signal<int> execute_mux_alua_sel;
    execute_mux_alua_sel.write(sel_alu_A.read());
    EXECUTE_MUX_ALUA.sel(execute_mux_alua_sel);
    EXECUTE_MUX_ALUA.Z(mux_alu_a);
    
    EXECUTE_MUX_ALUB.inputs.at(0)(mux_forward_b);
    EXECUTE_MUX_ALUB.inputs.at(1)(ex_imm);
    sc_signal<int> execute_mux_alub_sel;
    execute_mux_alub_sel.write(sel_alu_B.read());
    EXECUTE_MUX_ALUB.sel(execute_mux_alub_sel);
    EXECUTE_MUX_ALUB.Z(mux_alu_b);

    EXECUTE_EFORWARD.ID_EX_rs1(ex_rs1);
    EXECUTE_EFORWARD.ID_EX_rs2(ex_rs2);
    EXECUTE_EFORWARD.EX_MEM_rd(mem_rd);
    EXECUTE_EFORWARD.MEM_WB_rd(wb_rd);
    EXECUTE_EFORWARD.EX_MEM_write(mem_wr_en);
    EXECUTE_EFORWARD.MEM_WB_write(f_breg_wr);
    EXECUTE_EFORWARD.forwardA(forward_a);
    EXECUTE_EFORWARD.forwardB(forward_b);

    EXECUTE_ALUCONTROL.ex_funct7(ex_funct7);
    EXECUTE_ALUCONTROL.ex_funct3(ex_funct3);
    EXECUTE_ALUCONTROL.alu_op(alu_op);
    EXECUTE_ALUCONTROL.opcode_alu(opcode_alu);

    EXECUTE_ULA.A(mux_alu_a);
    EXECUTE_ULA.B(mux_alu_b);
    EXECUTE_ULA.Z(alu_out);
    EXECUTE_ULA.opcode(opcode_alu);
    EXECUTE_ULA.zero(zero_alu);

    EX_MEM.ex_rd(ex_rd);
    EX_MEM.ex_rs2(ex_rs2);
    EX_MEM.ex_alu_out(alu_out);
    EX_MEM.ex_mux_alu_b(mux_forward_b);
    EX_MEM.ex_mem_ctrl(ex_to_mem_m);
    EX_MEM.ex_wb_ctrl(ex_to_mem_wb);
    EX_MEM.clk(clock);
    // EX_MEM.wren(one);
    // EX_MEM.rst(zero);
    EX_MEM.wren(true_sig);
    EX_MEM.rst(false_sig);

    // stage 4

    EX_MEM.rd_en(mem_rd_en);
    EX_MEM.wr_en(mem_wr_en);
    EX_MEM.d_size(mem_data_size);
    EX_MEM.mem_wb_ctrl(mem_to_wb);
    EX_MEM.mem_rd(mem_rd);
    EX_MEM.mem_rs2(mem_rs2);
    EX_MEM.mem_alu_out(mem_alu_out);
    EX_MEM.mem_mux_alu_b(mem_mux_alu_b);

    MUX_MEM.inputs.at(0)(mem_mux_alu_b);
    MUX_MEM.inputs.at(1)(wb_mux_data);
    sc_signal<int> mem_mux_data_sel;
    mem_mux_data_sel.write(sel_mux_mem.read());
    MUX_MEM.sel(mem_mux_data_sel);
    MUX_MEM.Z(mdata);
        
    DATA_MEMORY.rd_en(mem_rd_en);
    DATA_MEMORY.wr_en(mem_wr_en);
    DATA_MEMORY.d_size(mem_data_size);
    DATA_MEMORY.mem_addr(mdata);
    sc_signal<sc_uint<IMMSIZE>> data_mem_imm_zero;
    data_mem_imm_zero.write(0);
    DATA_MEMORY.imm(data_mem_imm_zero);
    DATA_MEMORY.wr_data(mem_alu_out);
    DATA_MEMORY.mem_out(dm_out);
    DATA_MEMORY.clk(clock);

    MEM_WB.wb_ctrl(mem_to_wb);
    MEM_WB.mem_rd(mem_rd);
    MEM_WB.mem_alu_out(mem_alu_out);
    MEM_WB.mem_mdata_out(dm_out);
    MEM_WB.clk(clock);
    MEM_WB.wren(true_sig);
    MEM_WB.rst(false_sig);

    MEM_MFORWARD.mem_rs2(mem_rs2);
    MEM_MFORWARD.wb_rd(wb_rd);
    MEM_MFORWARD.f_breg_wr(f_breg_wr);
    MEM_MFORWARD.sel_mux_mem(sel_mux_mem);

    // stage 5

    MEM_WB.mux_data(wb_sel_mux);
    MEM_WB.breg_wr(f_breg_wr);
    MEM_WB.wb_rd(wb_rd);
    MEM_WB.wb_alu_out(wb_alu_out);
    MEM_WB.wb_mdata_out(wb_md_out);

    WB_MUX.inputs.at(0)(wb_md_out);
    WB_MUX.inputs.at(1)(wb_alu_out);
    sc_signal<int> wb_mux_sel;
    wb_mux_sel.write((wb_sel_mux).read());
    WB_MUX.sel(wb_mux_sel);
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
    CONTROLLER.ex_ctrl(ex_ctrl);
    CONTROLLER.mem_ctrl(ex_mem_ctrl);
    CONTROLLER.wb_ctrl(ex_wb_ctrl);
    
  }
};
