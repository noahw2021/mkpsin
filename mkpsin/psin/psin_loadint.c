//
//  psin_loadint.c
//  mkpsin
//
//  Created by Noah Wooten on 2/7/22.
//

#include "psin.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void psini_createinst(byte Opcode, byte OperandA, byte OperandB, byte OperandC, byte Regmap, byte PresentMap, char* Name, char* Desc, char* OpADesc, char* OpBDesc, char* OpCDesc, int TotalSize, int OpAPhys, int OpBPhys, int OpCPhys) {
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
	InstructionMap[InstructionCount].TotalInstructionSize = TotalSize;
	InstructionMap[InstructionCount].TotalOpcodeSize = TotalSize;
	InstructionMap[InstructionCount].TotalOpcodeSize -= OperandA;
	InstructionMap[InstructionCount].TotalOpcodeSize -= OperandB;
	InstructionMap[InstructionCount].TotalOpcodeSize -= OperandC;
	InstructionMap[InstructionCount].OperandAPhysSize = OpAPhys;
	InstructionMap[InstructionCount].OperandBPhysSize = OpBPhys;
	InstructionMap[InstructionCount].OperandCPhysSize = OpCPhys;
	
	InstructionCount++;
	return;
}

#define _ISFLAG_READY 		0x01
#define _ISFLAG_FOUNDALL 	0x02
#define _ISFLAG_SEEKINGDESC 0x04

