//
//  main.c
//  mkpsin
//
//  Created by Noah Wooten on 2/2/22.
//

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "mk/mk.h"
#include "ui/ui.h"
#include "psin/psin.h"

#define ArgumentBody(Source, Name) if (!strcmp(Source, Name))

int main(int argc, char** argv) {
	mk_init(MKI_LINE_LF);
	mkdoc_t* Document = mk_newdoc();
	mktable_t* Table = mk_newtable();
	
	mkdt_addheader(Table, "Header A", 0);
	mkdt_addheader(Table, "Header B", 1);
	mkdt_addheader(Table, "Header C", 2);
	mkdt_addfield(Table, "Test #00", 0, 0);
	mkdt_addfield(Table, "Test #01", 0, 1);
	mkdt_addfield(Table, "Test #02", 0, 2);
	mkdt_addfield(Table, "Test #03", 0, 3);
	mkdt_addfield(Table, "Test #10", 1, 0);
	mkdt_addfield(Table, "Test #11", 1, 1);
	mkdt_addfield(Table, "Test #12", 1, 2);
	mkdt_addfield(Table, "Test #13", 1, 3);
	mkd_addtable(Document, Table);
	
	char* CompiledDocument = mk_compile(Document);
	printf("%s", CompiledDocument);
	free(CompiledDocument);
	mk_shutdown();
	
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
