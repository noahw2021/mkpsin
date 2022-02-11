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
	while (1) {
		fgets(Buffer, 2048, Input);
		if (!strcmp(Buffer, "-a"))
			break;
		int Reference = psin_declare(Buffer);
		
	}
	char* Data = mk_compile(Document);
	fwrite(Data, strlen(Data), 1, Output);
	fclose(Output);
	free(Buffer);
	printf("[INFO]: Wrote to file!\n");
	return;
}
