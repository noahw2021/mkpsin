//
//  psin_getdata.c
//  plassemble
//
//  Created by Noah Wooten on 2/7/22.
//

#include "psin.h"

char* psin_getmnemonic(u32 Iterator) {
	return InstructionMap[Iterator].Mnemonic;
}

byte psin_getopcode(u32 Iterator) {
	return InstructionMap[Iterator].Opcode;
}

byte psin_getregmap(u32 Iterator) {
	return InstructionMap[Iterator].RegMap;
}

byte psin_getpresentmap(u32 Iterator) {
	return InstructionMap[Iterator].PresentMap;
}

byte psin_getoperandasize(u32 Iterator) {
	return InstructionMap[Iterator].OperandASize;
}

byte psin_getoperandbsize(u32 Iterator) {
	return InstructionMap[Iterator].OperandBSize;
}

byte psin_getoperandcsize(u32 Iterator) {
	return InstructionMap[Iterator].OperandCSize;
}
