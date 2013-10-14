#ifndef SEMANTIC_H
#define SEMANTIC_H

#include "symbols.h"
#include "token.h"
#include "lexer.h"
#include "tag.h"
#include "malloc.h"
#include <stdlib.h>


// Kiem tra xem bien su dung da duoc khai bao hay chua.
// Neu da khai bao tra ve 0
// Neu khai bao nhung khac kieu, tra ve enum ident_type la type kieu (>=10)
// Neu chua khai bao tra ve 1.
// KHONG DUNG TYPE = ITPROCEDURE
extern int find_declared(struct symbols* current_symbols, char* name, enum ident_type type);

// Dung de kiem tra khi khai bao bien. Kiem tra trung ten khai bao.
extern int is_exist_name(struct symbols* current_symbols, char* name, enum ident_type type);

// Them ident
extern int add_ident(struct symbols* current_symbols, char* name, enum ident_type type);

// Tao bang moi cho thu tuc
extern struct symbols* add_ident_procedure(struct symbols* current_symbols, char* name, enum ident_type type);

// Tim bang cha
extern struct symbols* find_parent(struct symbols* current_symbols);

// Tim procedure
// = 1 Neu khong tim thay thu tuc,
// = 0 neu tim thay thu tuc.
extern int find_procedure(struct symbols* current_symbols, char* name, char* param_code);

extern int add_ident(struct symbols* current_symbols, char* name, enum ident_type type) {
	if (current_symbols->index >= MAX_NUM_SYMBOL) {
		printf("Khai bao so bien qua gioi han %d bien\n", MAX_NUM_SYMBOL);
		exit(-1);
		return 0;
	}
	printf("add\n");
	current_symbols->index = current_symbols->index + 1;
	ini_ident(&(current_symbols->list_ident[current_symbols->index]),
		name, type);
	return 1;
}

extern int add_var_ident(struct symbols* current_symbols, char* name) {
	if (current_symbols->index >= MAX_NUM_SYMBOL) {
		printf("Khai bao so bien qua gioi han %d bien\n", MAX_NUM_SYMBOL);
		exit(-1);
		return 0;
	}
	current_symbols->index = current_symbols->index + 1;
	ini_ident(&(current_symbols->list_ident[current_symbols->index]),
		name, ITVARIABLE);
	current_symbols->list_ident[current_symbols->index].is_var = 1;
	return 1;
}

extern int is_exist_name(struct symbols* current_symbols, char* name, enum ident_type type) {
	int i = 0;
	for (i=0; i < current_symbols->index + 1; i++) {
		if (strcmp(name, current_symbols->list_ident[i].name) == 0) {
			if (type == ITPROCEDURE) { // Procedure co the trung ten bien/ hang
				if (current_symbols->list_ident[i].type == ITPROCEDURE) {
					return 1;
				}
			} else { // Khong phai procedure => Bao trung ten luon
				return 1;
			}
		}
	}
	return 0;
}

extern int find_declared(struct symbols* current_symbols, char* name, enum ident_type type) {
	int i = 0;
	int tmp_type = -1;
	for (i=0; i < current_symbols->index + 1; i++) {
		if (strcmp(name, current_symbols->list_ident[i].name) == 0) {
			if (current_symbols->list_ident[i].type == type) {
				return 0;
			} else {
				if (type == ITPROCEDURE) {
					tmp_type = current_symbols->list_ident[i].type;
				} else {
					return current_symbols->list_ident[i].type;
				}
			}
		}
	}
	// Khong tim thay. Tim bang cha.
	if (current_symbols->parent == NULL) {
		printf("---- No parent----");
		if (tmp_type == -1) { // Chua duoc khai bao
			return 1;
		} else {
			return tmp_type; // Khai bao khac kieu
		}
	} else {
		printf("---- Find parent----");
		int tmp2 = find_declared(current_symbols->parent, name, type);
		if (tmp2 == 0) { // Tim thay
			return 0;
		} else {	// Khong tim thay hoac khac kieu
			// Return kieu sai gan nhat
			if (tmp_type != -1) {
				return tmp_type;
			} else {
				return tmp2;
			}
		}
	}
}

extern void print_symbols(struct symbols table) {
	int i = 0;
	for (i=0; i < table.index + 1; i++) {
		char str_type[50];
		switch (table.list_ident[i].type) {
			case ITARRAY:
				strcpy(str_type, "ITARRAY");
			break;
			case ITCONSTANT:
				strcpy(str_type, "ITCONSTANT");
			break;
			case ITPROCEDURE:
				strcpy(str_type, "ITPROCEDURE");
			break;
			case ITVARIABLE:
				strcpy(str_type, "ITVARIABLE");
			break;
		}
		printf("%s %s\n", table.list_ident[i].name, str_type);
	}
}

extern struct symbols* add_ident_procedure(struct symbols* current_symbols, char* name, enum ident_type type) {
	add_ident(current_symbols, name, type);
	int index = current_symbols->index;
	struct symbols * new_list = malloc(sizeof(struct symbols));
	current_symbols->list_ident[index].next_list = new_list;
	new_list->parent = current_symbols;
	new_list->index = -1;
	return new_list;
}

extern struct symbols* find_parent(struct symbols* current_symbols) {
	return current_symbols->parent;
}

extern int find_procedure(struct symbols* current_symbols, char* name, char* param_code) {
	printf("Find proc %d\n", 10);
	int i = 0;
	int tmp_type = -1;
	for (i=0; i < current_symbols->index + 1; i++) {
		printf("cai gi the %s\n", current_symbols->list_ident[i].name);
		if (strcmp(name, current_symbols->list_ident[i].name) == 0) {
			printf("found name\n");
			if (current_symbols->list_ident[i].type == ITPROCEDURE) {
				//(*num_param) = current_symbols->list_ident[i].next_list->n_param;
				strcpy(param_code, current_symbols->list_ident[i].next_list->param_code);
				return 0;
			} else {
				tmp_type = current_symbols->list_ident[i].type;
			}
		}
	}
	printf("1\n");
	// Khong tim thay. Tim bang cha.
	if (current_symbols->parent == NULL) {
		printf("---- No parent----");
		if (tmp_type == -1) { // Chua duoc khai bao
			return 1;
		} else {
			return tmp_type; // Khai bao khac kieu
		}
	} else {
		printf("---- Find parent----");
		int tmp2 = find_procedure(current_symbols->parent, name, param_code);
		if (tmp2 == 0) { // Tim thay
			return 0;
		} else {	// Khong tim thay hoac khac kieu
			// Return kieu sai gan nhat
			if (tmp_type != -1) {
				return tmp_type;
			} else {
				return tmp2;
			}
		}
	}
	printf("Det\n");
}

extern void set_param_code(struct symbols* current_symbols, char* param_code) {
	strcpy(current_symbols->param_code, param_code);
}
#endif
