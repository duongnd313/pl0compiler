#ifndef TAG_H
#define TAG_H

#define NUM_KEYWORD 15
enum token_tag {
	// BEGIN = 25
	TBEGIN = 0,
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
	// ERROR=40
	TERROR,
	// TNONE
	TENDT
	};
	
extern char tag_name[42][48] = {
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
	// ERROR
	"TERROR",
	// TNONE
	"TENDT"
	};
	
extern char tag_keyword_name[NUM_KEYWORD][48] = {
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
