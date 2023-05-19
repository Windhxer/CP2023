%{
#include <iostream>
#include "AST.hpp"
using namespace std;
using namespace AST;

int yylex(void);
void yyerror(const char *s) {
    printf("Error: %s\n", s);
    exit(1); 
}

Node* root;
%}

%output "parser.cpp"

%union{
	Node* node;
}

%token	COMMA ELLIPSES DOT SQUOTE DQUOTE SEMI QUES COLON
		LPAREN RPAREN LBRACKET RBRACKET LBRACE RBRACE
		SHLEQ SHL SHREQ SHR
		EQ GE GT LE LT NEQ NOT ASSIGN
		AND BANDEQ BAND OR BOREQ BOR
		ARW BXOREQ BXOR BNOT
		DADD ADDEQ ADD DSUB SUBEQ SUB
		MULEQ MUL DIVEQ DIV MODEQ MOD
		STRUCT UNION TYPEDEF CONST ENUM
		IF ELSE FOR WHILE DO SWITCH CASE DEFAULT 
		BREAK CONTINUE RETURN SIZEOF
		SHORT INT LONG CHAR FLOAT DOUBLE VOID

%token<node> INTEGER IDENTIFIER REAL CHARACTER STRING

%nonassoc IF
%nonassoc ELSE


%left	COMMA //15
%left	ARGS// 仅用来指定优先级
%right	ASSIGN ADDEQ SUBEQ MULEQ DIVEQ MODEQ SHLEQ SHREQ BANDEQ BOREQ BXOREQ //15
%right	QUES COLON //14
%left	OR//13
%left	AND//12
%left	BOR//11
%left	BXOR//10
%left	BAND//9
%left	EQ NEQ//8
%left	GE GT LE LT//7
%left	SHL SHR//6
%left	ADD SUB//5
%left	TYPE_CHANGE//4，仅用来指定优先级
%left	MUL DIV MOD//3
%right	NOT DADD DSUB BNOT SIZEOF//2, ++a, --a
%left	DOT ARW//1, a++, a--

%%

Program:		Decls
				;

Decls:			Decls Decl
			|
			;

Decl:			VarDecl
			|	TypeDecl
			|	FunDecl
			;

VarDecl:		DataType VarList SEMI
			;

DataType:		BuildInType
			|	STRUCT LBRACE FieldDecls RBRACE
			|	UNION LBRACE FieldDecls RBRACE
			|	ENUM LBRACE EnumList RBRACE
			|	DataType MUL
			|	IDENTIFIER /* typedef */
			;

BuildInType:	SHORT
			|	INT
			|	LONG
			|	CHAR
			|	FLOAT
			|	DOUBLE
			;

FieldDecls:		FieldDecls FieldDecl
			|
			;

FieldDecl:		DataType MemList SEMI
			|	SEMI
			;

MemList:		MemList COMMA IDENTIFIER
			|	IDENTIFIER
			;

EnumList:		EnumList_ COMMA Enum
			|	Enum
			|
			;

EnumList_:		EnumList_ COMMA Enum
			|	Enum
			;

Enum:			IDENTIFIER
			|	IDENTIFIER ASSIGN INTEGER
			;

VarList:		Var COMMA VarList
			|	Var
			;

Var:			IDENTIFIER
			|	IDENTIFIER ASSIGN Exp
			;

TypeDecl:		TYPEDEF DataType IDENTIFIER SEMI
			;

FunDecl:		ReturnType IDENTIFIER LPAREN ArgList RPAREN SEMI
			|	ReturnType IDENTIFIER LPAREN ArgList RPAREN FunBody
			;

ReturnType:		DataType
			|	VOID

ArgList:		ArgList_ COMMA Arg
			|	ArgList_ COMMA ELLIPSES
			|	Arg
			|	ELLIPSES
			|	VOID
			|
			;

ArgList_:		ArgList_ COMMA Arg
			|	Arg
			;

