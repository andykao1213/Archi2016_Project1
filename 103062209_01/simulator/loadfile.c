#include "loadfile.h"
#include "global.h"
#include <stdlib.h>
#include <stdio.h>

void read()
{

	FILE * iImage;
	FILE * dImage;
	FILE * err;
	size_t iresult, dresult;

	//load the file
	iImage = fopen("iimage.bin", "rb");
	dImage = fopen("dimage.bin", "rb");
	err = fopen("error_dump.rpt", "wb");
	if (iImage == NULL || dImage == NULL) {
		fputs ("File error",stderr);
		exit (1);
	}

	//seek the length of the file
  	fseek (iImage, 0, SEEK_END);
	fseek (dImage, 0, SEEK_END);
  	iSize = ftell (iImage);
	dSize = ftell (dImage);
  	rewind (iImage);
	rewind (dImage);

  	// allocate memory to contain the whole file:
  	ibuffer = (unsigned char*) malloc (sizeof(unsigned char)*iSize);
	dbuffer = (unsigned char*) malloc (sizeof(unsigned char)*dSize);
	if (ibuffer == NULL || dbuffer == NULL) {
		fputs ("Memory error",stderr);
		exit (2);
	}


  	// copy the file into the buffer:
  	iresult = fread (ibuffer,1,iSize,iImage);
	dresult = fread (dbuffer,1,dSize,dImage);
  	if (iresult != iSize || dresult != dSize) {
		fputs ("Reading error",stderr);
		exit (3);
	}

  	iprocess();
	dprocess();

  	// terminate
  	fclose (iImage);
	fclose (dImage);
  	free (ibuffer);
	free (dbuffer);

}

void iprocess()
{
	unsigned i, tmp = 0, start;

	//store PC
	for(i=0; i<4; i++){
		tmp = (tmp << 8) + ibuffer[i];
	}
	PC = tmp;

	//store the number of instructor
	tmp = 0;
	for(i=4; i<8; i++)
		tmp = (tmp << 8) + ibuffer[i];
	numOfInstr = tmp;

	//push buffer into imemory
	start = PC;	//the instruction start from PC
	for(i=8; i<8+numOfInstr*4; i++, start++){
        	imemory[start] = ibuffer[i];
	}

}

void dprocess()
{

	unsigned i, tmp = 0, numOfWord, start;

	//store $sp
	for(i=0; i<4; i++){
		tmp = (tmp << 8) + dbuffer[i];
	}
	reg[29] = tmp;

	//store the number of word
	tmp = 0;
	for(i=4; i<8; i++)
		tmp = (tmp << 8) + dbuffer[i];
	numOfWord = tmp;

	//push buffer into dmemory
	start = 0;
	for(i=8; i<8+numOfWord*4; i++, start++)
		dmemory[start] = dbuffer[i];

}


