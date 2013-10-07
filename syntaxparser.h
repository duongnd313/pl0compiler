#ifndef PARSER_H
#define PARSER_H

#include "token.h"
#include "lexer.h"
#include "tag.h"
#include <stdlib.h>
extern int parse_program(struct token* current_token, void (*get_token)(struct token* next_token));
extern int parse_factor(struct token* current_token, void (*get_token)(struct token* next_token));
extern int parse_expression(struct token* current_token, void (*get_token)(struct token* next_token));
extern int parse_block(struct token* current_token, void (*get_token)(struct token* next_token));
extern int parse_statement(struct token* current_token, void (*get_token)(struct token* next_token));
extern int parse_condition(struct token* current_token, void (*get_token)(struct token* next_token));
extern int parse_term(struct token* current_token, void (*get_token)(struct token* next_token));
extern void error(int error_code, struct token mtoken);

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

extern int parse_program(struct token* current_token, void (*get_token)(struct token* next_token)) {
	printf("parse program: ");
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
		(*get_token)(current_token);
		if (current_token->tag == TLBRACE) {
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
	switch (current_token->tag) {
		case TCONST:
			do {
				(*get_token)(current_token);
				if (current_token->tag == TIDENT) {
					(*get_token)(current_token);
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
				parse_block(current_token, get_token);
				return 0;
			} else { // thieu dau ;
				error(1, *current_token);
				return 1;
			}
			break;
		case TVAR:
			do {
				(*get_token)(current_token);
				if (current_token->tag == TIDENT) {
					(*get_token)(current_token);
					// check array?
					if (current_token->tag == TLBRACE) { // "[" => array
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
					}
				} else { // Thieu IDENT
					error(6, *current_token);
					return 6;
				}
			} while (current_token->tag == TCOMMA);
			// Test ;
			if (current_token->tag == TSCOLON) {
				(*get_token)(current_token);
				parse_block(current_token, get_token);
				return 0;
			} else { // thieu dau ;
				error(1, *current_token);
				return 1;
			}
			break;
		case TPROCEDURE:
			(*get_token)(current_token);
			if (current_token->tag == TIDENT) {
				(*get_token)(current_token);
				if (current_token->tag == TLPAREN) { // TLPAREN
					do {
						(*get_token)(current_token);
						// VAR is optionnal
						if (current_token->tag == TVAR) {
							(*get_token)(current_token);
						}
						//(*get_token)(current_token);
						if (current_token->tag == TIDENT) {
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
					if (current_token->tag == TSCOLON) {
						(*get_token)(current_token);
						parse_block(current_token, get_token);
						return 0;
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
			break;
		case TBEGIN:
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
			break;
		default:
			error(5, *current_token);
			return -1;
	}
	// cannot reach
	(*get_token)(current_token);
	return 0;
}

extern int parse_statement(struct token* current_token, void (*get_token)(struct token* next_token)) {
	printf("parse statement: ");
	print_token(*current_token);
	switch (current_token->tag) {
		case TIDENT:
			(*get_token)(current_token);
			// is array?
			if (current_token->tag == TLBRACE) {
				(*get_token)(current_token);
				parse_expression(current_token, get_token);
				if (current_token->tag == TRBRACE) {
					(*get_token)(current_token);
				} else { // Thieu dau ]
					error(17, *current_token);
					return 17;
				}
			}
			if (current_token->tag == TASSIGN) {
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
						while (current_token->tag == TCOMMA) {
							printf("parse co tham so\n");
							(*get_token)(current_token);
							parse_expression(current_token, get_token);
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
			} else { // check ( or fail
				if (current_token->tag == TLPAREN) {
					(*get_token)(current_token);
					if (current_token->tag == TIDENT) {
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
