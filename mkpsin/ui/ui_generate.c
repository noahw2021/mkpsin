//
//  ui_generate.c
//  mkpsin
//
//  Created by Noah Wooten on 2/11/22.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ui.h"
#include "../psin/psin.h"
#include "../mk/mk.h"

void ui_generate(int argc, char** argv) {
	char* Infile = argv[2];
	char* Outfile = argv[3];
	if (!Infile) {
		printf("[ERR]: No Input file!\n");
		return;
	}
	if (!Outfile) {
		printf("[ERR]: No Output file!\n");
		return;
	}
	FILE* Input = fopen(Infile, "r");
	FILE* Output = fopen(Outfile, "w");
	if (!Input) {
		if (Output)
			fclose(Output);
		printf("[ERR]: Cannot open input file!\n");
		return;
	}
	if (!Output) {
		if (Input)
			fclose(Input);
		printf("[ERR]: Cannot open output file!\n");
		return;
	}
	char* Buffer = malloc(2048);
	mkdoc_t* Document = mk_newdoc();
	mkd_addheading1(Document, "Instructions");
	while (1) {
		fgets(Buffer, 2048, Input);
		if (!strcmp(Buffer, "-a"))
			break;
		int Reference = psin_declare(Buffer);
		
		// Get Instruction Names
		char* TotalName = malloc(256);
		sprintf(TotalName, "%s (%s)", psin_getmnemonic(Reference), psin_getdesc(Reference));
		mkd_addheading2(Document, TotalName);
		mkd_addtext(Document, psin_getdesc(Reference));
		
		// Instruction Table
		byte PresentMap = psin_getpresentmap(Reference);
		int InstructionCount = 0;
		switch (PresentMap) {
			case 0b000:
				InstructionCount = 0;
				break;
			case 0b100:
				InstructionCount = 1;
				break;
			case 0b110:
				InstructionCount = 2;
				break;
			case 0b111:
				InstructionCount = 3;
				break;
		}
		byte Regmap = psin_getregmap(Reference);
		char* TempStr = malloc(4096);
		
		if (PresentMap != 0b000) {
			mktable_t* InstructionTable = mk_newtable();
			mkdt_addheader(InstructionTable, "Name", 0);
			mkdt_addheader(InstructionTable, "Type", 1);
			mkdt_addheader(InstructionTable, "Available Size", 2);
			mkdt_addheader(InstructionTable, "Physical Size", 3);
			byte UpCounter = 0;
			if (PresentMap & 0b100) {
				UpCounter++;
				mkdt_addfield(InstructionTable, psin_getoperandadesc(Reference), UpCounter, 0);
				if (Regmap & 0b100)
					mkdt_addfield(InstructionTable, "Register", UpCounter, 1);
				else
					mkdt_addfield(InstructionTable, "Immediate", UpCounter, 1);
			
				sprintf(TempStr, "%i", psin_getoperandasize(Reference));
				mkdt_addfield(InstructionTable, TempStr, UpCounter, 2);
			}
			if (PresentMap & 0b010) {
				UpCounter++;
				mkdt_addfield(InstructionTable, psin_getoperandbdesc(Reference), UpCounter, 0);
				if (Regmap & 0b010)
					mkdt_addfield(InstructionTable, "Register", UpCounter, 1);
				else
					mkdt_addfield(InstructionTable, "Immediate", UpCounter, 1);
				sprintf(TempStr, "%i", psin_getoperandbsize(Reference));
				mkdt_addfield(InstructionTable, TempStr, UpCounter, 2);
			}
			if (PresentMap & 0b001) {
				UpCounter++;
				mkdt_addfield(InstructionTable, psin_getoperandcdesc(Reference), UpCounter, 0);
				if (Regmap & 0b001)
					mkdt_addfield(InstructionTable, "Register", UpCounter, 1);
				else
					mkdt_addfield(InstructionTable, "Immediate", UpCounter, 1);
				sprintf(TempStr, "%i", psin_getoperandcsize(Reference));
				mkdt_addfield(InstructionTable, TempStr, UpCounter, 2);
			}
		} else {
			mkd_addtext(Document, "This instruction takes zero operands.");
			mkd_addline(Document);
		}
		
		// General Information Table
		mktable_t* GeneralInformation = mk_newtable();
		mkdt_addheader(GeneralInformation, "Instruction", 0);
		mkdt_addheader(GeneralInformation, "Opcode", 1);
		mkdt_addheader(GeneralInformation, "Operand Count", 2);
		mkdt_addheader(GeneralInformation, "Total Instruction Size", 3);
		mkdt_addheader(GeneralInformation, "Opcode Size", 4);
		mkdt_addfield(GeneralInformation, psin_getmnemonic(Reference), 1, 0);
		char* StrInt = malloc(12);
		sprintf(StrInt, "%hX", psin_getopcode(Reference));
		mkdt_addfield(GeneralInformation, StrInt, 1, 1);
		sprintf(StrInt, "%i", InstructionCount);
		mkdt_addfield(GeneralInformation, StrInt, 1, 2);
		sprintf(StrInt, "%i", psin_getoperandsize(Reference));
		mkdt_addfield(GeneralInformation, StrInt, 1, 3);
		sprintf(StrInt, "%i", psin_getopcodesize(Reference));
		mkdt_addfield(GeneralInformation, StrInt, 1, 4);
		free(StrInt);
	
		free(TempStr);
	}
	char* Data = mk_compile(Document);
	fwrite(Data, strlen(Data), 1, Output);
	fclose(Output);
	free(Buffer);
	printf("[INFO]: Wrote to file!\n");
	return;
}
