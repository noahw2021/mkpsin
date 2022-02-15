//
//  psin.h
//  mkpsin
//
//  Created by Noah Wooten on 2/7/22.
//

#ifndef psin_h
#define psin_h
#include "../root.h"
// "parsepsin" Library v2.0 - 02/15/2022.
/*
 Changelog:
 -v1.3: Revamps parsing library
 -v1.2.1: Adds instruction physical size support
 -v1.2: Adds instruction & opcode sizes for more complex encoding schemes
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
int psin_getoperandsize(int Reference);
int psin_getopcodesize(int Reference);
char* psin_getoperandadesc(int Reference);
char* psin_getoperandbdesc(int Reference);
char* psin_getoperandcdesc(int Reference);
int psin_getoperandaphyssize(int Reference);
int psin_getoperandbphyssize(int Reference);
int psin_getoperandcphyssize(int Reference);

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
	int TotalInstructionSize;
	int TotalOpcodeSize;
	byte OperandAPhysSize;
	byte OperandBPhysSize;
	byte OperandCPhysSize;
}psinentry_t;
extern psinentry_t* InstructionMap;
extern int InstructionCount;

#endif /* psin_h */
