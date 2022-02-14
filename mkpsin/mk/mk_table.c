//
//  mk_table.c
//  mkpsin
//
//  Created by Noah Wooten on 2/14/22.
//

#include "mk.h"
#include <stdlib.h>
#include <string.h>

extern int mki_newelem(mkdoc_t* Document, byte Type, const char* Primary, const char* Secondary);
extern char* mki_getline(void);

int mki_newtablelem(mktable_t* Table, byte Type, const char* Primary, int Row, int Column) {
	if (Table->CurrentRow < Row)
		Table->CurrentRow = Row;
	if (Table->CurrentColumn < Column)
		Table->CurrentColumn = Column;
	if (Type == _MK_HEADER) {
		Table->Headers = realloc(Table->Headers, (sizeof(mkheader_t) * (Table->HeaderCount + 1)));
		Table->Headers[Table->HeaderCount].Reference = (Table->LastReference + 1);
		Table->Headers[Table->HeaderCount].Text = malloc(strlen(Primary) + 1);
		strcpy(Table->Headers[Table->HeaderCount].Text, Primary);
		Table->Headers[Table->HeaderCount].Column = Column;
		Table->HeaderCount++;
	} else if (Type == _MK_TABLEFIELD) {
		Table->Fields = realloc(Table->Fields, (sizeof(mktablefield_t) * (Table->FieldCount + 1)));
		Table->Fields[Table->FieldCount].Reference = (Table->LastReference + 1);
		Table->Fields[Table->FieldCount].Column = Column;
		Table->Fields[Table->FieldCount].Row = Row;
		Table->Fields[Table->FieldCount].Data = malloc(strlen(Primary) + 1);
		strcpy(Table->Fields[Table->FieldCount].Data, Primary);
		Table->FieldCount++;
	}
	Table->LastReference++;
	return Table->LastReference;
}

int mkd_addtable(mkdoc_t* Document, mktable_t* Table) {
	//Document->ElementCount++;
	char* CompiledTable = mki_compiletable(Table);
	int Return = mki_newelem(Document, _MK_TABLE, CompiledTable, NULL);
	free(CompiledTable);
	free(Table);
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
	mktablefield_t* NewFields = malloc(sizeof(mktablefield_t) * (Table->HeaderCount - 1));
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

mkheader_t* mktdi_getheaderbycolumn(mkheader_t* Headers, int Count, int Column) {
	for (int i = 0; i < Count; i++) {
		if (Headers[i].Column == Column)
			return &Headers[i];
	}
	return NULL;
}
mktablefield_t* mktdi_getfieldbycolumn(mktablefield_t* Fields, int Count, int Column) {
	for (int i = 0; i < Count; i++)
		if (Fields[i].Column == Column)
			return &Fields[i];
	return NULL;
}
mktablefield_t* mktdi_getfieldbyrow(mktablefield_t* Fields, int Count, int Row) {
	for (int i = 0; i < Count; i++)
		if (Fields[i].Row == Row)
			return &Fields[i];
	return NULL;
}

char* mki_compiletable(mktable_t* Table) {
	int TableSizeLength = 75 + (Table->HeaderCount * 5) + (Table->FieldCount * 3);
	for (int i = 0; i < Table->HeaderCount; i++)
		TableSizeLength += strlen(Table->Headers[i].Text) + 1;
	for (int i = 0; i < Table->FieldCount; i++)
		TableSizeLength += strlen(Table->Fields[i].Data) + 1;
	TableSizeLength++;
	char* Return = malloc(TableSizeLength);
	
	for (int i = 0; i < (Table->CurrentColumn); i++) {
		mkheader_t* Header = mktdi_getheaderbycolumn(Table->Headers, Table->HeaderCount, i);
		strcat(Return, "**");
		strcat(Return, Header->Text);
		strcat(Return, "**|");
	}
	strcat(Return, mki_getline());
	for (int r = 0; r < (Table->CurrentRow); r++) {
		for (int c = 0; c < (Table->CurrentColumn + 1); c++) {
			strcat(Return, Table->Fields[c].Data);
			strcat(Return, "|");
		}
		strcat(Return, mki_getline());
	}
	
	return Return;
}

mktable_t* mk_newtable(void) {
	mktable_t* Return = malloc(sizeof(mktable_t));
	memset(Return, 0, sizeof(mktable_t));
	return Return;
}
