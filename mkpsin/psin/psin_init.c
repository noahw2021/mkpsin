//
//  psin_init.c
//  mkpsin
//
//  Created by Noah Wooten on 2/7/22.
//

#include "psin.h"
#include <stdlib.h>

psinentry_t* InstructionMap;
int InstructionCount;

void psin_init(void) {
	InstructionCount = 0;
	InstructionMap = NULL;
	return;
}
void psin_shutdown(void) {
	if (InstructionMap)
		free(InstructionMap);
	return;
}
