/*
 *  main.cpp
 *  RISCV
 *
 *  Created by Ricardo Jacobi on 26/01/11.
 *  Copyright 2011 Universidade de Brasilia. All rights reserved.
 *
 */

#include <iostream>
#include "globals.h"
#include "memoria.h"


using namespace std;

int main (int argc, const char * argv[]) {

    // **********************************************************
    // Debug:	ch = 'i' imprime instrucao decodificada
    //			ch = 'b' imprime banco de registradores
    //			ch = 'd' imprime ambos
    //			ch = 'f' encerra
    // **********************************************************

    /*
    char ch;

    init();

    mem[0] = 0x20102000;
    mem[1] = 0x8e080000;
    mem[2] = 0x8e090004;

    mem[2048] = 0xff000000;
    mem[2049] = 0x00ff0000;

    load_mem("code.bin", 0);
    load_mem("data.bin", 2048);

    dump_mem(0, 200, 'h');
    dump_mem(0x2000, 0x2020, 'h');

    // Set terminal to raw mode
    system("stty raw");

    //while ((ch=getchar()) != 'f')
    //	step(ch);

    run();

    cout << "\n\nResultado: \n";

    dump_mem(0x2000, 0x2020, 'h');
    */

    init();
    instruction_context_st ic;

    //uint32_t ri = 0x01c38333;
    //decode(ri, ic);
    //debug_decode(ic);
    //print_instr(ic);

    load_mem("code.bin", 0);
    load_mem("data.bin", 0x2000);

    //decode(mem[0], ic);
    //debug_decode(ic);


    for (int i =0; i < 20; i++) {
        fetch(ic);
        //cout  << "mem[" << i << "] =  " << x << endl;
        decode(ic);
        print_instr(ic);
        if (ic.ins_code == I_ecall) break;
    }

    run();
    /*

    dump_mem(0x2000, 0x2020, 'h');

    dump_asm(0, 20);

    run();

    dump_mem(0x2000, 0x2020, 'h');
     */

    return 0;
}
