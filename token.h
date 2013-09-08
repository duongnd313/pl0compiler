#ifndef TOKEN_H
#define TOKEN_H

#include "tag.h"
#define MAX_NAME_LENGTH 20
#define MAX_ATTRIBUTE_LENGTH 42
#define MAX_NUM_LENGTH 6
#define MAX_IDENT_LENGTH 10

struct token {
	enum token_tag tag;
	char attribute[MAX_ATTRIBUTE_LENGTH];
};
#endif
