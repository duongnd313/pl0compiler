#ifndef PARSER_H
#define PARSER_H

#include "token.h"
#include "lexer.h"
#include "tag.h"
#include "semantic.h"
#include <stdlib.h>
extern int parse_program(struct token* current_token, void (*get_token)(struct token* next_token));
extern int parse_factor(struct token* current_token, void (*get_token)(struct token* next_token));
extern int parse_expression(struct token* current_token, void (*get_token)(struct token* next_token));
extern int parse_block(struct token* current_token, void (*get_token)(struct token* next_token));
extern int parse_statement(struct token* current_token, void (*get_token)(struct token* next_token));
extern int parse_condition(struct token* current_token, void (*get_token)(struct token* next_token));
extern int parse_term(struct token* current_token, void (*get_token)(struct token* next_token));
extern void error(int error_code, struct token mtoken);
extern void printferror(struct token mtoken, char* msg);

struct symbols main_block_symbols;
struct symbols* current_symbols = &main_block_symbols;
extern void error(int error_code, struct token mtoken) {
	printf("\nError %d truoc token %s(line %d, col %d)", error_code, tag_name[mtoken.tag], mtoken.line, mtoken.col);
	switch (error_code) {
		case 1: // Thieu dau , hoac ;
			printf("Thieu dau \",\" hoac \";\".\n");
			break;
		case 2: // Thieu number sau dau =.
			printf("= must be followed by a number.\n");
			break;
		case 3:
			printf("Thieu token END.\n");
			break;
		case 4:
			printf("Thieu tu khoa Program.\n");
			break;
		case 5:
			printf("Khong phai la mot block.\n");
			break;
		case 6:
			printf("const, var, procedure, call, program, for must be followed by identifier.\n");
			break;
		case 7:
			printf("Thieu dau \"=\" sau ident.\n");
			break;
		case 8:
			printf("Khong phai la mot chuong trinh.\n");
			break;
		case 9:
			printf("Khong phai la mot block.\n");
			break;
		case 10:
			printf("Thieu dau \".\".\n");
			break;
		case 11:
			printf("Thieu dau \"=\" sau ident.\n");
			break;
		case 12:
			printf("Identifier must be followed by =.\n");
			break;
		case 13:
			printf("Incorrect symbol after procedure declaration.\n");
			break;
		case 14:
			printf("Statement expected.\n");
			break;
		case 15:
			printf("call must be followed by an identifier.\n");
			break;
		case 16:
			printf("then expected.\n");
			break;
		case 17:
			printf("Thieu dau ] hoac }.\n");
			break;
		case 18:
			printf("do expected.\n");
			break;
		case 19:
			printf("Thieu dau dong ngoac ).\n");
			break;
		case 20:
			printf("Thieu ident sau tu khoa const.\n");
			break;
		case 21:
			printf("Thieu dau \"=\" sau ident.\n");
			break;
		case 22:
			printf("Thieu so.\n");
			break;
		case 23:
			printf("Thieu phep gan.\n");
			break;
		case 24:
			printf("Thieu token TO hoac ;.\n");
			break;
		case 25:
			printf("Khong phai mot statement.\n");
			break;
		case 26:
			printf("Thieu toan tu so sanh.\n");
			break;
		case 27:
			printf("Thieu tu khoa while.\n");
			break;
		case 28:
			printf("Thieu Ident trong for.\n");
			break;
		case 29:
			printf("Thieu dau ( hoac ident sau for.\n");
			break;
		case 30:
			printf("Thieu dau :.\n");
			break;
		case 31:
			printf("Thieu dau ?\n.");
			break;
		case 32:
			printf("Khong phai la factor\n.");
			break;
	}
	exit(-1);
}

extern void printferror(struct token mtoken, char* msg) {
	printf("\nError truoc token %s(line %d, col %d)", tag_name[mtoken.tag], mtoken.line, mtoken.col);
	printf("%s", msg);
	exit(-1);
}

extern void error_semantic(struct token mtoken, char* msg) {
	printf("\nError token %s(line %d, col %d) \n", mtoken.attribute, mtoken.line, mtoken.col);
	printf("%s\n", msg);
	exit(-1);
}

