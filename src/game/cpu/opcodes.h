
#ifndef GAME_OPCODES_H_
#define GAME_OPCODES_H_

#define NOP 0x00

#define HALT 0x76

#define JP_a16 0xC3

#define LD_d8 0x3E

#define LD_B_d8 0x06

#define LD_C_d8 0x0E

#define LD_a8_A 0xE0

#define LD_a16_A 0xEA

#define LD_A_a16 0xFA

#define LD_A_a8 0xF0

#define LD_aC_A 0xE2

#define CP_d8 0xFE

#define PUSH_BC 0xC5

#define PUSH_AF 0xF5

#define PUSH_DE 0xD5

#define PUSH_HL 0xE5

#define JP_C_a16 0xDA

#define LD_BC_d16 0x01

#define LD_DE_d16 0x11

#define LD_HL_d16 0x21

#define LD_SP_d16 0x31

#define LD_A_aDE 0x1A

#define LD_A_aHL 0x7E

#define LD_A_aHLI 0x2A

#define LD_aHL_A 0x77

#define LD_aHL_d8 0x36

#define LD_aHLI_A 0x22

#define LD_aHLD_A 0x32

#define INC_A 0x3C

#define INC_B 0x04

#define INC_C 0x0C

#define INC_D 0x14

#define INC_E 0x1C

#define INC_H 0x24

#define INC_L 0x2C

#define INC_aHL 0x34

#define INC_DE 0x13

#define INC_HL 0x23

#define DEC_A 0x3D

#define DEC_B 0x05

#define DEC_C 0x0D

#define DEC_BC 0x0B

#define LD_A_B 0x78

#define LD_H_A 0x67

#define LD_L_A 0x6F

#define LD_A_H 0x7C

#define LD_A_C 0x79

#define LD_A_L 0x7D

#define LD_C_A 0x4F

#define LD_D_A 0x57

#define LD_B_A 0x47

#define LD_B_B 0x40

#define LD_B_C 0x41

#define LD_B_D 0x42

#define LD_B_E 0x43

#define LD_B_H 0x44

#define LD_B_L 0x45

#define LD_B_aHL 0x46

#define ADD_A_B 0x80

#define ADD_A_d8 0xC6

#define SUB_A_B 0x90

#define ADD_HL_BC 0x09

#define OR_A_B 0xB0

#define OR_A_C 0xB1

#define XOR_A_A 0xAF

#define JR_NZ_s8 0x20

#define JR_Z_s8 0x28

#define JP_NZ_a16 0xC2

#define JP_Z_a16 0xCA

#define JP_NC_a16 0xD2

#define CALL_a16 0xCD

#define CALL_Z_a16 0xCC

#define CALL_NZ_a16 0xC4

#define CALL_C_a16 0xDC

#define RET 0xC9

#define RETI 0xD9

#define RET_Z 0xC8

#define RET_NC 0xD0

#define JR_s8 0x18

#define CCF 0x3F

#define IE 0xFB

#define DI 0xF3

#endif  // GAME_OPCODES_H_
