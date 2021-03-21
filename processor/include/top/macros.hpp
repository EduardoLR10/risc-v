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
    I_type
} FORMAT_RV;

#endif
