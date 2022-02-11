//
//  mk_fields.c
//  mkpsin
//
//  Created by Noah Wooten on 2/9/22.
//

#include "mk.h"
#include <stdlib.h>
#include <string.h>

int mki_newelem(mkdoc_t* Document, byte Type, const char* Primary, const char* Secondary) {
	Document->Elements = realloc(Document->Elements, (sizeof(mkfield_t) * (Document->ElementCount + 1)));
	memset(&Document->Elements[Document->ElementCount], 0, sizeof(mkfield_t));
	if (Primary)
		Document->Elements[Document->ElementCount].Primary = malloc(strlen(Primary) + 1);
	if (Secondary)
		Document->Elements[Document->ElementCount].Secondary = malloc(strlen(Secondary) + 1);
	
	Document->Elements[Document->ElementCount].Type = Type;
	if (Primary)
		strcpy(Document->Elements[Document->ElementCount].Primary, Primary);
	if (Secondary)
		strcpy(Document->Elements[Document->ElementCount].Secondary, Secondary);
	Document->ElementCount++;
	return (int)Document->ElementCount - 1;
}

int mkd_addheading1(mkdoc_t* Document, const char* Value) {
	return mki_newelem(Document, _MK_HEADING1, Value, NULL);
}
int mkd_addheading2(mkdoc_t* Document, const char* Value) {
	return mki_newelem(Document, _MK_HEADING2, Value, NULL);
}
int mkd_addheading3(mkdoc_t* Document, const char* Value) {
	return mki_newelem(Document, _MK_HEADING3, Value, NULL);
}
int mkd_addtext(mkdoc_t* Document, const char* Value) {
	return mki_newelem(Document, _MK_TEXT, Value, NULL);
}
int mkd_addlink(mkdoc_t* Document, const char* Address, const char* Title) {
	return mki_newelem(Document, _MK_LINK, Address, Title);
}
int mkd_addimage(mkdoc_t* Document, const char* Address, const char* Alt) {
	return mki_newelem(Document, _MK_IMAGE, Address, Alt);
}
int mkd_addboldtext(mkdoc_t* Document, const char* Text) {
	return mki_newelem(Document, _MK_BOLD, Text, NULL);
}
int mkd_additalicstext(mkdoc_t* Document, const char* Title) {
	return mki_newelem(Document, _MK_ITALICS, Title, NULL);
}
int mkd_addcode(mkdoc_t* Document, const char* Source, const char* LanguageStr) {
	return mki_newelem(Document, _MK_CODE, Source, LanguageStr);
}
int mkd_addline(mkdoc_t* Document) {
	return mki_newelem(Document, _MK_LINE, NULL, NULL);
}
