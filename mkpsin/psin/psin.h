//
//  psin.h
//  plassemble
//
//  Created by Noah Wooten on 2/7/22.
//

#ifndef psin_h
#define psin_h
#include "../root.h"

void psin_init(void);
void psin_shutdown(void);

u32 psin_declare(const char* Instruction);
char* psin_getsyntax(void);

char* psin_parseline(byte Opcode, u64 OperandA, u64 OperandB, u64 OperandC, byte Regmap);
u32 psin_getbyopcode(byte Opcode);
u32 psin_getbymnemonic(char* Mnemonic);

char* psin_getmnemonic(u32 Iterator);
byte psin_getopcode(u32 Iterator);
byte psin_getregmap(u32 Iterator);
byte psin_getpresentmap(u32 Iterator);
byte psin_getoperandasize(u32 Iterator);
byte psin_getoperandbsize(u32 Iterator);
byte psin_getoperandcsize(u32 Iterator);

typedef struct psinentry {
	str Mnemonic[16];
	byte Opcode;
	byte RegMap;
	byte PresentMap;
	byte OperandASize;
	byte OperandBSize;
	byte OperandCSize;
}psinentry_t;
extern psinentry_t* InstructionMap;
extern u32 InstructionCount;

#endif /* psin_h */
