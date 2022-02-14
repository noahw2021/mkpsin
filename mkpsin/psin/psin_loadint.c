//
//  psin_loadint.c
//  plassemble
//
//  Created by Noah Wooten on 2/7/22.
//

#include "psin.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void psini_createinst(byte Opcode, byte OperandA, byte OperandB, byte OperandC, byte Regmap, byte PresentMap, char* Name, char* Desc, char* OpADesc, char* OpBDesc, char* OpCDesc) {
	if (InstructionCount == 0)
		InstructionMap = malloc((InstructionCount + 1) * sizeof(psinentry_t));
	else
		InstructionMap = realloc(InstructionMap, (InstructionCount + 1) * sizeof(psinentry_t));
	
	memset(&InstructionMap[InstructionCount], 0, sizeof(psinentry_t));
	InstructionMap[InstructionCount].PresentMap = PresentMap;
	InstructionMap[InstructionCount].RegMap = Regmap;
	InstructionMap[InstructionCount].Opcode = Opcode;
	strncpy(InstructionMap[InstructionCount].Mnemonic, Name, 16);
	InstructionMap[InstructionCount].OperandASize = OperandA;
	InstructionMap[InstructionCount].OperandBSize = OperandB;
	InstructionMap[InstructionCount].OperandCSize = OperandC;
	strncpy(InstructionMap[InstructionCount].OperandAName, OpADesc, 32);
	strncpy(InstructionMap[InstructionCount].OperandBName, OpBDesc, 32);
	strncpy(InstructionMap[InstructionCount].OperandCName, OpCDesc, 32);
	strncpy(InstructionMap[InstructionCount].Description, Desc, 240);
	
	InstructionCount++;
	return;
}