int psin_declare(const char* Instruction) {
	char* Mnemonic = malloc(32);
	char* Description = malloc(240);
	char* OperandADesc = malloc(64);
	char* OperandBDesc = malloc(64);
	char* OperandCDesc = malloc(64);
	u32 TotalInstructionSize = 0;
	int OperandASize = 0, OperandAPhys = 0;
	int OperandBSize = 0, OperandBPhys = 0;
	int OperandCSize = 0, OperandCPhys = 0;
	byte PresentMap = '\0', RegisterMap = '\0';
	byte Opcode = '\0';
	int DescriptionLength = 0;
	int LocalIterator = 0, StrIterator = 0;
	int CurrentStage = 0;
	char* TempStr = malloc(256);
	int InterStage = 0;
	char* DescriptionBasePtr = NULL;
	byte Flags = 0;
	int BackupIterator = 0;
	int LocalDescriptionCounter = 0;
	char* LocalDescriptionBasePtr = NULL;
	
	char* ParseString = malloc(strlen(Instruction) + 1);
	strcpy(ParseString, Instruction);
	
	// SET = 0x00, // Set Register (SET [R:(4,4),DEST] [R:(4,4),SRC]):16
	
	while (ParseString[StrIterator]) {
		if (CurrentStage == 0) { // Get Mnemonic
			switch (ParseString[StrIterator]) {
				case ' ':
					CurrentStage++;
					break;
				default:
					Mnemonic[LocalIterator] = ParseString[StrIterator];
					LocalIterator++;
					break;
			}
		}
		if (CurrentStage == 1) { // Get Opcode
			switch (ParseString[StrIterator]) {
				case 'x':
					Opcode = strtol(ParseString + StrIterator + 1, NULL, 16);
					CurrentStage++;
					break;
				default:
					break;
			}
		}
		if (CurrentStage == 2) { // Get Description
			switch (ParseString[StrIterator]) {
				case '/':
					InterStage++;
					break;
				case ' ':
					if (InterStage == 0)
						break;
					if (!(Flags & _ISFLAG_READY)) {
						InterStage++;
						Flags |= _ISFLAG_READY;
						if (InterStage == 3) {
							DescriptionBasePtr = ParseString + StrIterator + 1;
						}
					}
					break;
				case '(':
					if (Flags & _ISFLAG_READY) {
						DescriptionLength = (int)((ParseString + StrIterator) - (DescriptionBasePtr));
						InterStage++;
					}
					break;
				default:
					break;
			}
			if (InterStage == 4) {
				if (DescriptionLength == 0)
					DescriptionLength++;
				strncpy(Description, DescriptionBasePtr, DescriptionLength - 1);
				DescriptionLength = 0;
				InterStage = 0;
				CurrentStage++;
				BackupIterator = StrIterator;
			}
		}
		if (CurrentStage == 3) { // Get Operand Count
			switch (ParseString[StrIterator]) {
				case '[':
					InterStage++;
					break;
				case ':':
					if (ParseString[StrIterator + 1] != '(') {
						Flags |= _ISFLAG_FOUNDALL;
						StrIterator = BackupIterator;
					}
					break;
			}
			if (Flags & _ISFLAG_FOUNDALL) {
				switch (InterStage) {
					case 0:
						PresentMap = 0b000;
						break;
					case 1:
						PresentMap = 0b100;
						break;
					case 2:
						PresentMap = 0b110;
						break;
					case 3:
						PresentMap = 0b111;
						break;
					default:
						printf("[ERR]: Parse error, %d is too many operands!\n", InterStage);
						break;
				}
				InterStage = 0;
				CurrentStage++;
			}
		}
		if (CurrentStage == 4) { // Get Operand A
			if (!(PresentMap & 0b100)) {
				CurrentStage++;
			} else {
				switch (ParseString[StrIterator]) {
					case '[': // Stage 0
						if (InterStage == 0)
							InterStage++;
						break;
					case 'I': // Stage 1
					case 'R':
						if (InterStage == 1) {
							if (ParseString[StrIterator] == 'R')
								RegisterMap |= 0b100;
							InterStage++;
							break;
						} else {
							break;
						}
					case '(': // Stage 2: Get Virtual Size
						if (InterStage != 2)
							break;
						if (ParseString[StrIterator + 2] == ',')
							strncpy(TempStr, ParseString + StrIterator + 1, 1);
						else
							strncpy(TempStr, ParseString + StrIterator + 1, 2);
						OperandASize = atoi(TempStr);
						InterStage++;
						break;
					case ',': // Stage 3: Get Physical Size
						if (InterStage == 4) { // Stage 4: Get Description
							Flags |= _ISFLAG_SEEKINGDESC;
							if (LocalDescriptionCounter == 0)
								LocalDescriptionBasePtr = ParseString + StrIterator;
						} else {
							if (InterStage != 3)
								break;
							if (ParseString[StrIterator + 2] == ')')
								strncpy(TempStr, ParseString + StrIterator + 1, 1);
							else
								strncpy(TempStr, ParseString + StrIterator + 1, 2);
							OperandAPhys = atoi(TempStr);
							InterStage++;
						}
						break;
					case ']':
						if (InterStage == 4) {
							if (Flags & _ISFLAG_SEEKINGDESC) {
								strncpy(OperandADesc, LocalDescriptionBasePtr + 1, LocalDescriptionCounter);
								InterStage = 0;
								Flags = 0;
								LocalDescriptionCounter = 0;
								CurrentStage++;
							}
						}
						break;
					default:
						if (Flags & _ISFLAG_SEEKINGDESC)
							LocalDescriptionCounter++;
				}
			}
		}
		if (CurrentStage == 5) { // Get Operand B
			if (!(PresentMap & 0b010)) {
				CurrentStage++;
			} else {
				switch (ParseString[StrIterator]) {
					case '[': // Stage 0
						if (InterStage == 0)
							InterStage++;
						break;
					case 'I': // Stage 1
					case 'R':
						if (InterStage == 1) {
							if (ParseString[StrIterator] == 'R')
								RegisterMap |= 0b010;
							InterStage++;
							break;
						} else {
							break;
						}
					case '(': // Stage 2: Get Virtual Size
						if (InterStage != 2)
							break;
						if (ParseString[StrIterator + 2] == ',')
							strncpy(TempStr, ParseString + StrIterator + 1, 1);
						else
							strncpy(TempStr, ParseString + StrIterator + 1, 2);
						OperandBSize = atoi(TempStr);
						InterStage++;
						break;
					case ',': // Stage 3: Get Physical Size
						if (InterStage == 4) { // Stage 4: Get Description
							Flags |= _ISFLAG_SEEKINGDESC;
							if (LocalDescriptionCounter == 0)
								LocalDescriptionBasePtr = ParseString + StrIterator;
						} else {
							if (InterStage != 3)
								break;
							if (ParseString[StrIterator + 2] == ')')
								strncpy(TempStr, ParseString + StrIterator + 1, 1);
							else
								strncpy(TempStr, ParseString + StrIterator + 1, 2);
							OperandBPhys = atoi(TempStr);
							InterStage++;
						}
						break;
					case ']':
						if (InterStage == 4) {
							if (Flags & _ISFLAG_SEEKINGDESC) {
								strncpy(OperandBDesc, LocalDescriptionBasePtr + 1, LocalDescriptionCounter + 1);
								InterStage = 0;
								LocalDescriptionCounter = 0;
								Flags = 0;
								CurrentStage++;
							}
						}
						break;
					default:
						if (Flags & _ISFLAG_SEEKINGDESC)
							LocalDescriptionCounter++;
				}
			}
		}
		if (CurrentStage == 6) { // Get Operand C
			if (!(PresentMap & 0b001)) {
				CurrentStage++;
			} else {
				switch (ParseString[StrIterator]) {
					case '[': // Stage 0
						if (InterStage == 0)
							InterStage++;
						break;
					case 'I': // Stage 1
					case 'R':
						if (InterStage == 1) {
							if (ParseString[StrIterator] == 'R')
								RegisterMap |= 0b001;
							InterStage++;
							break;
						} else {
							break;
						}
					case '(': // Stage 2: Get Virtual Size
						if (InterStage != 2)
							break;
						if (ParseString[StrIterator + 2] == ',')
							strncpy(TempStr, ParseString + StrIterator + 1, 1);
						else
							strncpy(TempStr, ParseString + StrIterator + 1, 2);
						OperandCSize = atoi(TempStr);
						InterStage++;
						break;
					case ',': // Stage 3: Get Physical Size
						if (InterStage == 4) { // Stage 4: Get Description
							Flags |= _ISFLAG_SEEKINGDESC;
							if (LocalDescriptionCounter == 0)
								LocalDescriptionBasePtr = ParseString + StrIterator;
						} else {
							if (InterStage != 3)
								break;
							if (ParseString[StrIterator + 2] == ')')
								strncpy(TempStr, ParseString + StrIterator + 1, 1);
							else
								strncpy(TempStr, ParseString + StrIterator + 1, 2);
							OperandCPhys = atoi(TempStr);
							InterStage++;
						}
						break;
					case ']':
						if (InterStage == 4) {
							if (Flags & _ISFLAG_SEEKINGDESC) {
								strncpy(OperandCDesc, LocalDescriptionBasePtr + 1, LocalDescriptionCounter + 1);
								InterStage = 0;
								Flags = 0;
								LocalDescriptionCounter = 0;
								CurrentStage++;
							}
						}
						break;
					default:
						if (Flags & _ISFLAG_SEEKINGDESC)
							LocalDescriptionCounter++;
				}
			}
		}
		if (CurrentStage == 7) { // Get Instruction Size
			switch (ParseString[StrIterator]) {
				case ':':
					if (ParseString[StrIterator + 1] != '(') {
						TotalInstructionSize = atoi(ParseString + StrIterator + 1);
						CurrentStage++;
					} else {
						StrIterator++;
						break;
					}
					break;
				default:
					StrIterator++;
			}
		}
		if (CurrentStage == 8) { // End of Sequence
			break;
		}
		
		StrIterator++;
	}
	psini_createinst(Opcode, OperandASize, OperandBSize, OperandCSize, RegisterMap, PresentMap, Mnemonic, Description, OperandADesc, OperandBDesc, OperandCDesc, (int)TotalInstructionSize, OperandAPhys, OperandBPhys, OperandCPhys);
	
	free(ParseString);
	free(Mnemonic);
	free(Description);
	free(OperandADesc);
	free(OperandBDesc);
	free(OperandCDesc);
	free(TempStr);
	return InstructionCount - 1;
}
