#include <stdio.h>
#include "semantic.h"
#include "symbols.h"

int test_proc() {
	printf("hahaha\n");
	return 0;
}

int main(int argc, char* argv[]) {
	struct symbols main_block_symbols;
	struct symbols* currenttt = &main_block_symbols;
	main_block_symbols.index = -1;
	add_ident(currenttt, "temp\0", ITVARIABLE);
	add_ident(currenttt, "temp2", ITVARIABLE);
	add_ident(currenttt, "temp3\0", ITCONSTANT);
	currenttt = add_ident_procedure(currenttt, "my_func\0", ITPROCEDURE);
	add_ident(currenttt, "temp2\0", ITCONSTANT);
	printf("index main %d\n", main_block_symbols.index);
	printf("index cur %d\n", currenttt->index);
	if (is_exist_name(currenttt, "temp", ITVARIABLE)) {
		printf("Ton tai\n");
	} else {
		printf("Khong ton tai\n");
	}
	printf("Find declare %d\n", find_declared(currenttt, "temp", ITVARIABLE));
	print_symbols(*find_parent(currenttt));
	printf("00000011\n");
	print_symbols(*(main_block_symbols.list_ident[main_block_symbols.index].next_list));
	return 1;
}


