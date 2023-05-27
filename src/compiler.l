
%{
#include "y.tab.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "tree.h"
#include <iostream>
using namespace std;

void Count(void);
void Comment();
int check_type();
int column = 0;//记录此时所在代码的列，从而实现代码定位

%}

%option yylineno

D			[0-9]
L			[a-zA-Z_]
H			[a-fA-F0-9]
E			([Ee][+-]?{D}+)
P           ([Pp][+-]?{D}+)
FS			(f|F|l|L)
IS          ((u|U)|(u|U)?(l|L|ll|LL)|(l|L|ll|LL)(u|U))

%%

"/*"			{ Comment();/*注释,词法接收时仅接纳前半部分,通过Comment函数进行后半部分的处理*/}
"//"[^\n]*      { /* 直接消除 //-comment */ }

"bool"			{ Count(); yylval.nd =createTree("BOOL",0,yylineno); 		return(BOOL);	}
"int"			{ Count(); yylval.nd =createTree("INT",0,yylineno);  		return(INT); }
"char"			{ Count(); yylval.nd =createTree("CHAR",0,yylineno); 		return(CHAR); }
"double"		{ Count(); yylval.nd =createTree("DOUBLE",0,yylineno); 	return(DOUBLE); }
"break"			{ Count(); yylval.nd =createTree("BREAK",0,yylineno); 		return(BREAK); }
"case"			{ Count(); yylval.nd =createTree("CASE",0,yylineno); 		return(CASE); }
"continue"		{ Count(); yylval.nd =createTree("CONTINUE",0,yylineno); 	return(CONTINUE); }
"do"			{ Count(); yylval.nd =createTree("DO",0,yylineno);			return(DO); }
"else"			{ Count(); yylval.nd =createTree("ELSE",0,yylineno);		return(ELSE); }
"for"			{ Count(); yylval.nd =createTree("FOR",0,yylineno);		return(FOR); }
"goto"			{ Count(); yylval.nd =createTree("GOTO",0,yylineno);		return(GOTO); }
"if"			{ Count(); yylval.nd =createTree("IF",0,yylineno);			return(IF); }
"return"		{ Count(); yylval.nd =createTree("RETURN",0,yylineno);		return(RETURN); }
"switch"		{ Count(); yylval.nd =createTree("SWITCH",0,yylineno);		return(SWITCH); }
"void"			{ Count(); yylval.nd =createTree("VOID",0,yylineno);		return(VOID); }
"while"			{ Count(); yylval.nd =createTree("WHILE",0,yylineno);		return(WHILE); }
"true"			{ Count(); yylval.nd =createTree("TRUE",0,yylineno);		return(TRUE); }
"false"			{ Count(); yylval.nd =createTree("FALSE",0,yylineno);		return(FALSE); }

{L}({L}|{D})* 	{Count(); yylval.nd =createTree("IDENTIFIER",0,yylineno);	return(IDENTIFIER);/*IDENTIFIER*/ }

0[xX]{H}+{IS}?	{ Count(); yylval.nd =createTree("CONSTANT_INT",0,yylineno);	return(CONSTANT_INT); /*16进制*/}
0[0-7]*{IS}?	{ Count(); yylval.nd =createTree("CONSTANT_INT",0,yylineno);	return(CONSTANT_INT); /*8进制*/}
[1-9]{D}*{IS}?	{ Count(); yylval.nd =createTree("CONSTANT_INT",0,yylineno);	return(CONSTANT_INT); /*10进制*/}
L?'(\\.|[^\\'\n])+'		{ Count(); return(CONSTANT); }

{D}+{E}{FS}?				{ Count(); yylval.nd =createTree("CONSTANT_DOUBLE",0,yylineno);	return(CONSTANT_DOUBLE); /*浮点数*/}
{D}*"."{D}+{E}?{FS}?		{ Count(); yylval.nd =createTree("CONSTANT_DOUBLE",0,yylineno);	return(CONSTANT_DOUBLE); /*浮点数*/}
{D}+"."{D}*{E}?{FS}?		{ Count(); yylval.nd =createTree("CONSTANT_DOUBLE",0,yylineno);	return(CONSTANT_DOUBLE); /*浮点数*/}
0[xX]{H}+{P}{FS}?			{ Count(); return(CONSTANT); }
0[xX]{H}*"."{H}+{P}?{FS}?   { Count(); return(CONSTANT); }
0[xX]{H}+"."{H}*{P}?{FS}?   { Count(); return(CONSTANT); }


L?\"(\\.|[^\\"\n])*\"	{ Count();  yylval.nd =createTree("STRING_LITERAL",0,yylineno);	return(STRING_LITERAL); /*字符串常量*/}

