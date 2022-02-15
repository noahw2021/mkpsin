//
//  psin_getdata.c
//  mkpsin
//
//  Created by Noah Wooten on 2/7/22.
//

#include "psin.h"

char* psin_getmnemonic(int Iterator) {
	return InstructionMap[Iterator].Mnemonic;
}

byte psin_getopcode(int Iterator) {
	return InstructionMap[Iterator].Opcode;
}

byte psin_getregmap(int Iterator) {
	return InstructionMap[Iterator].RegMap;
}

byte psin_getpresentmap(int Iterator) {
	return InstructionMap[Iterator].PresentMap;
}

byte psin_getoperandasize(int Iterator) {
	return InstructionMap[Iterator].OperandASize;
}

byte psin_getoperandbsize(int Iterator) {
	return InstructionMap[Iterator].OperandBSize;
}

byte psin_getoperandcsize(int Iterator) {
	return InstructionMap[Iterator].OperandCSize;
}

char* psin_getdesc(int Reference) {
	return InstructionMap[Reference].Description;
}

int psin_getoperandsize(int Reference) {
	return InstructionMap[Reference].TotalInstructionSize;
}

int psin_getopcodesize(int Reference) {
	return InstructionMap[Reference].TotalOpcodeSize;
}

char* psin_getoperandadesc(int Reference) {
	return InstructionMap[Reference].OperandAName;
}

char* psin_getoperandbdesc(int Reference) {
	return InstructionMap[Reference].OperandBName;
}

char* psin_getoperandcdesc(int Reference) {
	return InstructionMap[Reference].OperandCName;
}
