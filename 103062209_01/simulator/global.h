
unsigned char * ibuffer;

unsigned char * dbuffer;

unsigned char imemory[1024];

unsigned char dmemory[1024];

unsigned PC;

unsigned reg[32];

long iSize, dSize;

unsigned opcode, funct, shamt;

unsigned rs, rt, rd;

unsigned address;

int immediate;

unsigned numOfInstr;

int hal;

#define add  0x20
#define addu 0x21
#define sub  0x22
#define And  0x24
#define Or   0x25
#define Xor  0x26
#define nor  0x27
#define nand 0x28
#define slt  0x2A
#define sll  0x00
#define srl  0x02
#define sra  0x03
#define jr   0x08

#define addi  0x08
#define addiu 0x09
#define lw    0x23
#define lh    0x21
#define lhu   0x25
#define lb    0x20
#define lbu   0x24
#define sw    0x2B
#define sh    0x29
#define sb    0x28
#define lui   0x0F
#define andi  0x0C
#define ori   0x0D
#define nori  0x0E
#define slti  0x0A
#define beq   0x04
#define bne   0x05
#define bgtz  0x07

#define jump  0x02
#define jal   0x03

#define Halt  0x3F
