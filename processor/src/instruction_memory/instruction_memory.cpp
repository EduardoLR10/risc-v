#include "instruction_memory/instruction_memory.hpp"

void InstructionMemory::read_data()
{
  uint32_t addr = address.read();
  if (addr % 4 != 0)
  {
    std::cout << "Warning: Instruction memory read address is not a multiple of 4\n";
  }
  out = data[addr / 4];
}

void InstructionMemory::load_contents(std::string filename)
{
  std::vector<char> bytes = readBytes(filename);

  if (bytes.size() % 4 != 0)
  {
    std::cout << "Warning: ROM includes incomplete word (" << bytes.size() << " bytes)\n";
  }

  // read words into memory
  uint32_t i;
  for (i = 0; i < 4*MEMSIZE && i < bytes.size(); i += 4) {
    // read for bytes from input
    data[i/4] = (((uint8_t) bytes[i])   )
              + (((uint8_t) bytes[i+1]) << 8 )
              + (((uint8_t) bytes[i+2]) << 16 )
              + (((uint8_t) bytes[i+3]) << 24 );
  }
  for (uint32_t j = 0; j < i/4; j++)
      printf("%08x \t%08x\n", j, data[j].to_uint());
}

std::vector<char> InstructionMemory::readBytes(std::string filename)
{
  std::ifstream file(filename, std::ios::binary);
  return std::vector<char>((std::istreambuf_iterator<char>(file)),
                            std::istreambuf_iterator<char>());
}