#ifndef __MACROS__
#define __MACROS__

#define SIZE 32
#define W (SIZE / 4)

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
    BEQ = 0,
    BNE = 1,
    BLT = 2,
    BGE = 3
} FORMAT_BRANCH;

#endif
