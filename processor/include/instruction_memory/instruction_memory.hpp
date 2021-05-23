#ifndef __INSTRUCTION_MEMORY_H
#define __INSTRUCTION_MEMORY_H

#include <systemc.h>
#include <fstream>
#include <iterator>
#include <vector>
#include "top/macros.hpp"

#define MEMSIZE 256 // in words

SC_MODULE(InstructionMemory) {
  sc_in<sc_uint<32>> address; // pc signal goes here
  sc_out<sc_uint<32>> out;   // goes to ft_instruction 

  void read_data();
  void load_contents(std::string filename);
  std::vector<char> readBytes(std::string filename);

  std::vector<sc_uint<32>> data;

  SC_CTOR(InstructionMemory) {
    SC_METHOD(read_data);

    // load_contents("instruction_memory.bin");
    sensitive << address;
  }
};

#endif
