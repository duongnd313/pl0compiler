#ifndef LEXER_H
#define LEXER_H
#include "lexer.h"
#include "tag.h"
#include "token.h"
#include "stdio.h"
#include <ctype.h>
#include <string.h>
extern int isletter(char c);
extern int get_keyword(char* str);
extern struct token* get_token(FILE* f, char* c_before, struct token* mtoken);
extern void print_token(struct token mtoken);

extern int isletter(char c) {
	return (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z'));
};

extern int get_keyword(char* str) {
	int i;
	for (i = 0; i < NUM_KEYWORD; i++) {
		if (strcasecmp(str, tag_keyword_name[i]) == 0) {
			return i;
		}
	}
	return -1;
}

int line=1;
int col=1;

extern struct token* get_token(FILE* f, char* c_before, struct token* mtoken) {
	char ch = *c_before;
	
	while (ch != EOF) {
		// space
		if (ch == '\n') {
			line++;
			col = 1;
		} else {
			col++;
		}
		mtoken->line = line;
		mtoken->col = col;
		if (isspace(ch)) {
			// skip
			ch = fgetc(f);
		} 
		// digit
		else if (isdigit(ch)) {
			char value[MAX_NUM_LENGTH + 1];
			value[0] = ch;
			int i=1;
			while(1) {
				ch = fgetc(f);
				if (i > MAX_NUM_LENGTH + 1) {
					mtoken->tag = TERROR;
					strcpy(mtoken->attribute, "So nguyen dai hon 6 chu so");
					return mtoken;
				}
				if (isdigit(ch)) {
					value[i] = ch;
					i++;
				} else {
					*c_before = ch;
					value[i] = '\0';
					mtoken->tag = TNUMBER;
					strcpy(mtoken->attribute, value);
					return mtoken;
				}
			}
		} else if (isletter(ch)) {
			char value[MAX_IDENT_LENGTH + 1];
			value[0] = ch;
			int i = 1;
			while (1) {
				ch = fgetc(f);
				if (i > MAX_IDENT_LENGTH + 1) {
					mtoken->tag = TERROR;
					value[i] = '\0';
					strcpy(mtoken->attribute, value);
					return mtoken;
				}
				if (isdigit(ch) || isletter(ch)) {
					value[i] = ch;
					i++;
				} else {
					*c_before = ch;
					value[i] = '\0';
					// check keyword
					int key_index = get_keyword(value);
					if (key_index == -1) {
						mtoken->tag = TIDENT;
						strcpy(mtoken->attribute, value);
					} else {
						mtoken->tag = key_index;
					}
					return mtoken;
				}
			}
		} else {
			switch (ch) {
			case '+':
					mtoken->tag = TPLUS;
					*c_before = fgetc(f);
					return mtoken;
			case '-':
					mtoken->tag = TMINUS;
					*c_before = fgetc(f);
					return mtoken;
			case '*':
					mtoken->tag = TMUL;
					*c_before = fgetc(f);
					return mtoken;
			case '/':
					mtoken->tag = TDIV;
					*c_before = fgetc(f);
					return mtoken;
			case '%':
					mtoken->tag = TPERCENT;
					*c_before = fgetc(f);
					return mtoken;
			case '(':
				//printf("(");
					ch = fgetc(f);
					if (ch == '*') {
						//printf("*");
						while (ch != EOF) {
							ch = fgetc(f);
							if (ch == '*') {
								//printf("*");
								ch = fgetc(f);
								if (ch == ')') {
									//printf(")");
									break;
								}
							}
						}
						if (ch == EOF) {
							mtoken->tag = TERROR;
							strcpy(mtoken->attribute, "Loi comment");
							*c_before =	ch;
							return mtoken;
						} else {
							ch = fgetc(f);
							*c_before =	ch;
							printf("TCOMMENT\n");
							break;
						}
					}
					else {
						mtoken->tag = TLPAREN;
						*c_before =	ch;
					}
					return mtoken;
					
					/*
					mtoken->tag = ;
					*c_before = fgetc(f);
					return mtoken;*/
			case ')':
					mtoken->tag = TRPAREN;
					*c_before = fgetc(f);
					return mtoken;
			case '[':
					mtoken->tag = TLBRACE;
					*c_before = fgetc(f);
					return mtoken;
			case ']':
					mtoken->tag = TRBRACE;
					*c_before = fgetc(f);
					return mtoken;
			case '{':
					mtoken->tag = TLCBRACE;
					*c_before = fgetc(f);
					return mtoken;
			case '}':
					mtoken->tag = TRCBRACE;
					*c_before = fgetc(f);
					return mtoken;
			case '>':
					ch = fgetc(f);
					if (ch == '=') {
						mtoken->tag = TCGTEQ;
						*c_before = fgetc(f);
					}
					else {
						*c_before = ch;
						mtoken->tag = TCGT;
					}
					return mtoken;
			case '<':
					ch = fgetc(f);
					if (ch == '=') {
						mtoken->tag = TCLTEQ;
						*c_before = fgetc(f);
					} else if (ch == '>') {
						mtoken->tag = TCGTLT;
						*c_before = fgetc(f);
					}
					else {
						*c_before = ch;
						mtoken->tag = TCLT;
					}
					return mtoken;
			case '=':
					mtoken->tag = TEQUAL;
					*c_before = fgetc(f);
					return mtoken;
			case ',':
					mtoken->tag = TCOMMA;
					*c_before = fgetc(f);
					return mtoken;
			case ';':
					mtoken->tag = TSCOLON;
					*c_before = fgetc(f);
					return mtoken;
			case '.':
					mtoken->tag = TDOT;
					*c_before = fgetc(f);
					return mtoken;
			case ':':
					ch = fgetc(f);
					if (ch == '=') {
						mtoken->tag = TASSIGN;
						*c_before = fgetc(f);
					}
					else {
						mtoken->tag = TCOLOM;
						*c_before = fgetc(f);
					}
					return mtoken;
			case '?':
					printf("hoi cham");
					mtoken->tag = TQUESTION;
					*c_before = fgetc(f);
					return mtoken;
				default:
					mtoken->tag = TERROR;
					strcpy(mtoken->attribute ,"Unknow token");
					return mtoken;
			}
				
		}
	}
	mtoken->tag = TENDT;
	return mtoken;
}

extern void print_token(struct token mtoken) {
	switch (mtoken.tag) {
		case TIDENT:
		case TERROR:
		case TNUMBER:
			printf("%s(%s)\n", tag_name[mtoken.tag], mtoken.attribute);
			break;
		default:
			printf("%s\n", tag_name[mtoken.tag]);
			break;
			
	}
}
#endif
