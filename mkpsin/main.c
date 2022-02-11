//
//  main.c
//  mkpsin
//
//  Created by Noah Wooten on 2/2/22.
//

#include <stdio.h>
#include "mk/mk.h"

int main(int argc, const char * argv[]) {
	mk_init(MKI_LINE_LF);
	mkdoc_t* Document = mk_newdoc();
	
	printf("%s", mk_compile(Document));
	return 0;
}