extern int parse_program(struct token* current_token, void (*get_token)(struct token* next_token)) {
	printf("parse program: ");
	main_block_symbols.parent = NULL;
	print_token(*current_token);
	if (current_token->tag == TEND) {
		error(4, *current_token);
		return -1;
	}
	if (current_token->tag == TPROGRAM) {
		(*get_token)(current_token);
		if (current_token->tag == TIDENT) {
			(*get_token)(current_token);
			if (current_token->tag == TSCOLON) {
				(*get_token)(current_token);
				parse_block(current_token, get_token);
				if (current_token->tag == TDOT) {
					printf("\n\n\nparse successfull\n\n\n");
					return 0;
				} else {	// thieu dau .
					error(10, *current_token);
					return 10;
				}
			} else { //thieu dau ;
				error(1, *current_token);
				return 1;
			}
		} else {
			error(6, *current_token);
			return 6;
		}
	} else {
		error(4, *current_token);
		return 4;
	}
	// cannot reach
	(*get_token)(current_token);
	return 0;
}

extern int parse_factor(struct token* current_token, void (*get_token)(struct token* next_token)) {
	printf("parse_factor: ");
	print_token(*current_token);
	if (current_token->tag == TIDENT) {
		// coppy token
		struct token tmp;
		strcpy(tmp.attribute, current_token->attribute);
		tmp.col = current_token->col;
		tmp.line = current_token->line;
		(*get_token)(current_token);
		if (current_token->tag == TLBRACE) { // Array
			int code = find_declared(current_symbols, tmp.attribute, ITARRAY);
			switch (code) {
				case 1: // chua khai bao
					error_semantic(tmp, "Mang chua duoc khai bao.\0");
				break;
				case 0: // da khai bao
				break;
				case ITARRAY: // khong the xay ra
				break;
				case ITCONSTANT:
					error_semantic(tmp, "Khong the su dung hang nhu 1 mang.\0");
				break;
				case ITPROCEDURE:
					error_semantic(tmp, "Khong the su dung thu tuc nhu 1 mang.\0");
				break;
				case ITVARIABLE:
					error_semantic(tmp, "Khong the su dung bien nhu 1 mang.\0");
				break;
			}
			(*get_token)(current_token);
			parse_expression(current_token, get_token);
			if (current_token->tag == TRBRACE) {
				(*get_token)(current_token);
				return 0;
			} else { // Thieu dau ]
				error(17, *current_token);
				return 17;
			}
		}
		// variable or constant
		int code = find_declared(current_symbols, tmp.attribute, ITVARIABLE);
		switch (code) {
			case 1: // chua khai bao
				error_semantic(tmp, "Bien/Hang chua duoc khai bao.\0");
			break;
			case 0: // da khai bao
			break;
			case ITARRAY:
				error_semantic(tmp, "Thieu index cho mang.\0");
			break;
			case ITCONSTANT:
				// ok
			break;
			case ITPROCEDURE:
				error_semantic(tmp, "Khong the su dung thu tuc nhu 1 bien.\0");
			break;
			case ITVARIABLE: // Khong the xay ra
			break;
		}
		return 0;
	} else if (current_token->tag == TNUMBER) {
		(*get_token)(current_token);
		return 0;
	} else if (current_token->tag == TLPAREN) {
		(*get_token)(current_token);
		parse_expression(current_token, get_token);
		if (current_token->tag == TRPAREN) {
			(*get_token)(current_token);
			return 0;
		} else { // Thieu dong ngoac
			error(19, *current_token);
			return 19;
		}
		return 0;
	} else {
		// not a factor
		error(32, *current_token);
		return 32;
	}
	return 0;
}

extern int parse_term(struct token* current_token, void (*get_token)(struct token* next_token)) {
	printf("parse_term: ");
	print_token(*current_token);
	parse_factor(current_token, get_token);
	while (current_token->tag == TMUL || current_token->tag == TDIV) {
		(*get_token)(current_token);
		parse_factor(current_token, get_token);
	}
	return 0;
}

extern int parse_expression(struct token* current_token, void (*get_token)(struct token* next_token)) {
	printf("parse_expression: ");
	print_token(*current_token);
	switch (current_token->tag) {
		case TPLUS:
		case TMINUS:
			(*get_token)(current_token);
		default:
			parse_term(current_token, get_token);
			while (current_token->tag == TPLUS || current_token->tag == TMINUS) {
				(*get_token)(current_token);
				parse_term(current_token, get_token);
			}
			printf("end parse_expression: ");
			return 0;
	}
	// cannot reach
	printf("end parse_expression: ");
	return 0;
}

