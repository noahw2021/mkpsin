//
//  psin.h
//  mkpsin
//
//  Created by Noah Wooten on 2/7/22.
//

#ifndef psin_h
#define psin_h
#include "../root.h"
// "parsepsin" Library v1.1 - 02/14/2022.
/*
 Changelog:
 -v1.1: Adds descriptions and operand names
 -v1.0: Base implementation
 */

void psin_init(void);
void psin_shutdown(void);

int psin_declare(const char* Instruction);
char* psin_getsyntax(void);

char* psin_parseline(byte Opcode, u64 OperandA, u64 OperandB, u64 OperandC, byte Regmap);
int psin_getbyopcode(byte Opcode);
int psin_getbymnemonic(char* Mnemonic);

char* psin_getmnemonic(int Iterator);
byte psin_getopcode(int Iterator);
byte psin_getregmap(int Iterator);
byte psin_getpresentmap(int Iterator);
byte psin_getoperandasize(int Iterator);
byte psin_getoperandbsize(int Iterator);
byte psin_getoperandcsize(int Iterator);
char* psin_getdesc(int Reference);

typedef struct psinentry {
	str Mnemonic[16];
	str Description[240];
	byte Opcode;
	byte RegMap;
	byte PresentMap;
	byte OperandASize;
	byte OperandBSize;
	byte OperandCSize;
	str OperandAName[32];
	str OperandBName[32];
	str OperandCName[32];
}psinentry_t;
extern psinentry_t* InstructionMap;
extern int InstructionCount;

#endif /* psin_h */
