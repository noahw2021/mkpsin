//
//  ui_help.c
//  mkpsin
//
//  Created by Noah Wooten on 2/11/22.
//

#include <stdio.h>
#include "ui.h"

void ui_help(int argc, char** argv) {
	printf("'mkpsin' Tool Help\n");
	printf("%s -h: Shows this menu.\n", argv[0]);
	printf("%s -g (infile) (outfile): Generates a documentation for a PSIN database.\n", argv[0]);
	printf("%s -s: Displays syntax.\n", argv[0]);
	printf("%s -p (outfile): Generates a documentation using the internal PLASM PSIN database.\n", argv[0]);
	return;
}