extern int parse_block(struct token* current_token, void (*get_token)(struct token* next_token)) {
	printf("parse_block: ");
	print_token(*current_token);
	if (current_token->tag == TENDT) {
		error(5, *current_token);
		return -1;
	}
	if (current_token->tag == TCONST) {
		do {
			(*get_token)(current_token);
			if (current_token->tag == TIDENT) {
				// coppy token
				struct token tmp;
				strcpy(tmp.attribute, current_token->attribute);
				tmp.col = current_token->col;
				tmp.line = current_token->line;
				(*get_token)(current_token);
				// kiem tra va add constant
				if (!is_exist_name(current_symbols, tmp.attribute, ITCONSTANT)) {
					add_ident(current_symbols, current_token->attribute, ITCONSTANT);
				} else {
					error_semantic(*current_token, "Khai bao hang trung ten\n\0");
				}
				if (current_token->tag == TEQUAL) {
					(*get_token)(current_token);
					if (current_token->tag == TNUMBER) {
						(*get_token)(current_token);
					} else { // Thieu number sau dau =
						error(2, *current_token);
						return 2;
					}
				} else { // Thieu dau "="
					error(7, *current_token);
					return 7;
				}
			} else { // Thieu ident
				error(6, *current_token);
				return 6;
			}
		} while (current_token->tag == TCOMMA);
		// Test ;
		if (current_token->tag == TSCOLON) {
			(*get_token)(current_token);
			// continue
		} else { // thieu dau ;
			error(1, *current_token);
			return 1;
		}
	}
	if (current_token->tag == TVAR) {
		do {
			(*get_token)(current_token);
			if (current_token->tag == TIDENT) {
				// coppy token
				struct token tmp;
				strcpy(tmp.attribute, current_token->attribute);
				tmp.col = current_token->col;
				tmp.line = current_token->line;
				(*get_token)(current_token);
				// check array?
				if (current_token->tag == TLBRACE) { // "[" => array
					// check and add ident array
					if (!is_exist_name(current_symbols, tmp.attribute, ITARRAY)) {
						add_ident(current_symbols, tmp.attribute, ITARRAY);
					} else {
						error_semantic(*current_token, "Khai bao mang trung ten\n\0");
					}
					(*get_token)(current_token);
					if (current_token->tag == TNUMBER) {
						(*get_token)(current_token);
						if (current_token->tag == TRBRACE) {
							(*get_token)(current_token);
						} else {
							error(17, *current_token);
							return 17;
						}
					} else {
						return 17;
						error(22, *current_token);
					}
				} else { // La bien
					// kiem tra va add bien
					if (!is_exist_name(current_symbols, tmp.attribute, ITVARIABLE)) {
						add_ident(current_symbols, tmp.attribute, ITVARIABLE);
					} else {
						error_semantic(*current_token, "Khai bao bien trung ten\n\0");
					}
				}
			} else { // Thieu IDENT
				error(6, *current_token);
				return 6;
			}
		} while (current_token->tag == TCOMMA);
		// Test ;
		if (current_token->tag == TSCOLON) {
			(*get_token)(current_token);
			// continue
		} else { // thieu dau ;
			error(1, *current_token);
			return 1;
		}
	}
	if (current_token->tag == TPROCEDURE) {
		(*get_token)(current_token);
		if (current_token->tag == TIDENT) {
			// check semantic
			if (!is_exist_name(current_symbols, 
					current_token->attribute, ITPROCEDURE)) {
				//add ident va tao bang symbols moi
				current_symbols = add_ident_procedure(current_symbols, 
					current_token->attribute, ITPROCEDURE);
			} else {
				error_semantic(*current_token, "Khai bao thu tuc trung ten.\n\0");
			}
			(*get_token)(current_token);
			if (current_token->tag == TLPAREN) { // TLPAREN
				do {
					(*get_token)(current_token);
					// VAR is optionnal
					if (current_token->tag == TVAR) {
						(*get_token)(current_token);
					}

					if (current_token->tag == TIDENT) {
						// check semantic
						if (!is_exist_name(current_symbols, 
								current_token->attribute, ITVARIABLE)) {
							add_ident(current_symbols, 
								current_token->attribute, ITVARIABLE);
						} else {
							error_semantic(*current_token, "Khai bao tham so trung ten\n\0");
						}
						(*get_token)(current_token);
					} else {
						error(6, *current_token);
						return 6;
					}
				} while (current_token->tag == TSCOLON);
				// Test ")"
				printf("Oh yeah\n");
				//(*get_token)(current_token);
				if (current_token->tag == TRPAREN) {
					(*get_token)(current_token);
				} else {
					error(19, *current_token);
					return 19;
				}
			} 
			// ; block ;
			if (current_token->tag == TSCOLON) {
				(*get_token)(current_token);
				parse_block(current_token, get_token);
				// check semantic : exit procedure symbols
				current_symbols = find_parent(current_symbols);
				if (current_token->tag == TSCOLON) {
					(*get_token)(current_token);
					// continue
				} else { // thieu dau ;
					error(1, *current_token);
					return 1;
				}
			} else { // thieu dau ;
				error(1, *current_token);
				return 1;
			}
		}
		else { // Thieu ident sau procedure
			error(6, *current_token);
		}
	}
	if (current_token->tag == TBEGIN) {
		do {
			(*get_token)(current_token);
			parse_statement(current_token, get_token);
		} while (current_token->tag == TSCOLON);
		if (current_token->tag == TEND) {
			(*get_token)(current_token);
			return 0;
		} else {
			printf("error here\n");
			error(3, *current_token);
			return 3;
		}
	}
	printferror(*current_token, "Thieu BEGIN trong block\n\0");
	return 0;
}

