#include "pc/pc_tb.hpp"

void pc_tb::activate(void) {
  std::cout << "PC testbench\n";
  ld_pc.write(0);
  clock.write(0);
  std::cout << "pc_out: " << std::hex << pc_out.read() << std::endl;

  wait(1, SC_NS);
  clock.write(1);
  wait(1, SC_NS);
  clock.write(0);
  std::cout << "pc_out: " << std::hex << pc_out.read() << std::endl;

  wait(1, SC_NS);
  clock.write(1);
  wait(1, SC_NS);
  clock.write(0);
  std::cout << "pc_out: " << std::hex << pc_out.read() << std::endl;

  wait(1, SC_NS);
  clock.write(1);
  wait(1, SC_NS);
  clock.write(0);
  std::cout << "pc_out: " << std::hex << pc_out.read() << std::endl;

  std::cout << "Loading value into pc\n";
  wait(1, SC_NS);
  ld_pc.write(1);
  pc_in.write(0x0000BEEF);
  clock.write(1);
  wait(1, SC_NS);
  clock.write(0);
  ld_pc.write(0);
  wait(1, SC_NS);
  std::cout << "pc_out: " << std::hex << pc_out.read() << std::endl;

  wait(1, SC_NS);
  clock.write(1);
  wait(1, SC_NS);
  clock.write(0);
  wait(1, SC_NS);
  std::cout << "pc_out: " << std::hex << pc_out.read() << std::endl;

  wait(1, SC_NS);
  clock.write(1);
  wait(1, SC_NS);
  clock.write(0);
  wait(1, SC_NS);
  std::cout << "pc_out: " << std::hex << pc_out.read() << std::endl;
}