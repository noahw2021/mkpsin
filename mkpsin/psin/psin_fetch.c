//
//  psin_fetch.c
//  mkpsin
//
//  Created by Noah Wooten on 2/7/22.
//

#include "psin.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define rtl_toupr(c)	((c) >= 'a' && (c) <= 'z' ? (c) - 0x20: (c))
char* rtl_strupr(char* Source, char* Destination) {
	u32 Length = strlen(Source);
	strcpy(Destination, Source);
	
	for (int i = 0; i < Length; i++)
		Destination[i] = rtl_toupr(Destination[i]);
	
	return Destination;
}

int psin_getbyopcode(byte Opcode) {
	for (int i = 0; i < InstructionCount; i++) {
		if (InstructionMap[i].Opcode == Opcode)
			return i;
	}
	return 0xFFFFFFFF;
}
int psin_getbymnemonic(char* Mnemonic) {
	char* Uppercased = malloc(strlen(Mnemonic) + 1);
	rtl_strupr(Mnemonic, Uppercased);
	
	for (int i = 0; i < InstructionCount; i++) {
		if (!strcmp(InstructionMap[i].Mnemonic, Uppercased)) {
			free(Uppercased);
			return i;
		}
	}
	
	free(Uppercased);
	return 0xFFFFFFFF;
}
