#include "global.h"
#include "decode.h"
#include "doInstruct.h"

#include <stdlib.h>
#include <stdio.h>

void opdecode(/*int j*/)
{

    unsigned tmp = 0, i, start = PC/*+j*4*/;
    for(i=0; i<4; i++, start++)
        tmp = (tmp << 8) + imemory[start];

    opcode = tmp;
    opcode = opcode >> 26;
    if(opcode == 0x00)
        rdecode(tmp);
    else if(opcode == 0xFFF)
        halt();
    else if (opcode == 0x02 || opcode == 0x03)
        jdecode(tmp);
    else
        idecode(tmp);

}

void rdecode(unsigned tmp)
{

    funct = tmp;
    funct = funct << 26 >> 26;

    shamt =tmp;
    shamt = shamt << 21 >> 27;

    rs = tmp;
    rs = rs << 6 >> 27;

    rt = tmp;
    rt = rt << 11 >> 27;

    rd = tmp;
    rd = rd << 16 >> 27;

    printf("%5x, %5x, %5x, %5x, %6x\n", rs, rt, rd, shamt, funct);

    doRInstruct();

}

void idecode(unsigned tmp)
{

    rs = tmp;
    rs = rs << 6 >> 27;

    rt = tmp;
    rt = rt << 11 >> 27;

    immediate = tmp;
    immediate = immediate << 16 >> 16;

     printf("%5x, %5x, %16x\n", rs, rt, immediate);


     doIInstruct();

}

void jdecode(unsigned tmp)
{

    address = tmp;
    address = address << 6 >> 6;

    printf("%26x", address);

    doJInstruct();

}

void halt()
{
    hal = 0;
}