u32 psin_declare(const char* Instruction) {
	// SET = 0x00, // Set Register (SET [R:(4,4),DEST] [R:(4,4),SRC]):16s
 	char* LocalData = malloc(strlen(Instruction) + 1);
	int StrIterator = 0;
	strcpy(LocalData, Instruction);
	
	// Declarations
	char* InstructionName = malloc(16);
	u32 OperandA = 0, OperandB = 0, OperandC = 0;
	byte PresentMap = 0;
	byte RegMap = 0;
	byte Opcode = 0;
	u32 Return;
	char* Description = malloc(240);
	char* OperandADesc = malloc(240);
	char* OperandBDesc = malloc(240);
	char* OperandCDesc = malloc(240);
	int LocalIterator = 0;
	
	// Get Instruction Name
	while (LocalData[StrIterator] != ' ') {
		InstructionName[StrIterator] = LocalData[LocalIterator];
		StrIterator++;
		LocalIterator++;
	}
	
	// Get Opcode
	StrIterator = 0;
	while (LocalData[StrIterator] != 'x') {
		StrIterator++;
	}
	StrIterator++;
	char* TemporaryData = malloc(4);
	strncpy(TemporaryData, LocalData + StrIterator, 2);
	Opcode = strtoul(TemporaryData, NULL, 16);
	free(TemporaryData);
	
	// Get Description
	StrIterator = 0;
	while (LocalData[StrIterator] != '/') {
		StrIterator++;
	}
	StrIterator += 3;
	LocalIterator = 0;
	while (LocalData[StrIterator] != '(') {
		Description[LocalIterator] = LocalData[StrIterator];
		StrIterator++;
		LocalIterator++;
	}
	
	// Get Operand A
	StrIterator = 0;
	while (LocalData[StrIterator] != '[') {
		if (LocalData[StrIterator] == ')') {
			goto Create;
		}
		StrIterator++;
	}
	PresentMap |= 0b100;
	StrIterator++;
	switch (LocalData[StrIterator]) {
		case 'I':
			RegMap |= 0b000;
			break;
		case 'R':
			RegMap |= 0b100;
			break;
		default:
			printf("[ERR]: Invalid syntax in %s.\n", Instruction);
	}
	StrIterator += 2;
	TemporaryData = malloc(5);
	if (LocalData[StrIterator + 1] != ')') {
		StrIterator += 3;
	} else {
		StrIterator += 2;
	}
	if (LocalData[StrIterator + 1] != ')') {
		strncpy(TemporaryData, LocalData + StrIterator + 1, 2);
	} else {
		strncpy(TemporaryData, LocalData + StrIterator, 1);
	}
	
	OperandA = atoi(TemporaryData);
	free(TemporaryData);
	LocalIterator = 0;
	while (LocalData[StrIterator] != ',')
		StrIterator++;
	StrIterator++;
	while (LocalData[StrIterator] != ']') {
		OperandADesc[LocalIterator] = LocalData[StrIterator];
		LocalIterator++;
		StrIterator++;
	}
	
	// Get Operand B
	while (LocalData[StrIterator] != '[') {
		if (LocalData[StrIterator] == ')') {
			goto Create;
		}
		StrIterator++;
	}
	PresentMap |= 0b010;
	StrIterator++;
	switch (LocalData[StrIterator]) {
		case 'I':
			RegMap |= 0b000;
			break;
		case 'R':
			RegMap |= 0b010;
			break;
		default:
			printf("[ERR]: Invalid syntax in %s.\n", Instruction);
	}
 	StrIterator += 2;
	TemporaryData = malloc(5);
	if (LocalData[StrIterator + 1] != ',') {
		StrIterator += 3;
	} else {
		StrIterator += 2;
	}
	if (LocalData[StrIterator + 1] != ',') {
		strncpy(TemporaryData, LocalData + StrIterator + 1, 2);
	} else {
		strncpy(TemporaryData, LocalData + StrIterator, 1);
	}
	OperandB = atoi(TemporaryData);
	while (LocalData[StrIterator] != ']') {
		StrIterator++;
	}
	free(TemporaryData);
	while (LocalData[StrIterator] != ',')
		StrIterator++;
	StrIterator++;
	while (LocalData[StrIterator] != ']') {
		OperandBDesc[LocalIterator] = LocalData[StrIterator];
		LocalIterator++;
		StrIterator++;
	}
	
	// Get Operand C
	while (LocalData[StrIterator] != '[') {
		if (LocalData[StrIterator] == ')') {
			goto Create;
		}
		StrIterator++;
	}
	PresentMap |= 0b001;
	StrIterator++;
	switch (LocalData[StrIterator]) {
		case 'I':
			RegMap |= 0b000;
			break;
		case 'R':
			RegMap |= 0b001;
			break;
		default:
			printf("[ERR]: Invalid syntax in %s.\n", Instruction);
	}
	StrIterator += 2;
	TemporaryData = malloc(5);
	if (LocalData[StrIterator + 1] != ',') {
		StrIterator += 3;
	} else {
		StrIterator += 2;
	}
	if (LocalData[StrIterator + 1] != ',') {
		strncpy(TemporaryData, LocalData + StrIterator + 1, 2);
	} else {
		strncpy(TemporaryData, LocalData + StrIterator, 1);
	}
	OperandC = atoi(TemporaryData);
	while (LocalData[StrIterator] != ']') {
		StrIterator++;
	}
	free(TemporaryData);
	while (LocalData[StrIterator] != ',')
		StrIterator++;
	StrIterator++;
	while (LocalData[StrIterator] != ']') {
		OperandCDesc[LocalIterator] = LocalData[StrIterator];
		LocalIterator++;
		StrIterator++;
	}
	
	goto Create;
	
	// Create
Create:
	Return = 0;
	psini_createinst(Opcode, OperandA, OperandB, OperandC, RegMap, PresentMap, InstructionName, Description, OperandADesc, OperandBDesc, OperandCDesc);
	Return = InstructionCount - 1;
	
	// Return
	free(LocalData);
	free(InstructionName);
	free(Description);
	free(OperandADesc);
	free(OperandBDesc);
	free(OperandCDesc);
	return Return;
}
