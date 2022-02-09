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

typedef struct _mkfield {
	byte Type;
	str* Primary;
	str* Secondary;
}mkfield_t;

typedef struct _mkdoc {
	u32 ElementCount;
	mkfield_t* Elements;
}mkdoc_t;

void mk_init(u16 LineEnding);
void mk_shutdown(void);

mkdoc_t* mk_newdoc(void);
char* mk_compile(mkdoc_t* Document);

int mkd_addheading1(mkdoc_t* Document, const char* Value);
int mkd_addheading3(mkdoc_t* Document, const char* Value);
int mkd_addheading3(mkdoc_t* Document, const char* Value);
int mkd_addtext(mkdoc_t* Document, const char* Value);
int mkd_addlink(mkdoc_t* Document, const char* Address, const char* Title);
int mkd_addimage(mkdoc_t* Document, const char* Address, const char* Alt);
int mkd_addboldtext(mkdoc_t* Document, const char* Text);
int mkd_additalicstext(mkdoc_t* Document, const char* Title);
int mkd_addcode(mkdoc_t* Document, const char* Source, const char* LanguageStr);
int mkd_addline(mkdoc_t* Document);

void mkd_deleteelem(mkdoc_t* Document, int Reference);

#endif /* md_h */
