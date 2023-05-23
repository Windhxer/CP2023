%{
#include <cstdlib>
#include <cstdio>
#include <string>
#include "tree.h"
#include "block.h"
#include "Praser.h"
using namespace std;

extern char *yytext;
extern int column;
extern FILE * yyin;
extern FILE * yyout;
treeNode *root;
extern int yylineno;

int yylex(void);
void yyerror(const char*); 
%}

%union{
	struct treeNode* nd;
}
%token <nd> IDENTIFIER CONSTANT STRING_LITERAL SIZEOF CONSTANT_INT CONSTANT_DOUBLE
%token <nd> PTR_OP INC_OP DEC_OP LEFT_OP RIGHT_OP LE_OP GE_OP EQ_OP NE_OP
%token <nd> AND_OP OR_OP MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN
%token <nd> SUB_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN
%token <nd> XOR_ASSIGN OR_ASSIGN TYPE_NAME

%token <nd> CHAR INT DOUBLE VOID BOOL 

%token <nd> CASE IF ELSE SWITCH WHILE DO FOR GOTO CONTINUE BREAK RETURN

%token <nd> TRUE FALSE

%token <nd> ';' ',' ':' '=' '[' ']' '.' '&' '!' '~' '-' '+' '*' '/' '%' '<' '>' '^' '|' '?' '{' '}' '(' ')'


%nonassoc IF
%nonassoc ELSE


%left	',' //15
%left	ARGS// 仅用来指定优先级
%right	ASSIGN ADD_ASSIGN SUB_ASSIGN MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN OR_ASSIGN XOR_ASSIGN //15
%right	'?' ':' //14
%left	OR_OP//13
%left	AND_OP//12
%left	'|'//11
%left	'^'//10
%left	'&'//9
%left	EQ_OP NEQ_OP//8
%left	GE_OP '>' LE_OP '<'//7
%left	LEFT_OP RIGHT_OP//6
%left	'+' '-'//5
%left	TYPE_CHANGE//4，仅用来指定优先级
%left	'*' '/' '%'//3
%right	'!' '~' //2, ++a, --a
%left	INC_OP DEC_OP//1, a++, a--

%%

Program:		Decls{
					root = create_tree("Program",1,$1);
				}
				;

Decls:			Decls Decl	{$$ = create_tree("Decls",2,$1,$2);}
			|				{$$ = create_tree("Decls",0,yylineno);}
			;

Decl:			VarDecl		{$$ = create_tree("Decl",1,$1);}
			|	TypeDecl	{$$ = create_tree("Decl",1,$1);}
			|	FunDecl		{$$ = create_tree("Decl",1,$1);}
			;

VarDecl:		DataType VarList ';'	{$$ = create_tree("VarDecl",2,$1,$2);}
			;

DataType:		BuildInType		{$$ = create_tree("DataType",1,$1);}
			|	DataType '*'	{$$ = create_tree("DataType",2,$1,$2);}
			|	IDENTIFIER /* typedef */	{$$ = create_tree("DataType",1,$1);}
			;

BuildInType:	INT				{$$ = create_tree("BuildInType",1,$1);}
			|	CHAR			{$$ = create_tree("BuildInType",1,$1);}
			|	VOID			{$$ = create_tree("BuildInType",1,$1);}
			|	DOUBLE			{$$ = create_tree("BuildInType",1,$1);}
			|	BOOL			{$$ = create_tree("BuildInType",1,$1);}
			;

FieldDecls:		FieldDecls FieldDecl	{$$ = create_tree("FieldDecls",2,$1,$2);}
			|							{$$ = create_tree("FieldDecls",0,yylineno);}
			;

FieldDecl:		DataType MemList ';'	{$$ = create_tree("FieldDecl",3,$1,$2,$3);}
			|	';'						{$$ = create_tree("FieldDecl",1,$1);}
			;

MemList:		MemList ',' IDENTIFIER	{$$ = create_tree("MemList",3,$1,$2,$3);}
			|	IDENTIFIER				{$$ = create_tree("MemList",1,$1);}
			;

VarList:		Var ',' VarList			{$$ = create_tree("VarList",3,$1,$2,$3);}
			|	Var						{$$ = create_tree("VarList",1,$1);}
			;

Var:			IDENTIFIER				{$$ = create_tree("Var",1,$1);}
			|	IDENTIFIER ASSIGN Exp	{$$ = create_tree("Var",3,$1,$2,$3);}
			;

TypeDecl:		TYPEDEF DataType IDENTIFIER ';'	{$$ = create_tree("TypeDecl",4,$1,$2,$3,$4);}
			;

FunDecl:		ReturnType IDENTIFIER LPAREN ArgList RPAREN ';'	{
					{$$ = create_tree("FunDecl",6,$1,$2,$3,$4,$5,$6);}
			}
			|	ReturnType IDENTIFIER LPAREN ArgList RPAREN FunBody{
					{$$ = create_tree("FunDecl",6,$1,$2,$3,$4,$5,$6);}
			}
			;

