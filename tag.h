#ifndef TAG_H
#define TAG_H

#define NUM_KEYWORD 16
enum token_tag {
	// CONST
	TCONST,
	// BEGIN = 25
	TBEGIN,
	// CALL
	TCALL,
	// CONST
	TCOST,
	// DO
	TDO,
	// END
	TEND,
	// ELSE=30
	TELSE,
	// FOR
	TFOR,
	// IF
	TIF,
	// ODD
	TODD,
	// PROCEDURE
	TPROCEDURE,
	// PROGRAM
	TPROGRAM,
	// THEN
	TTHEN,
	// TO
	TTO,
	// VAR
	TVAR,
	// WHILE
	TWHILE,
	// name
	TIDENT,
	// number
	TNUMBER,
	// true
	TTRUE,
	// false
	TFALSE,
	// +
	TPLUS,
	// -
	TMINUS,
	// *
	TMUL,
	// /
	TDIV,
	// %
	TPERCENT,
	// (
	TLPAREN,
	// ) = 10
	TRPAREN,
	// [
	TLBRACE,
	// ]
	TRBRACE,
	// {
	TLCBRACE,
	// }
	TRCBRACE,
	// >
	TCGT,
	// <
	TCLT,
	// =
	TEQUAL,
	// ,
	TCOMMA,
	// ;
	TSCOLON,
	// .=20
	TDOT,
	// :=
	TASSIGN,
	// >=
	TCGTEQ,
	// <=
	TCLTEQ,
	// <>
	TCGTLT,
	// :
	TCOLOM,
	// ?
	TQUESTION,
	// ERROR=40
	TERROR,
	// TNONE
	TENDT
	};
	
char tag_name[45][48] = {
	// CONST
	"TCONST",
	// BEGIN
	"TBEGIN",
	// CALL
	"TCALL",
	// CONST
	"TCOST",
	// DO
	"TDO",
	// END
	"TEND",
	// ELSE=30
	"TELSE",
	// FOR
	"TFOR",
	// IF
	"TIF",
	// ODD
	"TODD",
	// PROCEDURE
	"TPROCEDURE",
	// PROGRAM
	"TPROGRAM",
	// THEN
	"TTHEN",
	// TO
	"TTO",
	// VAR
	"TVAR",
	// WHILE
	"TWHILE",
	// name
	"TIDENT",
	// number
	"TNUMBER",
	// true
	"TTRUE",
	// false
	"TFALSE",
	// +
	"TPLUS",
	// -
	"TMINUS",
	// *
	"TMUL",
	// /
	"TDIV",
	// %
	"TPERCENT",
	// (
	"TLPAREN",
	// )
	"TRPAREN",
	// [
	"TLBRACE",
	// ]
	"TRBRACE",
	// {
	"TLCBRACE",
	// }
	"TRCBRACE",
	// >
	"TCGT",
	// <
	"TCLT",
	// =
	"TEQUAL",
	// ,
	"TCOMMA",
	// ;
	"TSCOLON",
	// .
	"TDOT",
	// :=
	"TASSIGN",
	// >=
	"TCGTEQ",
	// <=
	"TCLTEQ",
	// <>
	"TCGTLT",
	// COLOM
	"COLOM",
	// QUESTION
	"QUESTION",
	// ERROR
	"TERROR",
	// TNONE
	"TENDT"
	};
	
char tag_keyword_name[NUM_KEYWORD][48] = {
	// CONST
	"CONST",
	// BEGIN
	"BEGIN",
	// CALL
	"CALL",
	// CONST
	"CONST",
	// DO
	"DO",
	// END
	"END",
	// ELSE=30
	"ELSE",
	// FOR
	"FOR",
	// IF
	"IF",
	// ODD
	"ODD",
	// PROCEDURE
	"PROCEDURE",
	// PROGRAM
	"PROGRAM",
	// THEN
	"THEN",
	// TO
	"TO",
	// VAR
	"VAR",
	// WHILE
	"WHILE"
};
#endif