extern int parse_statement(struct token* current_token, void (*get_token)(struct token* next_token)) {
	printf("parse statement: ");
	print_token(*current_token);
	struct token tmp;
	switch (current_token->tag) {
		case TIDENT:
			// coppy token
			strcpy(tmp.attribute, current_token->attribute);
			tmp.col = current_token->col;
			tmp.line = current_token->line;
			(*get_token)(current_token);
			char is_error_constant = 0;
			// is array?
			if (current_token->tag == TLBRACE) {
				// kiem tra khai bao mang chua
				int code = find_declared(current_symbols, tmp.attribute, ITARRAY);
				switch (code) {
					case 1: // chua khai bao
						error_semantic(tmp, "Mang chua duoc khai bao.\0");
					break;
					case 0: // da khai bao
					break;
					case ITARRAY: // khong the xay ra
					break;
					case ITCONSTANT:
						error_semantic(tmp, "Khong the su dung hang nhu 1 mang.\0");
					break;
					case ITPROCEDURE:
						error_semantic(tmp, "Khong the su dung thu tuc nhu 1 mang.\0");
					break;
					case ITVARIABLE:
						error_semantic(tmp, "Khong the su dung bien nhu 1 mang.\0");
					break;
				}
				(*get_token)(current_token);
				parse_expression(current_token, get_token);
				if (current_token->tag == TRBRACE) {
					(*get_token)(current_token);
				} else { // Thieu dau ]
					error(17, *current_token);
					return 17;
				}
			} else { // is variable
				printf("Here I am 1\n");
				int code = find_declared(current_symbols, tmp.attribute, ITVARIABLE);
				printf("Here I am 1.5 %d\n", code);
				switch (code) {
					case 1: // chua khai bao
						error_semantic(tmp, "Bien/Hang chua duoc khai bao.\0");
					break;
					case 0: // da khai bao
					break;
					case ITARRAY:
						error_semantic(tmp, "Thieu index cho mang.\0");
					break;
					case ITCONSTANT:
						is_error_constant = 1;
					break;
					case ITPROCEDURE:
						error_semantic(tmp, "Khong the su dung thu tuc nhu 1 bien.\0");
					break;
					case ITVARIABLE: // Khong the xay ra
					break;
				}
			}
			if (current_token->tag == TASSIGN) {
				printf("Here I am 2\n");
				if (is_error_constant) {
					error_semantic(tmp, "Khong the gan gia tri cho hang.\0");
				}
				(*get_token)(current_token);
				parse_expression(current_token, get_token);
				switch (current_token->tag) {
					case TEQUAL:
					case TCGT:
					case TCGTEQ:
					case TCGTLT:
					case TCLT:
					case TCLTEQ:
						(*get_token)(current_token);
						parse_expression(current_token, get_token);
						if (current_token->tag == TQUESTION) {
							(*get_token)(current_token);
							parse_expression(current_token, get_token);
							if (current_token->tag == TCOLOM) {
								(*get_token)(current_token);
								parse_expression(current_token, get_token);
								printf("done parse statement\n");
								return 0;
							} else { // Thieu dau :
								error(30, *current_token);
								return 30;
							}
						} else { // Thieu dau ?
							error(31, *current_token);
							return 31;
						}
						break;
					default:
						printf("end parse statement: ");
						return 0;
				}
				printf("end parse statement: ");
				return 0;
			} else { // Thieu phep gan
				error(23, *current_token);
				return 23;
			}
			break;
		case TCALL:
			(*get_token)(current_token);
			if (current_token->tag == TIDENT) {
				strcpy(tmp.attribute, current_token->attribute);
				tmp.col = current_token->col;
				tmp.line = current_token->line;
				int n_param = 0;
				int code = find_procedure(current_symbols, current_token->attribute, &n_param);
				switch (code) {
					case 1: // chua khai bao
						error_semantic(tmp, "Thu tuc chua duoc khai bao.\0");
					break;
					case 0: // da khai bao
					break;
					case ITARRAY:
						error_semantic(tmp, "Khong the su dung mang nhu thu tuc.\0");
					break;
					case ITCONSTANT:
						error_semantic(tmp, "Khong the su dung hang nhu thu tuc.\0");
					break;
					case ITPROCEDURE: // Khong the xay ra
					break;
					case ITVARIABLE:
						error_semantic(tmp, "Khong the su dung bien nhu thu tuc.\0");
					break;
				}
				int real_n_param = 0;
				(*get_token)(current_token);
				// Co tham so?
				if (current_token->tag == TLPAREN) {
					(*get_token)(current_token);
					if (current_token->tag == TRPAREN) {
						// ok foo()
						(*get_token)(current_token);
					} else {
						printf("co tham so\n");
						parse_expression(current_token, get_token);
						real_n_param++;
						while (current_token->tag == TCOMMA) {
							printf("parse co tham so\n");
							(*get_token)(current_token);
							parse_expression(current_token, get_token);
							real_n_param++;
						}
						// check )
						if (current_token->tag == TRPAREN) {
							(*get_token)(current_token);
						} else { // Thieu dau dong ngoac
							error(19, *current_token);
							return 19;
						}
					}
				}
				// check semantic n_param
				if (real_n_param != n_param) {
					error_semantic(tmp, "So tham so truyen khong phu hop\n\0");
				}
				// Khong goi get_token vi da goi truoc roi.
				printf("end parse statement: ");
				return 0;
			} else { // Thieu ident
				error(6, *current_token);
				return 6;
			}
			break;
		case TBEGIN:
			// expect statement
			do {
				(*get_token)(current_token);
				parse_statement(current_token, get_token);
			} while (current_token->tag == TSCOLON);
			// expect end token
			if (current_token->tag == TEND) {
				(*get_token)(current_token);
				printf("end parse statement: ");
				return 0;
			} else {
				error(3, *current_token);
				return 3;
			}
			break;
		case TIF:
			(*get_token)(current_token);
			parse_condition(current_token, get_token);
			// expect THEN token
			if (current_token->tag == TTHEN) {
				(*get_token)(current_token);
				parse_statement(current_token, get_token);
				if (current_token->tag == TELSE) {
					(*get_token)(current_token);
					parse_statement(current_token, get_token);
				}
				printf("end parse statement: ");
				return 0;
			} else { // Thieu THEN
				error(16, *current_token);
				return 16;
			}
			break;
		case TWHILE:
			(*get_token)(current_token);
			parse_condition(current_token, get_token);
			// expect TDO token
			if (current_token->tag == TDO) {
				(*get_token)(current_token);
				parse_statement(current_token, get_token);
				printf("end parse statement: ");
				return 0;
			} else { // Thieu DO
				error(18, *current_token);
				return 18;
			}
			break;
		case TDO:
			do {
				(*get_token)(current_token);
				parse_statement(current_token, get_token);
			} while (current_token->tag == TSCOLON);
			// While?
			if (current_token->tag == TWHILE) {
				(*get_token)(current_token);
				parse_condition(current_token, get_token);
				printf("end parse statement: ");
				return 0;
			} else { // Thieu while
				error(27, *current_token);
				return 27;
			}
		case TFOR:
			(*get_token)(current_token);
			if (current_token->tag == TIDENT) {
				// check semantic
				int code = find_declared(current_symbols, current_token->attribute, ITVARIABLE);
				switch (code) {
					case 1: // chua khai bao
						error_semantic(*current_token, "Bien chua duoc khai bao.\0");
					break;
					case 0: // da khai bao
					break;
					case ITARRAY:
						error_semantic(*current_token, "Khong duoc su dung mang trong vong lap for.\0");
					break;
					case ITCONSTANT:
						error_semantic(*current_token, "Khong duoc su dung hang trong vong lap for.\0");
					break;
					case ITPROCEDURE:
						error_semantic(*current_token, "Khong the su dung thu tuc nhu 1 bien.\0");
					break;
					case ITVARIABLE: // Khong the xay ra
					break;
				}
				(*get_token)(current_token);
				if (current_token->tag == TASSIGN) {
					(*get_token)(current_token);
					parse_expression(current_token, get_token);
					if (current_token->tag == TTO) {
						(*get_token)(current_token);
						parse_expression(current_token, get_token);
						if (current_token->tag == TDO) {
							(*get_token)(current_token);
							parse_statement(current_token, get_token);
						} else { // Thieu token DO
							error(18, *current_token);
							return 18;
						}
					} else { // Thieu token TO
						error(24, *current_token);
						return 24;
					}
				} else { // Thieu phep gan
					error(23, *current_token);
					return 23;
				}
				// Khong goi get_token vi da goi truoc roi.
				printf("end parse statement: ");
				return 0;
			} else {
				// For kieu C, C++
				// check ( or fail
				if (current_token->tag == TLPAREN) {
					(*get_token)(current_token);
					if (current_token->tag == TIDENT) {
						int code = find_declared(current_symbols, current_token->attribute, ITVARIABLE);
						switch (code) {
							case 1: // chua khai bao
								error_semantic(*current_token, "Bien chua duoc khai bao.\0");
							break;
							case 0: // da khai bao
							break;
							case ITARRAY:
								error_semantic(*current_token, "Khong duoc su dung mang trong vong lap for.\0");
							break;
							case ITCONSTANT:
								error_semantic(*current_token, "Khong duoc su dung hang trong vong lap for.\0");
							break;
							case ITPROCEDURE:
								error_semantic(*current_token, "Khong the su dung thu tuc nhu 1 bien.\0");
							break;
							case ITVARIABLE: // Khong the xay ra
							break;
						}
						(*get_token)(current_token);
						if (current_token->tag == TASSIGN) {
							(*get_token)(current_token);
							parse_expression(current_token, get_token);
							if (current_token->tag == TSCOLON) {
								(*get_token)(current_token);
								parse_condition(current_token, get_token);
								if (current_token->tag == TSCOLON) {
									(*get_token)(current_token);
									if (current_token->tag == TIDENT) {
										(*get_token)(current_token);
										if (current_token->tag == TASSIGN) {
											(*get_token)(current_token);
											parse_expression(current_token, get_token);
											if (current_token->tag == TRPAREN) {
												(*get_token)(current_token);
												parse_statement(current_token, get_token);
												//
												printf("parse statement done\n");
												return 0;
											} else { // Thieu dau dong ngoac
												error(19, *current_token);
												return 19;
											}
										} else { // Thieu assign 2 trong for
											error(23, *current_token);
											return 23;
										}
									} else { // Thieu ident 2 trong for
										error(6, *current_token);
										return 6;
									}
								} else { // Thieu dau ; 2 trong for
									error(1, *current_token);
									return 1;
								}
							} else { // Thieu ; trong for
								error(1, *current_token);
								return 1;
							}
						} else { //Thieu phep gan trong ve 1 cua for
							error(23, *current_token);
							return 23;
						}
					} else { // Thieu iden trong for
						error(6, *current_token);
						return 6;
					}
				} else { // Thieu dau ( hoac ident sau for
					error(29, *current_token);
					return 29;
				}
			}
			break;
		default:
			printf("default\n");
			//(*get_token)(current_token);
			return 0;
	}
	(*get_token)(current_token);
	return 0;
}

extern int parse_condition(struct token* current_token, void (*get_token)(struct token* next_token)) {
	printf("parse condition: ");
	print_token(*current_token);
	parse_expression(current_token, get_token);
	switch (current_token->tag) {
		case TEQUAL:
		case TCGT:
		case TCGTEQ:
		case TCGTLT:
		case TCLT:
		case TCLTEQ:
			(*get_token)(current_token);
			parse_expression(current_token, get_token);
			printf("done parse condition: ");
			return 0;
		default:
			error(26, *current_token);
			return 26;
	}
}

#endif
