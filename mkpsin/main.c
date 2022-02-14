//
//  main.c
//  mkpsin
//
//  Created by Noah Wooten on 2/2/22.
//

#include <stdio.h>
#include <string.h>
#include "mk/mk.h"
#include "ui/ui.h"
#include "psin/psin.h"

#define ArgumentBody(Source, Name) if (!strcmp(Source, Name))

int main(int argc, char** argv) {
	psin_init();
	main_loadinst();
	
	char* SourceArgument = argv[1];
	if (argc < 2){
		ui_help(argc, argv);
	}
	ArgumentBody(SourceArgument, "-g") {
		ui_generate(argc, argv);
	}
	ArgumentBody(SourceArgument, "-s") {
		ui_syntax(argc, argv);
	}
	ArgumentBody(SourceArgument, "-h") {
		ui_help(argc, argv);
	}
	psin_shutdown();
	return 0;
}