ReturnType:		DataType	{$$ = create_tree("ReturnType",1,$1);}
			|	VOID		{$$ = create_tree("ReturnType",1,$1);}

ArgList:		ArgList_ ',' Arg		{$$ = create_tree("ArgList",3,$1,$2,$3);}
			|	Arg						{$$ = create_tree("ArgList",1,$1);}
			|	VOID					{$$ = create_tree("ArgList",1,$1);}
			|							{$$ = create_tree("ArgList",0,yylineno);}
			;

Arg:			DataType IDENTIFIER		{$$ = create_tree("Arg",2,$1,$2);}
			|	DataType				{$$ = create_tree("Arg",1,$1);}
			;

FunBody:		LBRACE Stms RBRACE		{$$ = create_tree("FunBody",3,$1,$2,$3);}
			;

Stms:			Stms Stm				{$$ = create_tree("Stms",2,$1,$2);}
			|							{$$ = create_tree("Stms",0,yylineno);}
			;

Stm:			Exp ';'					{$$ = create_tree("Stm",2,$1,$2);}
			|	IfStm					{$$ = create_tree("Stm",1,$1);}
			|	ForStm					{$$ = create_tree("Stm",1,$1);}
			|	WhileStm				{$$ = create_tree("Stm",1,$1);}
			|	DoStm					{$$ = create_tree("Stm",1,$1);}
			|	SwitchStm				{$$ = create_tree("Stm",1,$1);}
			|	BreakStm				{$$ = create_tree("Stm",1,$1);}
			|	ContinueStm				{$$ = create_tree("Stm",1,$1);}
			|	ReturnStm				{$$ = create_tree("Stm",1,$1);}
			|	Block					{$$ = create_tree("Stm",1,$1);}
			|	VarDecl					{$$ = create_tree("Stm",1,$1);}
			|	TypeDecl				{$$ = create_tree("Stm",1,$1);}
			|	';'						{$$ = create_tree("Stm",1,$1);}
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
			|	'+' Exp %prec '!'
			|	'-' Exp %prec '!'
				// (int)a
			|	LPAREN DataType RPAREN Exp %prec TYPE_CHANGE
			|	INC_OP Exp %prec '!'
			|	Exp INC_OP %prec DOT
			|	DEC_OP Exp %prec '!'
			|	Exp DEC_OP %prec DOT
			|	'*' Exp %prec '!'
			|	'&' Exp %prec '!'
			|	'!' Exp %prec '!'
			|	'~' Exp %prec '!'
			|	Exp '/' Exp
			|	Exp '*' Exp
			|	Exp '%' Exp
			|	Exp '+' Exp
			|	Exp '-' Exp
			|	Exp LEFT_OP Exp
			|	Exp RIGHT_OP Exp
			|	Exp GE_OP Exp
			|	Exp '>' Exp
			|	Exp LE_OP Exp
			|	Exp '<' Exp
			|	Exp EQ_OP Exp
			|	Exp NEQ_OP Exp
			|	Exp '&' Exp
			|	Exp '^' Exp
			|	Exp '|' Exp
			|	Exp AND_OP Exp
			|	Exp OR_OP Exp
			|	Exp '?' Exp ':' Exp
			|	Exp ASSIGN Exp
			|	Exp MUL_ASSIGN Exp
			|	Exp DIV_ASSIGN Exp
			|	Exp MOD_ASSIGN Exp
			|	Exp ADD_ASSIGN Exp
			|	Exp SUB_ASSIGN Exp
			|	Exp LEFT_ASSIGN Exp
			|	Exp RIGHT_ASSIGN Exp
			|	Exp AND_ASSIGN Exp
			|	Exp XOR_ASSIGN Exp
			|	Exp OR_ASSIGN Exp
			|	LPAREN Exp RPAREN
			|	IDENTIFIER
			|	Constant
			|	Exp	',' Exp
			;

IfStm:			IF LPAREN Exp RPAREN Stm ELSE Stm
			|	IF LPAREN Exp RPAREN Stm
			;

ForStm:			FOR LPAREN Exp ';' Exp ';' Exp RPAREN Stm
			|	FOR LPAREN VarDecl ';' Exp ';' Exp RPAREN Stm
			;

WhileStm:		WHILE LPAREN Exp RPAREN Stm
			;

DoStm:			DO Stm WHILE LPAREN Exp RPAREN ';'
			;

SwitchStm:		SWITCH LPAREN Exp RPAREN LBRACE CaseList RBRACE
			;

CaseList:		CaseList CaseStm
			|
			;

CaseStm:		CASE Exp ':' Stms
			|	DEFAULT ':' Stms
			;

ContinueStm:	CONTINUE ';'
			;

BreakStm:		BREAK
			;

ReturnStm:		RETURN ';'
			|	RETURN Exp ';'
			;

Block:			LBRACE Stms RBRACE
			;

ExpList:		ExpList_ ',' Exp
			|	Exp %prec ARGS
			|
			;

ExpList_:		ExpList_ ',' Exp
			|	Exp %prec ARGS
			;
Constant:		
				CHARACTER
			|	INTEGER
			|	REAL
			|	STRING
			;

%%
