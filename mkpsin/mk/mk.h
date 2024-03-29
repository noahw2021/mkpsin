//
//  mk.h
//  mkpsin
//
//  Created by Noah Wooten on 2/8/22.
//

#ifndef md_h
#define md_h
#include "../root.h"

#define _MK_HEADING1	0x00
#define _MK_HEADING2	0x01
#define _MK_HEADING3	0x02
#define _MK_TEXT		0x03
#define _MK_LINK		0x04
#define _MK_IMAGE		0x05
#define _MK_BOLD		0x06
#define _MK_ITALICS		0x07
#define _MK_BLOCKQUOTE	0x08
#define _MK_CODE		0x09
#define _MK_LINE		0x0A
#define _MK_TABLE		0x0B
#define _MK_HEADER		0x0C
#define _MK_TABLEFIELD	0x0D

#define MKI_LINE_CR		0x1000
#define MKI_LINE_LF		0x0100
#define MKI_LINE_CRLF   0x1100
#define MKI_LINE_LFCR   0x110F

typedef struct _mkctx {
	u16 LineEnding;
}mkctx_t;

typedef struct _mkfield {
	byte Type;
	str* Primary;
	str* Secondary;
}mkfield_t;

typedef struct _mkdoc {
	int ElementCount;
	mkfield_t* Elements;
}mkdoc_t;

typedef struct _mkheader {
	int Reference;
	int Column;
	str* Text;
}mkheader_t;

typedef struct _mktablefield {
	int Reference;
	int Row;
	int Column;
	str* Data;
}mktablefield_t;

typedef struct _mktable {
	mkheader_t* Headers;
	int HeaderCount;
	mktablefield_t* Fields;
	int FieldCount;
	int CurrentRow;
	int CurrentColumn;
	int LastReference;
}mktable_t;

void mk_init(u16 LineEnding);
void mk_shutdown(void);

mkdoc_t* mk_newdoc(void);
mktable_t* mk_newtable(void);
char* mk_compile(mkdoc_t* Document);
char* mki_compiletable(mktable_t* Table);

int mkd_addheading1(mkdoc_t* Document, const char* Value);
int mkd_addheading2(mkdoc_t* Document, const char* Value);
int mkd_addheading3(mkdoc_t* Document, const char* Value);
int mkd_addtext(mkdoc_t* Document, const char* Value);
int mkd_addlink(mkdoc_t* Document, const char* Address, const char* Title);
int mkd_addimage(mkdoc_t* Document, const char* Address, const char* Alt);
int mkd_addboldtext(mkdoc_t* Document, const char* Text);
int mkd_additalicstext(mkdoc_t* Document, const char* Title);
int mkd_addcode(mkdoc_t* Document, const char* Source, const char* LanguageStr);
int mkd_addline(mkdoc_t* Document);
int mkd_addtable(mkdoc_t* Document, mktable_t* Table);

int mkdt_addheader(mktable_t* Table, const char* Source, int Column);
int mkdt_addfield(mktable_t* Table, const char* Field, int Row, int Column);
void mkdt_deleteelem(mktable_t* Table, int Reference);

void mkd_deleteelem(mkdoc_t* Document, int Reference);

extern mkctx_t* mkctx;

#endif /* md_h */
