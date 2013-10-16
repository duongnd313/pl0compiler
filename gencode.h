#ifndef GENCODE_H
#define GENCODE_H
#include "symbols.h"
#include "token.h"
#include "lexer.h"
#include "tag.h"
#include "malloc.h"
#include <stdlib.h>

enum OP_CODE {
  OP_LA,   // Load Address:
  OP_LV,   // Load Value:
  OP_LC,   // load Constant 
  OP_LI,   // Load Indirect 
  OP_INT,  // Increment t 
  OP_DCT,  // Decrement t
  OP_J,    // Jump 
  OP_FJ,   // False Jump 
  OP_HL,   // Halt 
  OP_ST,   // Store 
  OP_CALL, // Call
  OP_EP,   // Exit Procedure 
  OP_EF,   // Exit Function
  OP_RC,   // Read Char 
  OP_RI,   // Read Integer
  OP_WRC,  // Write Char    
  OP_WRI,  // Write Int
  OP_WLN,  // WriteLN 
  OP_ADD,  // Add 
  OP_SUB,  // Substract
  OP_MUL,  // Multiple
  OP_DIV,  // Divide
  OP_NEG,  // Negative
  OP_CV,   // Copy Top
  OP_EQ,   // Equal
  OP_NE,   // Not Equal
  OP_GT,   // Greater
  OP_LT,   // Less
  OP_GE,   // Greater or Equal
  OP_LE,   // Less or Equal
  OP_BP    // Break point.
};

struct e_code {
	enum OP_CODE op;
	int p;
	int q;
	struct e_code* next_code;
	char str_code[10];
};

struct list_code {
	struct e_code* first_code;
	struct e_code* last_code;
	int n_code;
};

extern void gen_code(struct list_code* codes, enum OP_CODE op, int p, int q, struct e_code* holder);

////LA Id.Addr; LC Id.width; genE();MUL;  ADD; LI;
extern void gen_code(struct list_code* codes, enum OP_CODE op, int p, int q, struct e_code* holder) {
	switch (op) {
		case OP_LA:   // Load Address:
			holder->op = OP_LA;
			holder->p = p;
			holder->q = q;
			sprintf(holder->str_code, "LA %d %d", p, q);
			codes->last_code->next_code = holder;
			codes->last_code = holder;
		break;
  		case OP_LV:   // Load Value:
			holder->op = OP_LV;
			holder->p = p;
			holder->q = q;
			sprintf(holder->str_code, "LV %d %d", p, q);
			codes->last_code->next_code = holder;
			codes->last_code = holder;
		break;
  		case OP_LC:   // load Constant
			holder->op = OP_LC;
			holder->p = p;
			holder->q = q;
			sprintf(holder->str_code, "LC %d", q);
			codes->last_code->next_code = holder;
			codes->last_code = holder;
		break;
  		case OP_LI:   // Load Indirect 
			holder->op = OP_LI;
			holder->p = p;
			holder->q = q;
			strcpy(holder->str_code, "LI");
			codes->last_code->next_code = holder;
			codes->last_code = holder;
		break;
  		case OP_INT:  // Increment t 
		break;
  		case OP_DCT:  // Decrement t
		break;
  		case OP_J:    // Jump
			holder->op = OP_J;
			holder->p = p;
			holder->q = q;
			sprintf(holder->str_code, "J %d", q);
			codes->last_code->next_code = holder;
			codes->last_code = holder;
		break;
  		case OP_FJ:   // False Jump 
		break;
  		case OP_HL:   // Halt 
		break;
  		case OP_ST:   // Store 
  			holder->op = OP_ST;
			holder->p = p;
			holder->q = q;
			strcpy(holder->str_code, "ST");
			codes->last_code->next_code = holder;
			codes->last_code = holder;
		break;
  		case OP_CALL: // Call
		break;
  		case OP_EP:   // Exit Procedure 
		break;
  		case OP_EF:   // Exit Function
		break;
  		case OP_RC:   // Read Char 
		break;
  		case OP_RI:   // Read Integer
		break;
  		case OP_WRC:  // Write Char 
		break;   
  		case OP_WRI:  // Write Int
		break;
  		case OP_WLN:  // WriteLN 
		break;
  		case OP_ADD:  // Add 
			holder->op = OP_ADD;
			holder->p = -1;
			holder->q = -1;
			strcpy(holder->str_code, "ADD");
			codes->last_code->next_code = holder;
			codes->last_code = holder;
		break;
  		case OP_SUB:  // Substract
			holder->op = OP_SUB;
			holder->p = -1;
			holder->q = -1;
			strcpy(holder->str_code, "SUB");
			codes->last_code->next_code = holder;
			codes->last_code = holder;
		break;
  		case OP_MUL:  // Multiple
			holder->op = OP_MUL;
			holder->p = -1;
			holder->q = -1;
			strcpy(holder->str_code, "MUL");
			codes->last_code->next_code = holder;
			codes->last_code = holder;
		break;
  		case OP_DIV:  // Divide
			printf("1\n");
			holder->op = OP_DIV;
			holder->p = -1;
			holder->q = -1;
			strcpy(holder->str_code, "DIV");
			printf("2\n");
			codes->last_code->next_code = holder;
			printf("3\n");
			codes->last_code = holder;
			printf("4\n");
		break;
  		case OP_NEG:  // Negative
			holder->op = OP_NEG;
			holder->p = -1;
			holder->q = -1;
			strcpy(holder->str_code, "NEG");
			codes->last_code->next_code = holder;
			codes->last_code = holder;
		break;
  		case OP_CV:   // Copy Top
		break;
  		case OP_EQ:   // Equal
			holder->op = OP_EQ;
			holder->p = -1;
			holder->q = -1;
			strcpy(holder->str_code, "EQ");
			codes->last_code->next_code = holder;
			codes->last_code = holder;
		break;
  		case OP_NE:   // Not Equal
			holder->op = OP_NE;
			holder->p = -1;
			holder->q = -1;
			strcpy(holder->str_code, "NEG");
			codes->last_code->next_code = holder;
			codes->last_code = holder;
		break;
  		case OP_GT:   // Greater
  			holder->op = OP_GT;
			holder->p = -1;
			holder->q = -1;
			strcpy(holder->str_code, "GT");
			codes->last_code->next_code = holder;
			codes->last_code = holder;
		break;
  		case OP_LT:   // Less
  			holder->op = OP_LT;
			holder->p = -1;
			holder->q = -1;
			strcpy(holder->str_code, "LT");
			codes->last_code->next_code = holder;
			codes->last_code = holder;
		break;
  		case OP_GE:   // Greater or Equal
  			holder->op = OP_GE;
			holder->p = -1;
			holder->q = -1;
			strcpy(holder->str_code, "GE");
			codes->last_code->next_code = holder;
			codes->last_code = holder;
		break;
  		case OP_LE:   // Less or Equal
  			holder->op = OP_LE;
			holder->p = -1;
			holder->q = -1;
			strcpy(holder->str_code, "LE");
			codes->last_code->next_code = holder;
			codes->last_code = holder;
		break;
  		case OP_BP:    // Break point.
		break;
	}
	codes->n_code = codes->n_code + 1;
}

extern void print_codes(struct list_code codes) {
	struct e_code* tmp_code;
	tmp_code = codes.first_code;
	if (tmp_code == NULL) {
		printf("Code rong\n");
		return;
	}
	printf(" n code = %d\n", codes.n_code);
	while (tmp_code != NULL) {
		printf("%s\n", tmp_code->str_code);
		tmp_code = tmp_code->next_code;
	}
}
#endif
