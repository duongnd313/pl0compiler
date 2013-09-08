#include "tag.h"
#include "token.h"
#include "stdio.h"
#include <ctype.h>
#include <string.h>
#include "lexer.h"

int main(int argc, char* argv[]) {
	if (argc == 1) {
		printf("Duong dan file bi bo trong\n");
		return 0;
	}
	char* path = argv[1];
	FILE *f;
	if (!(f = fopen(path, "r"))) {
		printf("path:%s khong ton tai.\n",path);
		return 0;
	}
	
	struct token mtoken;
	char cb = ' ';
	do {
		get_token(f, &cb, &mtoken);
		print_token(mtoken);
	} while (mtoken.tag != TERROR && mtoken.tag != TENDT);
	return 0;
}


