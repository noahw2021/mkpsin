//
//  mk_engine.c
//  mkpsin
//
//  Created by Noah Wooten on 2/9/22.
//

#include <stdlib.h>
#include <string.h>
#include "mk.h"
mkctx_t* mkctx;

void mk_init(u16 LineEnding) {
	mkctx = malloc(sizeof(mkctx_t));
	memset(mkctx, 0, sizeof(mkctx_t));
	mkctx->LineEnding = LineEnding;
}
void mk_shutdown(void) {
	free(mkctx);
}