">>="	{ Count(); yylval.nd =createTree("RIGHT_ASSIGN",0,yylineno);	return(RIGHT_ASSIGN); }
"<<="	{ Count(); yylval.nd =createTree("LEFT_ASSIGN",0,yylineno);	return(LEFT_ASSIGN); }
"+="	{ Count(); yylval.nd =createTree("ADD_ASSIGN",0,yylineno);		return(ADD_ASSIGN); }
"-="	{ Count(); yylval.nd =createTree("SUB_ASSIGN",0,yylineno);		return(SUB_ASSIGN); }
"*="	{ Count(); yylval.nd =createTree("MUL_ASSIGN",0,yylineno);		return(MUL_ASSIGN); }
"/="	{ Count(); yylval.nd =createTree("DIV_ASSIGN",0,yylineno);		return(DIV_ASSIGN); }
"%="	{ Count(); yylval.nd =createTree("MOD_ASSIGN",0,yylineno);		return(MOD_ASSIGN); }
"&="	{ Count(); yylval.nd =createTree("AND_ASSIGN",0,yylineno);		return(AND_ASSIGN); }
"^="	{ Count(); yylval.nd =createTree("XOR_ASSIGN",0,yylineno);		return(XOR_ASSIGN); }
"|="	{ Count(); yylval.nd =createTree("OR_ASSIGN",0,yylineno);		return(OR_ASSIGN); }
">>"	{ Count(); yylval.nd =createTree("RIGHT_OP",0,yylineno);		return(RIGHT_OP); }
"<<"	{ Count(); yylval.nd =createTree("LEFT_OP",0,yylineno);		return(LEFT_OP); }
"++"	{ Count(); yylval.nd =createTree("INC_OP",0,yylineno);			return(INC_OP); }
"--"	{ Count(); yylval.nd =createTree("DEC_OP",0,yylineno);			return(DEC_OP); }
"->"	{ Count(); yylval.nd =createTree("PTR_OP",0,yylineno);			return(PTR_OP); }
"&&"	{ Count(); yylval.nd =createTree("AND_OP",0,yylineno);			return(AND_OP); }
"||"	{ Count(); yylval.nd =createTree("OR_OP",0,yylineno);			return(OR_OP); }
"<="	{ Count(); yylval.nd =createTree("LE_OP",0,yylineno);			return(LE_OP); }
">="	{ Count(); yylval.nd =createTree("GE_OP",0,yylineno);			return(GE_OP); }
"=="	{ Count(); yylval.nd =createTree("EQ_OP",0,yylineno);			return(EQ_OP); }
"!="	{ Count(); yylval.nd =createTree("NE_OP",0,yylineno);			return(NE_OP); }
";"		{ Count(); yylval.nd =createTree(";",0,yylineno);	return(';'); }
","		{ Count(); yylval.nd =createTree(",",0,yylineno);	return(','); }
":"		{ Count(); yylval.nd =createTree(":",0,yylineno);	return(':'); }
"="		{ Count(); yylval.nd =createTree("=",0,yylineno);	return('='); }
"["		{ Count(); yylval.nd =createTree("[",0,yylineno);	return('['); }
"]"		{ Count(); yylval.nd =createTree("]",0,yylineno);	return(']'); }
"."		{ Count(); yylval.nd =createTree(".",0,yylineno);	return('.'); }
"&"		{ Count(); yylval.nd =createTree("&",0,yylineno);	return('&'); }
"!"		{ Count(); yylval.nd =createTree("!",0,yylineno);	return('!'); }
"~"		{ Count(); yylval.nd =createTree("~",0,yylineno);	return('~'); }
"-"		{ Count(); yylval.nd =createTree("-",0,yylineno);	return('-'); }
"+"		{ Count(); yylval.nd =createTree("+",0,yylineno);	return('+'); }
"*"		{ Count(); yylval.nd =createTree("*",0,yylineno);	return('*'); }
"/"		{ Count(); yylval.nd =createTree("/",0,yylineno);	return('/'); }
"%"		{ Count(); yylval.nd =createTree("%",0,yylineno);	return('%'); }
"<"		{ Count(); yylval.nd =createTree("<",0,yylineno);	return('<'); }
">"		{ Count(); yylval.nd =createTree(">",0,yylineno);	return('>'); }
"^"		{ Count(); yylval.nd =createTree("^",0,yylineno);	return('^'); }
"|"		{ Count(); yylval.nd =createTree("|",0,yylineno);	return('|'); }
"?"		{ Count(); yylval.nd =createTree("?",0,yylineno);	return('?'); }
"{"		{ Count(); yylval.nd =createTree("{",0,yylineno);	return('{'); }
"}"		{ Count(); yylval.nd =createTree("}",0,yylineno);	return('}'); }
"("		{ Count(); yylval.nd =createTree("(",0,yylineno);	return('('); }
")"		{ Count(); yylval.nd =createTree(")",0,yylineno);	return(')'); }

[\t\v\n\f ]		{ Count();}
.			{ /* Add code to complain about unmatched characters */ }

%%


int yywrap() {
	return 1;
}


void Comment() {
	column = 0;
	char c, prev = 0;
	
	while (cin >> c)      /* (EOF maps to 0) */
	{
		if (c == '/' && prev == '*')
			return;
		prev = c;
	}
	printf("unterminated comment");
}



void Count(void)
{
	int i;

	for (i = 0; yytext[i] != '\0'; i++)
		if (yytext[i] == '\n')
			column = 0;
		else if (yytext[i] == '\t')
			column += 4 - (column % 4);
		else
			column++;
	ECHO;
}
