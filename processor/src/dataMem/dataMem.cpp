#include "dataMem/dataMem.hpp"

void dataMem::store() {
  if(wr_en == 1) {
    // Read values
    int32_t kte = 0;
    sc_uint<3> data_size = d_size.read();
    int32_t write_data = wr_data.read();

    // Auxiliary
    uint32_t write_addr;
    int32_t mem_content;
    int32_t position;
    int32_t mask;

    // Add kte with address
    kte += (int32_t)mem_addr.read();
    uint32_t address = (uint32_t)kte;

    // Verify boundaries of base addr
    if(address < BASEADDR) {
      std::cout << "Error: Memory address out of boundaries\n";
      return;
    }

    // Get real address
    address -= BASEADDR;
    write_addr = address;

    switch(data_size(2, 1)) {
      case 0:
      // BYTE (sb)
        // Get word address where byte is
        while(write_addr % 4 != 0){
          write_addr--;
        }

        // Get memory content
        mem_content = memory[write_addr/4];

        // Get difference between memory address and byte addess
        position = address - write_addr;

        // Mask With what will continue on memory
        switch(position){
          case 0:
            mask = 0xFFFFFF00;
            break;
          case 1:
            mask = 0xFFFF00FF;
            break;
          case 2:
            mask = 0xFF00FFFF;
            break;
          case 3:
            mask = 0x00FFFFFF;
            break;
        }

        // Shift data to appropiate position
        write_data = write_data << 8*position;

        // Mask data
        mem_content &= mask;
        write_data &= ~(mask);

        write_data += mem_content;

        break; // BYTE

      case 1:
      // HALF (sh)
        // Verify if address is aligned with memory
        if(address % 2 != 0){
          printf("WARNING: Store address not aligned to halfword boundary\n");
        }

        // Get word address where halfword is
        while(write_addr % 4 != 0){
          write_addr -= 2;
        }

        // Get memory content
        mem_content = memory[write_addr/4];

        // Get difference between memory address and byte addess
        position = address - write_addr;

        // Mask With what will continue on memory
        switch(position){
          case 0:
            mask = 0xFFFF0000;
            break;
          case 2:
            mask = 0x0000FFFF;
            break;
        }

        // Shift data to appropiate position
        write_data = write_data << 8*position;

        // Mask data
        mem_content &= mask;
        write_data &= ~(mask);

        write_data += mem_content;
        break; // HALF

      case 2:
      // WORD (sw)
        // Verify if address is aligned with memory
        if(address % 4 != 0){
          printf("WARNING: Store address not aligned to word boundary\n");
        }
        break; // WORD
    }      
    
    memory[write_addr/4] = write_data;
  }
}

void dataMem::load() {
  if(rd_en == 1){
    // Read values
    int32_t kte = 0;
    sc_uint<3> data_size = d_size.read();

    // Auxiliary
    int32_t data;
    uint32_t load_addr;
    int32_t position;
    uint32_t udata;

    // Add kte with address
    kte += (int32_t)mem_addr.read();
    uint32_t address = (uint32_t)kte;

    // Verify boundaries of base addr
    if(address < BASEADDR) {
      std::cout << "Error: Memory address out of boundaries\n";
      return;
    }

    // Get real address
    address -= BASEADDR;
    load_addr = address;

    switch(data_size(2, 1)) {
      case 0:
      // BYTE
        // Get word address where byte is
        while(load_addr % 4 != 0){
          load_addr--;
        }

        // Get byte position
        position = address - load_addr;

        if(data_size[0] == 1) {
          // SIGNED (LB)
          data = memory[load_addr/4];

          // Shift according to position
          data = data << 8*(3-position);
          data = data >> 24;
        } // LB
        else {
          // UNSIGNED (LBU)
          udata = (uint32_t)memory[load_addr/4];

          // Shift according to position
          udata = udata << 8*(3-position);
          udata = udata >> 24;

          data = (int32_t)udata;
        } // LBU
        break; // BYTE

      case 1:
      // HALF
        // Verify if address is aligned with memory
        if(address % 2 != 0){
          printf("WARNING: Load address not aligned to halfword boundary\n");
        }

        // Get word address where halfword is
        if( load_addr % 4 != 0){
            load_addr -= 2;
        }

        if(data_size[0] == 1) {
          // SIGNED (LH)
          data = memory[load_addr/4];

          // When halford is on the least significant half
          if(load_addr == address) {
            data = data << 16;
          }
          data = data >> 16;
        } // LH
        else {
          // UNSIGNED (LHU)
          udata = (uint32_t)memory[load_addr/4];

          // When halford is on the least significant half
          if(load_addr == address) {
            udata = udata << 16;
          }
          udata = udata >> 16;

          data = (int32_t)udata;
        } // LHU
        break; // HALF

      case 2:
      // WORD
        // Verify if address is aligned with memory
        if(address % 4 != 0){
          printf("WARNING: Load address not aligned to word boundary\n");
        }

        data = memory[load_addr/4];
        break; // WORD
    }

    mem_out.write(data);
  }
}
