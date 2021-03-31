#include "instruction_memory/instruction_memory.h"

void InstructionMemory::read_data()
{
  out = data[address.read()];
}

void InstructionMemory::load_contents(std::string filename)
{
  // std::ifstream input(filename, std::ios::binary);
  // std::vector<uint8_t> bytes(
  //     (std::istreambuf_iterator<uint8_t>(input)),
  //     (std::istreambuf_iterator<uint8_t>()));

  auto bytes = readBytes(filename);

  if (bytes.size() % 4 != 0) {
    std::cout << "Warning: ROM includes incomplete word\n";
  }

  // read words
  uint32_t word = 0;
  uint32_t i = 0;
  while (i < 4*MEMSIZE && i < bytes.size()) {
    // read for bytes from input
    for (uint32_t j = 0; j < 4; j++) {
      word += bytes[i+j];
      word <<= 8;
    }
    data[i / 4] = word;
    i += 4;
  }
}

std::vector<uint8_t> InstructionMemory::readBytes(std::string filename)
{
    ifstream ifs(filename, ios::binary|ios::ate);
    ifstream::pos_type pos = ifs.tellg();

    std::vector<char> result(pos);

    ifs.seekg(0, ios::beg);
    ifs.read(&result[0], pos);

    std::vector<uint8_t> bytes;

    auto char_to_uint8_t = [](char c) { return (uint8_t) c; };

    std::transform(result.begin(), result.end(), std::back_inserter(bytes), char_to_uint8_t);

    return bytes;
}