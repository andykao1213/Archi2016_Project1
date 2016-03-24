#include "global.h"
#include "decode.h"
#include "doInstruct.h"

#include <stdlib.h>
#include <stdio.h>

void opdecode()
{
    unsigned tmp, i, start, j;

    while(1){

        tmp = 0, start = PC, funct = 0;
        for(i=0; i<4; i++)
            tmp = (tmp << 8) + imemory[start + i];

        opcode = tmp;
        opcode = opcode >> 26;
        if(opcode == 0x00)
            rdecode(tmp);
        else if(opcode == 0x3F)
            return;
        else if (opcode == 0x02 || opcode == 0x03)
            jdecode(tmp);
        else
            idecode(tmp);

    }

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

    doIInstruct();

}

void jdecode(unsigned tmp)
{

    address = tmp;
    address = address << 6 >> 6;

    doJInstruct();

}





