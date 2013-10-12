#ifndef SYMBOLS_H
#define SYMBOLS_H

#include "tag.h"
#include <string.h>

#define MAX_NAME_LENGTH 20
#define MAX_NUM_SYMBOL 1000

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
};

struct symbols {
	struct symbols* parent;
	struct ident list_ident[MAX_NUM_SYMBOL];
	int index;
	
};

extern void ini_ident(struct ident* my_ident, char* name, enum ident_type type);

extern void ini_ident(struct ident* my_ident, char* name, enum ident_type type) {
	strcpy(my_ident->name, name);
	my_ident->type = type;
}
#endif