Arg:			DataType IDENTIFIER
			|	DataType
			;

FunBody:		LBRACE Stms RBRACE
			;

Stms:			Stms Stm
			|
			;

Stm:			Exp SEMI
			|	IfStm
			|	ForStm
			|	WhileStm
			|	DoStm
			|	SwitchStm
			|	BreakStm
			|	ContinueStm
			|	ReturnStm
			|	Block
			|	VarDecl
			|	TypeDecl
			|	SEMI
			;

				// a[2]
Exp:			Exp LBRACKET Exp RBRACKET %prec DOT
			|	SIZEOF LPAREN IDENTIFIER RPAREN
			|	SIZEOF LPAREN Exp RPAREN
			|	SIZEOF LPAREN DataType RPAREN
				// fun()
			|	IDENTIFIER LPAREN ExpList RPAREN
			|	Exp DOT IDENTIFIER
			|	Exp ARW IDENTIFIER
			|	ADD Exp %prec NOT
			|	SUB Exp %prec NOT
				// (int)a
			|	LPAREN DataType RPAREN Exp %prec TYPE_CHANGE
			|	DADD Exp %prec NOT
			|	Exp DADD %prec DOT
			|	DSUB Exp %prec NOT
			|	Exp DSUB %prec DOT
			|	MUL Exp %prec NOT
			|	BAND Exp %prec NOT
			|	NOT Exp %prec NOT
			|	BNOT Exp %prec NOT
			|	Exp DIV Exp
			|	Exp MUL Exp
			|	Exp MOD Exp
			|	Exp ADD Exp
			|	Exp SUB Exp
			|	Exp SHL Exp
			|	Exp SHR Exp
			|	Exp GE Exp
			|	Exp GT Exp
			|	Exp LE Exp
			|	Exp LT Exp
			|	Exp EQ Exp
			|	Exp NEQ Exp
			|	Exp BAND Exp
			|	Exp BXOR Exp
			|	Exp BOR Exp
			|	Exp AND Exp
			|	Exp OR Exp
			|	Exp QUES Exp COLON Exp
			|	Exp ASSIGN Exp
			|	Exp MULEQ Exp
			|	Exp DIVEQ Exp
			|	Exp MODEQ Exp
			|	Exp ADDEQ Exp
			|	Exp SUBEQ Exp
			|	Exp SHLEQ Exp
			|	Exp SHREQ Exp
			|	Exp BANDEQ Exp
			|	Exp BXOREQ Exp
			|	Exp BOREQ Exp
			|	LPAREN Exp RPAREN
			|	IDENTIFIER
			|	Constant
			|	Exp	COMMA Exp
			;

IfStm:			IF LPAREN Exp RPAREN Stm ELSE Stm
			|	IF LPAREN Exp RPAREN Stm
			;

ForStm:			FOR LPAREN Exp SEMI Exp SEMI Exp RPAREN Stm
			|	FOR LPAREN VarDecl SEMI Exp SEMI Exp RPAREN Stm
			;

WhileStm:		WHILE LPAREN Exp RPAREN Stm
			;

DoStm:			DO Stm WHILE LPAREN Exp RPAREN SEMI
			;

SwitchStm:		SWITCH LPAREN Exp RPAREN LBRACE CaseList RBRACE
			;

CaseList:		CaseList CaseStm
			|
			;

CaseStm:		CASE Exp COLON Stms
			|	DEFAULT COLON Stms
			;

ContinueStm:	CONTINUE SEMI
			;

BreakStm:		BREAK
			;

ReturnStm:		RETURN SEMI
			|	RETURN Exp SEMI
			;

Block:			LBRACE Stms RBRACE
			;

ExpList:		ExpList_ COMMA Exp
			|	Exp %prec ARGS
			|
			;

ExpList_:		ExpList_ COMMA Exp
			|	Exp %prec ARGS
			;
Constant:		
				CHARACTER
			|	INTEGER
			|	REAL
			|	STRING
			;

%%
