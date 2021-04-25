#include "dataMem/dataMem_tb.hpp"

void dataMem_tb::execute() {
  std::cout << "Starting dataMem test\n";

  // Store on memory
  rd_en = 0;
  wr_en = 1;
  // SW
  d_size = 4; //0b100
  mem_addr = 0x2000;
  imm = 0;
  wr_data = 0xCAFEB010;
  wait(10, SC_NS);
  // SW + imm
  imm = 0x4;
  wr_data = 0xABBADADA;
  wait(10, SC_NS);
  // SH
  d_size = 2; //0b010
  mem_addr = 0x2008;
  imm = 0;
  wr_data = 0xB01A;
  wait(10, SC_NS);
  // SH + imm
  imm = 0x2;
  wr_data = 0x3229;
  wait(10, SC_NS);
  // SB
  d_size = 0; //0b000s
  mem_addr = 0x200F;
  imm = 0;
  wr_data = 0xD4;
  wait(10, SC_NS);
  // SB + imm
  imm = -0x1;
  wr_data = 0x12;
  wait(10, SC_NS);
  // SB + imm
  imm = -0x2;
  wr_data = 0xAB;
  wait(10, SC_NS);
  // SB + imm
  imm = -0x3;
  wr_data = 0x69;
  wait(10, SC_NS);
  
  // Load from memory
  wr_en = 0;
  rd_en = 1;
  // LW
  d_size = 4; //0b100
  imm = 0;
  mem_addr = 0x2000;
  wait(10, SC_NS);
  std::cout << "address = " << std::setw(W) << std::hex << mem_addr.read();
  std::cout << "\timm = " << std::setw(W) << std::hex << imm.read();
  std::cout << "\toutput = " << mem_out.read() << std::endl;
  std::cout << "\texpected = " << "0xCAFEB010" << std::endl;
  // LW + imm
  imm = 4;
  wait(10, SC_NS);
  std::cout << "address = " << std::setw(W) << std::hex << mem_addr.read();
  std::cout << "\timm = " << std::setw(W) << std::hex << imm.read();
  std::cout << "\toutput = " << mem_out.read() << std::endl;
  std::cout << "\texpected = " << "0xABBADADA" << std::endl;
  // LH
  d_size = 3; //0b011
  mem_addr = 0x2008;
  imm = 0;
  wait(10, SC_NS);
  std::cout << "address = " << std::setw(W) << std::hex << mem_addr.read();
  std::cout << "\timm = " << std::setw(W) << std::hex << imm.read();
  std::cout << "\toutput = " << mem_out.read() << std::endl;
  std::cout << "\texpected = " << "0xFFFFB01A" << std::endl;
  // LH + imm
  imm = 2;
  wait(10, SC_NS);
  std::cout << "address = " << std::setw(W) << std::hex << mem_addr.read();
  std::cout << "\timm = " << std::setw(W) << std::hex << imm.read();
  std::cout << "\toutput = " << mem_out.read() << std::endl;
  std::cout << "\texpected = " << "0x00003229" << std::endl;
  // LHU
  d_size = 2; //0b010
  imm = 0;
  wait(10, SC_NS);
  std::cout << "address = " << std::setw(W) << std::hex << mem_addr.read();
  std::cout << "\timm = " << std::setw(W) << std::hex << imm.read();
  std::cout << "\toutput = " << mem_out.read() << std::endl;
  std::cout << "\texpected = " << "0x0000B01A" << std::endl;
  // LHU + imm
  imm = 2;
  wait(10, SC_NS);
  std::cout << "address = " << std::setw(W) << std::hex << mem_addr.read();
  std::cout << "\timm = " << std::setw(W) << std::hex << imm.read();
  std::cout << "\toutput = " << mem_out.read() << std::endl;
  std::cout << "\texpected = " << "0x00003229" << std::endl;
  // LB
  d_size = 1; //0b001
  mem_addr = 0x200F;
  imm = 0;
  wait(10, SC_NS);
  std::cout << "address = " << std::setw(W) << std::hex << mem_addr.read();
  std::cout << "\timm = " << std::setw(W) << std::hex << imm.read();
  std::cout << "\toutput = " << mem_out.read() << std::endl;
  std::cout << "\texpected = " << "0xFFFFFFD4" << std::endl;
  // LB + imm
  imm = -0x1;
  wait(10, SC_NS);
  std::cout << "address = " << std::setw(W) << std::hex << mem_addr.read();
  std::cout << "\timm = " << std::setw(W) << std::hex << imm.read();
  std::cout << "\toutput = " << mem_out.read() << std::endl;
  std::cout << "\texpected = " << "0x00000012" << std::endl;
  // LBU
  d_size = 0; //0b000
  imm = 0;
  wait(10, SC_NS);
  std::cout << "address = " << std::setw(W) << std::hex << mem_addr.read();
  std::cout << "\timm = " << std::setw(W) << std::hex << imm.read();
  std::cout << "\toutput = " << mem_out.read() << std::endl;
  std::cout << "\texpected = " << "0x000000D4" << std::endl;
  // LBU + imm
  imm = -0x1;
  wait(10, SC_NS);
  std::cout << "address = " << std::setw(W) << std::hex << mem_addr.read();
  std::cout << "\timm = " << std::setw(W) << std::hex << imm.read();
  std::cout << "\toutput = " << mem_out.read() << std::endl;
  std::cout << "\texpected = " << "0x00000012" << std::endl;
  // LBU
  d_size = 0; //0b000
  imm = -0x2;
  wait(10, SC_NS);
  std::cout << "address = " << std::setw(W) << std::hex << mem_addr.read();
  std::cout << "\timm = " << std::setw(W) << std::hex << imm.read();
  std::cout << "\toutput = " << mem_out.read() << std::endl;
  std::cout << "\texpected = " << "0x000000AB" << std::endl;
  // LBU
  d_size = 0; //0b000
  imm = -0x3;
  wait(10, SC_NS);
  std::cout << "address = " << std::setw(W) << std::hex << mem_addr.read();
  std::cout << "\timm = " << std::setw(W) << std::hex << imm.read();
  std::cout << "\toutput = " << mem_out.read() << std::endl;
  std::cout << "\texpected = " << "0x00000069" << std::endl;
  // LW
  d_size = 4; //0b100
  imm = 0;
  mem_addr = 0x2008;
  wait(10, SC_NS);
  std::cout << "address = " << std::setw(W) << std::hex << mem_addr.read();
  std::cout << "\timm = " << std::setw(W) << std::hex << imm.read();
  std::cout << "\toutput = " << mem_out.read() << std::endl;
  std::cout << "\texpected = " << "0x3229B01A" << std::endl;
  // LW
  mem_addr = 0x200C;
  wait(10, SC_NS);
  std::cout << "address = " << std::setw(W) << std::hex << mem_addr.read();
  std::cout << "\timm = " << std::setw(W) << std::hex << imm.read();
  std::cout << "\toutput = " << mem_out.read() << std::endl;
  std::cout << "\texpected = " << "0xd412ab69" << std::endl;

  // Store on top
  rd_en = 0;
  wr_en = 1;
  // SH
  d_size = 2; //0b010
  mem_addr = 0x2000;
  imm = 0;
  wr_data = 0x8067;
  wait(10, SC_NS);
  // SB
  d_size = 0; //0b000
  mem_addr = 0x2005;
  imm = 0;
  wr_data = 0xC4;
  wait(10, SC_NS);

  rd_en = 1;
  wr_en = 0;
  // LW
  d_size = 4; //0b100
  imm = 0;
  mem_addr = 0x2000;
  wait(10, SC_NS);
  std::cout << "address = " << std::setw(W) << std::hex << mem_addr.read();
  std::cout << "\timm = " << std::setw(W) << std::hex << imm.read();
  std::cout << "\toutput = " << mem_out.read() << std::endl;
  std::cout << "\texpected = " << "0xCAFE8067" << std::endl;
  // LW
  d_size = 4; //0b100
  imm = 0;
  mem_addr = 0x2004;
  wait(10, SC_NS);
  std::cout << "address = " << std::setw(W) << std::hex << mem_addr.read();
  std::cout << "\timm = " << std::setw(W) << std::hex << imm.read();
  std::cout << "\toutput = " << mem_out.read() << std::endl;
  std::cout << "\texpected = " << "0xABBAC4DA" << std::endl;

}
