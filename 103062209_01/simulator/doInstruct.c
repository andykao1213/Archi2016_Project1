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
            break;
        case addu:
            reg[rd] = reg[rs] + reg[rt];
            PC += 4;
            break;
        case sub:
            reg[rd] = reg[rs] - reg[rt];
            PC += 4;
            break;
        case And:
            reg[rd] = reg[rs] & reg[rt];
            PC += 4;
            break;
        case Or:
            reg[rd] = reg[rs] | reg[rt];
            PC += 4;
            break;
        case Xor:
            reg[rd] = reg[rs] ^ reg[rt];
            PC += 4;
            break;
        case nor:
            reg[rd] = ~(reg[rs] | reg[rt]);
            PC += 4;
            break;
        case nand:
            reg[rd] = ~(reg[rs] & reg[rt]);
            PC += 4;
            break;
        case slt:
            reg[rd] = (int)reg[rs] < (int)reg[rt];
            PC += 4;
            break;
        case sll:
            reg[rd] = reg[rs] << shamt;
            PC += 4;
            break;
        case srl:
            reg[rd] = reg[rs] >> shamt;
            PC += 4;
            break;
        case sra:
            reg[rd] = (int)reg[rs] >> shamt;
            PC += 4;
            break;
        case jr:
            printf("jr");
            PC = reg[rs];
            PC += 4;
            break;
        default:
            break;
    }
    printf("funct: %02x rs: %d rt: %d rd: %d shamt: %d\n", funct, reg[rs], reg[rt], reg[rd], shamt);
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
            else
                PC += 4;
            break;
        case bne:
            if(findSignBit(immediate) == 1) immediate = -immediate;
            if(reg[rs] != reg[rt])
                PC = PC + 4 + 4*immediate;
            else
                PC += 4;
            break;
        case bgtz:
            if(findSignBit(immediate) == 1) immediate = -immediate;
            if(reg[rs] > 0)
                PC = PC + 4 + 4*immediate;
            else
                PC += 4;
            break;
        default:
            break;

    }

    printf("op: %02x rs: %d rt:%d im:%d\n", opcode, reg[rs], reg[rt], immediate);

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

    printf("op: %02x address: %08x\n", opcode, address);
}
