#ifndef __MACROS__
#define __MACROS__

#define SIZE 32
#define W (SIZE / 4)

#define WSIZE 32
#define BSIZE 4

#define DATAMEMSIZE 128
#define BASEADDR 0x2000
#define IMMSIZE 12

typedef enum {
    R_type = 0x33,
    S_type = 0x23,
    SB_type = 0x63,
    UJ_type = 0x6F,
    U_type = 0x37,
    AU_type = 0x17,
    I_type
} FORMAT_RV;


typedef enum {
    LUI = 0x37,		AUIPC = 0x17,		// atribui 20 msbits
    ILType = 0x03,						// Load type
    BType = 0x63,						// branch condicional
    JAL = 0x6F,		JALR = 0x67,		// jumps
    StoreType = 0x23,					// store
    ILAType = 0x13,						// logico-aritmeticas com imediato
    RegType = 0x33,
    ECALL = 0x73,
    NOP = 0x00
} OPCODES;

typedef enum {
    I_add,	I_addi, I_and,  I_andi, I_auipc,
    I_beq,	I_bge,	I_bgeu, I_blt,  I_bltu,
    I_bne,  I_jal,	I_jalr, I_lb,	I_lbu,
    I_lw,   I_lh,   I_lhu,  I_lui,  I_sb,
    I_sh,   I_sw,   I_sll,  I_slt,  I_slli,
    I_srl,  I_sra,  I_sub,  I_slti, I_sltiu,
    I_xor,	I_or,	I_srli, I_srai,  I_sltu,
    I_ori, I_ecall, I_xori, I_nop
} INSTRUCTIONS;

typedef enum { RType, IType, SType, SBType, UType, UJType, NullFormat, NOPType } FORMATS;

typedef enum {
    BEQ3=0,		BNE3=01,	BLT3=04,	BGE3=05,	BLTU3=0x06, BGEU3=07,
    LB3=0,		LH3=01,		LW3=02,		LBU3=04,	LHU3=05,
    SB3=0,		SH3=01,		SW3=02,
    ADDSUB3=0,	SLL3=01,	SLT3=02,	SLTU3=03,
    XOR3=04,	SR3=05,		OR3=06,		AND3=07,
    ADDI3=0,	ORI3=06,	SLTI3=02,	XORI3=04,	ANDI3=07,
    SLTIU3=03,	SLLI3=01,	SRI3=05
} FUNCT3;

typedef enum {
    ADD7=0,	SUB7=0x20,	SRA7=0x20,	SRL7=0, SRLI7=0x00,	SRAI7=0x20
} FUNCT7;

typedef enum {
    BYTE_SIZE = 0, HALF_SIZE = 1, WORD_SIZE = 2, DOUBLE_SIZE = 3
} WORD_SIZE_E;

typedef enum {
    BEQ = 0,
    BNE = 1,
    BLT = 2,
    BGE = 3
} FORMAT_BRANCH;

typedef enum {
    ULA_ADD, ULA_SUB, ULA_AND, ULA_OR, ULA_XOR, ULA_NOR, ULA_SLL, ULA_SRL, ULA_SRA,
    ULA_SLT, ULA_SLTU, ULA_SGE, ULA_SGEU, ULA_SEQ, ULA_SNE
} ULA_OPCODE;


#endif
