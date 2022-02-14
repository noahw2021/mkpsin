//
//  mk_table.c
//  mkpsin
//
//  Created by Noah Wooten on 2/14/22.
//

#include "mk.h"
#include <stdlib.h>
#include <string.h>

int mki_newelem(mkdoc_t* Document, byte Type, const char* Primary, const char* Secondary);

int mki_newtablelem(mktable_t* Table, byte Type, const char* Primary, int Row, int Column) {
	if (Type == _MK_HEADER) {
		Table->Headers = realloc(Table->Headers, (sizeof(mkheader_t) * (Table->HeaderCount + 1)));
		Table->Headers[Table->HeaderCount].Reference = (Table->LastReference + 1);
		Table->Headers[Table->HeaderCount].Text = malloc(strlen(Primary) + 1);
		strcpy(Table->Headers[Table->HeaderCount].Text, Primary);
		Table->Headers[Table->HeaderCount].Column = Column;
	} else if (Type == _MK_TABLEFIELD) {
		Table->Fields[Table->FieldCount].Reference = (Table->LastReference + 1);
		Table->Fields[Table->FieldCount].Column = Column;
		Table->Fields[Table->FieldCount].Row = Row;
		Table->Fields[Table->FieldCount].Data = malloc(strlen(Primary) + 1);
		strcpy(Table->Fields[Table->FieldCount].Data, Primary);
	}
	Table->LastReference++;
	return Table->LastReference;
}

int mkd_addtable(mkdoc_t* Document, mktable_t* Table) {
	Document->ElementCount++;
	char* CompiledTable = mki_compiletable(Table);
	int Return = mki_newelem(Document, _MK_TABLE, CompiledTable, NULL);
	free(CompiledTable);
	return Return;
}

int mkdt_addheader(mktable_t* Table, const char* Source, int Column) {
	return mki_newtablelem(Table, _MK_HEADER, Source, Column, Column);
}

int mkdt_addfield(mktable_t* Table, const char* Field, int Row, int Column) {
	return mki_newtablelem(Table, _MK_TABLEFIELD, Field, Row, Column);
}

void mkdt_deleteelem(mktable_t* Table, int Reference) {
	mkheader_t* NewHeaders = malloc(sizeof(mkheader_t) * (Table->HeaderCount - 1));
	mkfield_t* NewFields = malloc(sizeof(mkheader_t) * (Table->HeaderCount - 1));
	int RefCount = 0;
	
	for (int i = 0; i < Table->HeaderCount; i++) {
		if (Table->Headers[i].Reference == Reference) {
			if (Table->Headers[i].Text)
				free(Table->Headers[i].Text);
			continue;
		} else {
			memcpy(&NewHeaders[++RefCount], &Table[i], sizeof(mkheader_t));
		}
	}
	
	RefCount = 0;
	for (int i = 0; i < Table->FieldCount; i++) {
		if (Table->Fields[i].Reference == Reference) {
			if (Table->Fields[i].Data)
				free(Table->Fields[i].Data);
			continue;
		} else {
			memcpy(&NewFields[++RefCount], &Table[i], sizeof(mkheader_t));
		}
	}
	
	free(Table->Headers);
	free(Table->Fields);
	Table->Headers = NewHeaders;
	Table->Fields = NewFields;
}


char* mki_compiletable(mktable_t* Table) {
	
}
