#include "genImm32/genImm32.hpp"

void genImm32::proc() {
	sc_int<SIZE> ins;
    sc_int<SIZE> im;

    ins = instruction.read();

    switch(ins(6, 0)){
        case R_type:
            im = 0;
            break;
        case S_type:
            im = (sc_int<20>(ins[31]),ins(31,25),ins(11,7));
            break;
        case SB_type:
            im = ((ins[31] ? (sc_int<19>(-1)) : (sc_int<19>(0))), ins[31], ins[7], ins(30, 25), ins(11,8), 0);
            break;
        case AU_type:
        case U_type:
            im = (ins(31, 12), sc_int<12>(0));
            break;
        case UJ_type:
            im = ((ins[31] ? (sc_int<12>(-1)) : (sc_int<12>(0))), ins[31], ins(19, 12), ins[20], ins(30, 21), 0);
            break;
        // case I_type:
        default:
            sc_int<3> funct3 = ins(14, 12);
            if(funct3 == 1 || funct3 == 5){
                im = ((ins[31] ? (sc_int<27>(-1)) : (sc_int<27>(0))), ins(24, 20));
            } else {
                im = ((ins[31] ? (sc_int<20>(-1)) : (sc_int<20>(0))), ins(31, 20));
            }
            break;
    }
	imm.write((im).to_uint());
	
}
