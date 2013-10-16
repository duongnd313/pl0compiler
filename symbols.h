#ifndef SYMBOLS_H
#define SYMBOLS_H

#include "tag.h"
#include <string.h>

#define MAX_NAME_LENGTH 20
#define MAX_NUM_SYMBOL 1000
#define MAX_NUM_PARAM 50

enum ident_type {
	ITVARIABLE = 10,
	ITCONSTANT,
	ITARRAY,
	ITPROCEDURE
};

struct ident {
	char name[MAX_NAME_LENGTH];
	int ptr;
	enum ident_type type;
	struct symbols* next_list;
	char is_var;
	int offset;
	int size;
};

struct symbols {
	struct symbols* parent;
	struct ident list_ident[MAX_NUM_SYMBOL];
	int index;
	int size;
	// 0: tham tri
	// 1: tham bien
	char param_code[MAX_NUM_PARAM];
	
};

extern void ini_ident(struct ident* my_ident, char* name, enum ident_type type, int size, int offset);

extern void ini_ident(struct ident* my_ident, char* name, enum ident_type type, int size, int offset) {
	strcpy(my_ident->name, name);
	my_ident->type = type;
	my_ident->size = size;
	my_ident->offset = offset;
}
#endif
