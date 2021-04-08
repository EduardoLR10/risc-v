#include "instruction_memory/instruction_memory.hpp"

void InstructionMemory::read_data()
{
  out = data[address.read() / 4];
}

void InstructionMemory::load_contents(std::string filename)
{
  auto bytes = readBytes(filename);

  if (bytes.size() % 4 != 0)
  {
    std::cout << "Warning: ROM includes incomplete word\n";
  }

  // read words into memory
  uint32_t i;
  for (i = 0; i < 4*MEMSIZE && i < bytes.size(); i += 4) {
    // read for bytes from input
    data[i/4] = (((uint8_t) bytes[i])   << 24)
              + (((uint8_t) bytes[i+1]) << 16)
              + (((uint8_t) bytes[i+2]) << 8 )
              + (((uint8_t) bytes[i+3])      );
  }
}

std::vector<char> InstructionMemory::readBytes(std::string filename)
{
  std::ifstream file(filename, std::ios::binary);
  return std::vector<char>((std::istreambuf_iterator<char>(file)),
                            std::istreambuf_iterator<char>());
}