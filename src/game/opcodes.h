
#ifndef GAME_OPCODES_H_
#define GAME_OPCODES_H_

#define JP_a16 0xC3

#define LD_d8 0x3E

#define LD_B_d8 0x06

#define LD_C_d8 0x0E

#define LD_a16_A 0xEA

#define LD_A_a16 0xFA

#define CP_d8 0xFE

#define PUSH_BC 0xC5

#define JP_C_a16 0xDA

#define LD_BC_d16 0x01

#define LD_DE_d16 0x11

#define LD_HL_d16 0x21

#define LD_A_aDE 0x1A

#define LD_aHLI_A 0x22

#define INC_DE 0x13

#define DEC_BC 0x0B

#define LD_A_B 0x78

#define OR_A_C 0xB1

#define JP_NZ_a16 0xC2

#define JP_Z_a16 0xCA

#define CALL_a16 0xCD

#endif  // GAME_OPCODES_H_
