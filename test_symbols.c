#include "tag.h"
#include "token.h"
#include "stdio.h"
#include <ctype.h>
#include <string.h>
#include "lexer.h"
#include "semantic.h"
#include "gencode.h"

int main(int argc, char* argv[]) {
	int p;
	struct symbols main_block_symbols;
	struct symbols* currenttt = &main_block_symbols;
	main_block_symbols.index = -1;
	main_block_symbols.size = 4;
	add_ident(currenttt, "temp\0", ITVARIABLE, 1);
	add_ident(currenttt, "marray", ITARRAY, 10);
	add_var_ident(currenttt, "varident", 1);
	add_ident(currenttt, "temp2", ITVARIABLE, 1);
	
	currenttt = add_ident_procedure(currenttt, "my_func\0", ITPROCEDURE);
	add_ident(currenttt, "temp2\0", ITCONSTANT, 1);
	add_ident(currenttt, "marray", ITARRAY, 5);
	add_ident(currenttt, "chan vai", ITARRAY, 1);
	printf("index main %d\n", main_block_symbols.index);
	printf("index cur %d\n", currenttt->index);

	if (is_exist_name(currenttt, "temp", ITVARIABLE)) {
		printf("Ton tai\n");
	} else {
		printf("Khong ton tai\n");
	}
	struct ident* m_ident = NULL;
	printf("Find declare %d\n", find_declared(currenttt, "temp2", ITCONSTANT, &p, &m_ident));
	printf("L=%d Offset=%d\n", p, m_ident->offset);
	print_symbols(*find_parent(currenttt));
	printf("00000011\n");
	print_symbols(*(main_block_symbols.list_ident[main_block_symbols.index].next_list));
	return 1;
}


