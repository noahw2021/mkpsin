//
//  ui_syntax.c
//  mkpsin
//
//  Created by Noah Wooten on 2/11/22.
//

#include <stdio.h>
#include "ui.h"

void ui_syntax(int argc, char** argv) {
	printf("PSIN Instructions in enum follow the below format:\n");
	printf("NAME[tab]= 0xNN, // DESCRIPTION (NAME [(R|I,D):(PSZ,USZ)]):TISZ\n");
	printf("\n");
	printf("Where NAME is the Instruction's name\n");
	printf("Where DESCRIPTION is the Instruction's functional description\n");
	printf("Where (R|I) represents R or I depending on if the value is a register or immediate\n");
	printf("Where D is the Operand's name\n");
	printf("Where PSZ is the allocated size of the operand in bits\n");
	printf("Where USZ is the usable size of the operand in bits\n");
	printf("Where TISZ is the total size of the instruction in bits\n");
	printf("Where NN is the total size of the opcode. See example below.\n");
	printf("\n");
	printf("Differences between PSZ and USZ occur when needed to be used as padding when an instruction's argument size in bits not divisible by 8 (or byte size on architecture).\n");
	printf("\n");
	printf("Example:\n");
	printf("\n");
	printf("MOV[tab]= 0x00, // Moves an operand into a register (MOV [R:(4,8),DEST] [I:(64,64),SRC]):80\n");
	printf("\n");
	printf("Where \"MOV\" is the Instruction's name\n");
	printf("Where \"Moves an operand into a register\" is the Instruction's description\n");
	printf("Where \"[R:(4,8),DEST]\" signifies that the operand \"DEST\" is a register physically stored in 8 bits but only 4 should be used by the instruction.\n");
	printf("Where \"I:(64,64),SRC]\" signifies that the operand \"SRC\" is an immediate value physically stored in 64 bits and that all 64 bits are available to be used by the compiler.\n");
	printf("Where \":80\" signifies that the instruction is in total 80 bits long. This is determined by (8 + 8 + 64), with 8 being the size of the opcode, 8 being the size of the 1st operand and 64 being the size of the 2nd operand.\n");
	printf("Where \"00\" signifies the opcode's value. May be larger or smaller than 8 bits. Zeros should be used to prefix the size if it cannot be represented (Each instruction must have the same opcode length).\n");
	printf("\nFiles must end -a!\n");
}
