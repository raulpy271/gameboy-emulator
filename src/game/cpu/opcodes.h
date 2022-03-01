
#ifndef GAME_OPCODES_H_
#define GAME_OPCODES_H_

#define JP_a16 0xC3

#define LD_d8 0x3E

#define LD_B_d8 0x06

#define LD_C_d8 0x0E

#define LD_a8_A 0xE0

#define LD_a16_A 0xEA

#define LD_A_a16 0xFA

#define LD_aC_A 0xE2

#define CP_d8 0xFE

#define PUSH_BC 0xC5

#define JP_C_a16 0xDA

#define LD_BC_d16 0x01

#define LD_DE_d16 0x11

#define LD_HL_d16 0x21

#define LD_A_aDE 0x1A

#define LD_A_aHL 0x7E

#define LD_aHL_A 0x77

#define LD_aHLI_A 0x22

#define INC_A 0x3C

#define INC_DE 0x13

#define INC_HL 0x23

#define DEC_C 0x0D

#define DEC_BC 0x0B

#define LD_A_B 0x78

#define LD_A_C 0x79

#define LD_C_A 0x4F

#define LD_B_A 0x47

#define ADD_HL_BC 0x09

#define OR_A_B 0xB0

#define OR_A_C 0xB1

#define XOR_A_A 0xAF

#define JR_NZ_s8 0x20

#define JP_NZ_a16 0xC2

#define JP_Z_a16 0xCA

#define CALL_a16 0xCD

#define RET 0xC9

#define RET_Z 0xC8

#define JR_s8 0x18

#define IE 0xFB

#define DI 0xF3

#endif  // GAME_OPCODES_H_
