#include "instruction_memory/instruction_memory_tb.hpp"

void InstructionMemoryTB::activate()
{
  // wait for memory contents to be read
  std::cout << "Hello from IM testbench!\n";
  clock = 0;
  wait(10, SC_NS); 

  address = 0x00000000;
  clock = 1;
  wait(1, SC_NS);
  clock = 0;
  std::cout << "address = " << std::setw(W) << std::hex << address.read();
  std::cout << "\toutput = " << out.read() << std::endl
            << std::endl;

  address = 0x00000004;
  clock = 1;
  wait(1, SC_NS);
  clock = 0;
  std::cout << "address = " << std::setw(W) << std::hex << address.read();
  std::cout << "\toutput = " << out.read() << std::endl
            << std::endl;

  address = 0x00000008;
  clock = 1;
  wait(1, SC_NS);
  clock = 0;
  std::cout << "address = " << std::setw(W) << std::hex << address.read();
  std::cout << "\toutput = " << out.read() << std::endl
            << std::endl;

  address = 0x0000000c;
  clock = 1;
  wait(1, SC_NS);
  clock = 0;
  std::cout << "address = " << std::setw(W) << std::hex << address.read();
  std::cout << "\toutput = " << out.read() << std::endl
            << std::endl;
}