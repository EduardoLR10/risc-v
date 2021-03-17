#include <systemc.h>
#include "genImm32/genImm32.hpp"
#include "genImm32/genImm32_tb.hpp"

SC_MODULE ( topGENIMM32 ) {

    genImm32_tb GENIMM32_tb;
    genImm32 GENIMM32;

    sc_signal< sc_int<SIZE> > instruction;
    sc_signal< sc_int<SIZE> > imm;

    SC_CTOR ( topGENIMM32 ) : GENIMM32_tb("GENIMM32_tb"), GENIMM32("GENIMM32") {
        GENIMM32.instruction(instruction); GENIMM32_tb.instruction(instruction);
        GENIMM32.imm(imm); GENIMM32_tb.imm(imm);
    }
};