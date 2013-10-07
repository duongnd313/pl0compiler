#include "tag.h"
#include "token.h"
#include "stdio.h"
#include <ctype.h>
#include <string.h>
#include "lexer.h"
#include "syntaxparser.h"

FILE *f;
int i = 0;
struct token mtoken;
char cb = ' ';
void get_token_wrapper(struct token* next_token);
int main(int argc, char* argv[]) {
	if (argc == 1) {
		printf("Duong dan file bi bo trong\n");
		return 0;
	}
	char* path = argv[1];
	
	if (!(f = fopen(path, "r"))) {
		printf("path:%s khong ton tai.\n",path);
		return 0;
	}
	struct token current_token;
	get_token_wrapper(&current_token);
	parse_program(&current_token, get_token_wrapper);
	return 0;
}

void get_token_wrapper(struct token* next_token) {
	get_token(f, &cb, next_token);
	print_token(*next_token);
}




