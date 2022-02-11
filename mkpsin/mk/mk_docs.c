//
//  mk_docs.c
//  mkpsin
//
//  Created by Noah Wooten on 2/9/22.
//

#include "mk.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

mkdoc_t* mk_newdoc(void) {
	mkdoc_t* Return = malloc(sizeof(mkdoc_t));
	memset(Return, 0, sizeof(mkdoc_t));
	return Return;
}

char* LastPointer = NULL;
char* mki_getline(void) {
	if (LastPointer) {
		free(LastPointer);
		LastPointer = NULL;
	}
	LastPointer	= malloc(4);
	switch (mkctx->LineEnding) {
		case MKI_LINE_CR:
			strcpy(LastPointer, "\r");
			break;
		case MKI_LINE_LF:
			strcpy(LastPointer, "\n");
			break;
		case MKI_LINE_CRLF:
			strcpy(LastPointer, "\r\n");
			break;
		case MKI_LINE_LFCR:
			strcpy(LastPointer, "\n\r");
			break;
		default:
			strcpy(LastPointer, "???");
			break;
	}
	return LastPointer;
}
void mki_writestream(char* Writing, u32* Size, u32* Used, char* Stream) {
	u32 Length = strlen(Writing);
	if ((Length + *Used) > *Size) {
		Stream = realloc(Stream, *Used + Length);
		*Size = (*Used + Length);
	}
	*Used += Length;
	strcat(Stream, Writing);
}

char* mk_compile(mkdoc_t* Document) {
	u32 CurrentSize = 512;
	u32 Used = 0;
	char* Outstream = malloc(512);
	memset(Outstream, 0, 512);
	
	for (int i = 0; i < Document->ElementCount; i++) {
		mkfield_t* CurField = &Document->Elements[i];
		char* TotalOutBuf = malloc(25 + (CurField->Primary == NULL) ? 0 : strlen(CurField->Primary) + (CurField->Secondary == NULL) ? 0 : strlen(CurField->Secondary));
		switch (CurField->Type) {
			case _MK_HEADING1:
				sprintf(TotalOutBuf, "# %s%s", CurField->Primary, mki_getline());
				mki_writestream(TotalOutBuf, &CurrentSize, &Used, Outstream);
				break;
			case _MK_HEADING2:
				sprintf(TotalOutBuf, "## %s%s", CurField->Primary, mki_getline());
				mki_writestream(TotalOutBuf, &CurrentSize, &Used, Outstream);
				break;
			case _MK_HEADING3:
				sprintf(TotalOutBuf, "### %s%s", CurField->Primary, mki_getline());
				mki_writestream(TotalOutBuf, &CurrentSize, &Used, Outstream);
				break;
			case _MK_TEXT:
				sprintf(TotalOutBuf, "%s%s", CurField->Primary, mki_getline());
				mki_writestream(TotalOutBuf, &CurrentSize, &Used, Outstream);
				break;
			case _MK_LINK:
				sprintf(TotalOutBuf, "[%s](%s)%s", CurField->Secondary, CurField->Primary, mki_getline());
				mki_writestream(TotalOutBuf, &CurrentSize, &Used, Outstream);
				break;
			case _MK_IMAGE:
				sprintf(TotalOutBuf, "![%s](%s)%s", CurField->Secondary, CurField->Primary, mki_getline());
				mki_writestream(TotalOutBuf, &CurrentSize, &Used, Outstream);
				break;
			case _MK_BOLD:
				sprintf(TotalOutBuf, "**%s**%s", CurField->Primary, mki_getline());
				mki_writestream(TotalOutBuf, &CurrentSize, &Used, Outstream);
				break;
			case _MK_ITALICS:
				sprintf(TotalOutBuf, "*%s*%s", CurField->Primary, mki_getline());
				mki_writestream(TotalOutBuf, &CurrentSize, &Used, Outstream);
				break;
			case _MK_BLOCKQUOTE:
				sprintf(TotalOutBuf, "> %s%s", CurField->Primary, mki_getline());
				mki_writestream(TotalOutBuf, &CurrentSize, &Used, Outstream);
				break;
			case _MK_CODE:
				sprintf(TotalOutBuf, "```%s%s%s```%s", CurField->Secondary, mki_getline(), CurField->Primary, mki_getline());
				mki_writestream(TotalOutBuf, &CurrentSize, &Used, Outstream);
				break;
			case _MK_LINE:
				sprintf(TotalOutBuf, "%s", mki_getline());	
				mki_writestream(TotalOutBuf, &CurrentSize, &Used, Outstream);
				break;
			default:
				sprintf(TotalOutBuf, "! INVALID ELEMENT TYPE !%s", mki_getline());
				mki_writestream(TotalOutBuf, &CurrentSize, &Used, Outstream);
				break;
			}
		free(TotalOutBuf);
		if (CurField->Primary)
			free(CurField->Primary);
		if (CurField->Secondary)
			free(CurField->Secondary);
	}
	free(Document->Elements);
	free(Document);
	return Outstream;
}

void mkd_deleteelem(mkdoc_t* Document, int Reference) {
	mkfield_t* NewFields = malloc(sizeof(mkfield_t) * (Document->ElementCount - 1));
	memset(NewFields, 0, sizeof(mkfield_t));
	for (int i = 0; i < Document->ElementCount; i++) {
		if (i == Reference) {
			if (Document->Elements[i].Primary)
				free(Document->Elements[i].Primary);
			if (Document->Elements[i].Secondary)
				free(Document->Elements[i].Secondary); // We don't need to also free the pointers, just this structure if the structure isn't being deleted.
			continue;
		}
		memcpy(&NewFields[i], &Document->Elements[i], sizeof(mkfield_t));
	}
	free(Document->Elements);
	Document->Elements = NewFields;
	return;
}
