#include <stdio.h>
#include <stdlib.h>

#include "global.h"
#include "doInstruct.h"



int findSignBit(unsigned a)
{
    a = a >> 15;
    return a;
}

void doRInstruct()
{

    switch(funct){
        case add:
            reg[rd] = reg[rs] + reg[rt];
            PC += 4;
            //printf("add %d, %d = %d\n", reg[rs], reg[rt], reg[rd]);
            break;
        case addu:
            reg[rd] = reg[rs] + reg[rt];
            PC += 4;
            //printf("addu %d, %d = %d\n", reg[rs], reg[rt], reg[rd]);
            break;
        case sub:
            reg[rd] = reg[rs] - reg[rt];
            //printf("sub %d, %d = %d\n", reg[rs], reg[rt], reg[rd]);
            PC += 4;
            break;
        case And:
            reg[rd] = reg[rs] & reg[rt];
            //printf("and %d, %d = %d\n", reg[rs], reg[rt], reg[rd]);
            PC += 4;
            break;
        case Or:
            reg[rd] = reg[rs] | reg[rt];
            //printf("or %d, %d = %d\n", reg[rs], reg[rt], reg[rd]);
            PC += 4;
            break;
        case Xor:
            reg[rd] = reg[rs] ^ reg[rt];
            //printf("xor %d, %d = %d\n", reg[rs], reg[rt], reg[rd]);
            PC += 4;
            break;
        case nor:
            reg[rd] = ~(reg[rs] | reg[rt]);
            //printf("nor %d, %d = %d\n", reg[rs], reg[rt], reg[rd]);
            PC += 4;
            break;
        case nand:
            reg[rd] = ~(reg[rs] & reg[rt]);
            //printf("nand %d, %d = %d\n", reg[rs], reg[rt], reg[rd]);
            PC += 4;
            break;
        case slt:
            reg[rd] = (int)reg[rs] < (int)reg[rt];
            //printf("slt %d, %d = %d\n", reg[rs], reg[rt], reg[rd]);
            PC += 4;
            break;
        case sll:
            reg[rd] = reg[rs] << shamt;
            //printf("sll %d = %d\n", reg[rs], reg[rd]);
            PC += 4;
            break;
        case srl:
            reg[rd] = reg[rs] >> shamt;
            //printf("srl %d = %d\n", reg[rs], reg[rd]);
            PC += 4;
            break;
        case sra:
            reg[rd] = (int)reg[rs] >> shamt;
            //printf("sra %d = %d\n", reg[rs], reg[rd]);
            PC += 4;
            break;
        case jr:
            PC = reg[rs];
            //printf("jr %d\n", reg[rs]);
            PC += 4;
            break;
    }

}

void doIInstruct()
{
    int i = 0;

    switch(opcode){
        case addi:
            if(findSignBit(immediate) == 1) immediate = immediate;
            reg[rt] = reg[rs] + immediate;
            PC += 4;
            break;
        case addiu:
            reg[rt] = reg[rs] + (unsigned)immediate;
            PC += 4;
            break;
        case lw:
            if(findSignBit(immediate) == 1) immediate = -immediate;
            for(i=0; i<4; i++)
                reg[rt] = (reg[rt] << 8) + dmemory[reg[rs] + immediate +i];
            PC += 4;
            break;
        case lhu:
            if(findSignBit(immediate) == 1) immediate = -immediate;
            for(i=0; i<2; i++)
                reg[rt] =(reg[rt] << 8) + dmemory[reg[rs] + immediate +i];
            PC += 4;
            break;
        case lh:
            for(i=0; i<2; i++)
                reg[rt] = (reg[rt] << 8) + dmemory[reg[rs] + (int)immediate +i];
            PC += 4;
            break;
        case lb:
            if(findSignBit(immediate) == 1) immediate = -immediate;
            reg[rt] = (reg[rt] << 8) + dmemory[reg[rs] + immediate +i];
            PC += 4;
            break;
        case lbu:
            if(findSignBit(immediate) == 1) immediate = -immediate;
            reg[rt] =(reg[rt] << 8) + dmemory[reg[rs] + immediate +i];
            PC += 4;
            break;
        case sw:
            tmp[0] = reg[rt];
            tmp[0] = tmp[0] >> 24 << 24;
            tmp[1] = reg[rt];
            tmp[1] = tmp[1] >> 16 << 24 >> 8;
            tmp[2] = reg[rt];
            tmp[2] = tmp[2] >> 8 << 24 >> 16;
            tmp[3] = reg[rt];
            tmp[3] = tmp[3] << 24 >> 24;
            if(findSignBit(immediate) == 1) immediate = -immediate;
            for(i=0; i<4; i++)
                dmemory[reg[rs] + immediate + i] = tmp[i];
            PC += 4;
            break;
        case sh:
            tmp[0] = reg[rt];
            tmp[0] = tmp[0] << 16 >> 24;
            tmp[1] = reg[rt];
            tmp[1] = tmp[1] << 24 >> 24;
            if(findSignBit(immediate) == 1) immediate = -immediate;
            for(i=0; i<2; i++)
                dmemory[reg[rs] + immediate + i] = tmp[i];
            PC += 4;
            break;
        case sb:
            if(findSignBit(immediate) == 1) immediate = -immediate;
            tmp[0] = reg[rt];
            dmemory[reg[rs] + immediate] = tmp[0];
            PC += 4;
            break;
        case lui:
            reg[rt] = immediate << 16;
            PC += 4;
            break;
        case andi:
            reg[rt] = rs & (unsigned)immediate;
            PC += 4;
            break;
        case ori:
            reg[rt] = rs | (unsigned)immediate;
            PC += 4;
            break;
        case nori:
            reg[rt] = ~(rs | (unsigned)immediate);
            PC += 4;
            break;
        case slti:
            if(findSignBit(immediate) == 1) immediate = -immediate;
            reg[rt] = reg[rs] < immediate;
            PC += 4;
            break;
        case beq:
            if(findSignBit(immediate) == 1) immediate = -immediate;
            if(reg[rs] == reg[rt])
                PC = PC + 4 + 4*immediate;
            break;
        case bne:
            if(findSignBit(immediate) == 1) immediate = -immediate;
            if(reg[rs] != reg[rt])
                PC = PC + 4 + 4*immediate;
            break;
        case bgtz:
            if(findSignBit(immediate) == 1) immediate = -immediate;
            if(reg[rs] > 0)
                PC = PC + 4 + 4*immediate;
            break;

    }
}

void doJInstruct()
{
    if(opcode == jump){
        PC = PC + 4;
        PC = PC >> 28;
        PC = PC << 28;
        PC = PC | 4*address;
    }
    else if(opcode == jal){
        reg[31] = PC + 4;
        PC = PC + 4;
        PC = PC >> 28;
        PC = PC << 28;
        PC = PC | 4*address;
    }
}
