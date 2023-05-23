
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

"bool"			{ Count(); yylval.nd =create_tree("BOOL",0,yylineno); 		return(BOOL);	}
"int"			{ Count(); yylval.nd =create_tree("INT",0,yylineno);  		return(INT); }
"char"			{ Count(); yylval.nd =create_tree("CHAR",0,yylineno); 		return(CHAR); }
"double"		{ Count(); yylval.nd =create_tree("DOUBLE",0,yylineno); 	return(DOUBLE); }
"break"			{ Count(); yylval.nd =create_tree("BREAK",0,yylineno); 		return(BREAK); }
"case"			{ Count(); yylval.nd =create_tree("CASE",0,yylineno); 		return(CASE); }
"continue"		{ Count(); yylval.nd =create_tree("CONTINUE",0,yylineno); 	return(CONTINUE); }
"do"			{ Count(); yylval.nd =create_tree("DO",0,yylineno);			return(DO); }
"else"			{ Count(); yylval.nd =create_tree("ELSE",0,yylineno);		return(ELSE); }
"for"			{ Count(); yylval.nd =create_tree("FOR",0,yylineno);		return(FOR); }
"goto"			{ Count(); yylval.nd =create_tree("GOTO",0,yylineno);		return(GOTO); }
"if"			{ Count(); yylval.nd =create_tree("IF",0,yylineno);			return(IF); }
"return"		{ Count(); yylval.nd =create_tree("RETURN",0,yylineno);		return(RETURN); }
"switch"		{ Count(); yylval.nd =create_tree("SWITCH",0,yylineno);		return(SWITCH); }
"void"			{ Count(); yylval.nd =create_tree("VOID",0,yylineno);		return(VOID); }
"while"			{ Count(); yylval.nd =create_tree("WHILE",0,yylineno);		return(WHILE); }
"true"			{ Count(); yylval.nd =create_tree("TRUE",0,yylineno);		return(TRUE); }
"false"			{ Count(); yylval.nd =create_tree("FALSE",0,yylineno);		return(FALSE); }

{L}({L}|{D})* 	{Count(); yylval.nd =create_tree("IDENTIFIER",0,yylineno);	return(IDENTIFIER);/*IDENTIFIER*/ }

0[xX]{H}+{IS}?	{ Count(); yylval.nd =create_tree("CONSTANT_INT",0,yylineno);	return(CONSTANT_INT); /*16进制*/}
0[0-7]*{IS}?	{ Count(); yylval.nd =create_tree("CONSTANT_INT",0,yylineno);	return(CONSTANT_INT); /*8进制*/}
[1-9]{D}*{IS}?	{ Count(); yylval.nd =create_tree("CONSTANT_INT",0,yylineno);	return(CONSTANT_INT); /*10进制*/}
L?'(\\.|[^\\'\n])+'		{ Count(); return(CONSTANT); }

{D}+{E}{FS}?				{ Count(); yylval.nd =create_tree("CONSTANT_DOUBLE",0,yylineno);	return(CONSTANT_DOUBLE); /*浮点数*/}
{D}*"."{D}+{E}?{FS}?		{ Count(); yylval.nd =create_tree("CONSTANT_DOUBLE",0,yylineno);	return(CONSTANT_DOUBLE); /*浮点数*/}
{D}+"."{D}*{E}?{FS}?		{ Count(); yylval.nd =create_tree("CONSTANT_DOUBLE",0,yylineno);	return(CONSTANT_DOUBLE); /*浮点数*/}
0[xX]{H}+{P}{FS}?			{ Count(); return(CONSTANT); }
0[xX]{H}*"."{H}+{P}?{FS}?   { Count(); return(CONSTANT); }
0[xX]{H}+"."{H}*{P}?{FS}?   { Count(); return(CONSTANT); }


L?\"(\\.|[^\\"\n])*\"	{ Count();  yylval.nd =create_tree("STRING_LITERAL",0,yylineno);	return(STRING_LITERAL); /*字符串常量*/}

">>="	{ Count(); yylval.nd =create_tree("RIGHT_ASSIGN",0,yylineno);	return(RIGHT_ASSIGN); }
"<<="	{ Count(); yylval.nd =create_tree("LEFT_ASSIGN",0,yylineno);	return(LEFT_ASSIGN); }
"+="	{ Count(); yylval.nd =create_tree("ADD_ASSIGN",0,yylineno);		return(ADD_ASSIGN); }
"-="	{ Count(); yylval.nd =create_tree("SUB_ASSIGN",0,yylineno);		return(SUB_ASSIGN); }
"*="	{ Count(); yylval.nd =create_tree("MUL_ASSIGN",0,yylineno);		return(MUL_ASSIGN); }
"/="	{ Count(); yylval.nd =create_tree("DIV_ASSIGN",0,yylineno);		return(DIV_ASSIGN); }
"%="	{ Count(); yylval.nd =create_tree("MOD_ASSIGN",0,yylineno);		return(MOD_ASSIGN); }
"&="	{ Count(); yylval.nd =create_tree("AND_ASSIGN",0,yylineno);		return(AND_ASSIGN); }
"^="	{ Count(); yylval.nd =create_tree("XOR_ASSIGN",0,yylineno);		return(XOR_ASSIGN); }
"|="	{ Count(); yylval.nd =create_tree("OR_ASSIGN",0,yylineno);		return(OR_ASSIGN); }
">>"	{ Count(); yylval.nd =create_tree("RIGHT_OP",0,yylineno);		return(RIGHT_OP); }
"<<"	{ Count(); yylval.nd =create_tree("LEFT_OP",0,yylineno);		return(LEFT_OP); }
"++"	{ Count(); yylval.nd =create_tree("INC_OP",0,yylineno);			return(INC_OP); }
"--"	{ Count(); yylval.nd =create_tree("DEC_OP",0,yylineno);			return(DEC_OP); }
"->"	{ Count(); yylval.nd =create_tree("PTR_OP",0,yylineno);			return(PTR_OP); }
"&&"	{ Count(); yylval.nd =create_tree("AND_OP",0,yylineno);			return(AND_OP); }
"||"	{ Count(); yylval.nd =create_tree("OR_OP",0,yylineno);			return(OR_OP); }
"<="	{ Count(); yylval.nd =create_tree("LE_OP",0,yylineno);			return(LE_OP); }
">="	{ Count(); yylval.nd =create_tree("GE_OP",0,yylineno);			return(GE_OP); }
"=="	{ Count(); yylval.nd =create_tree("EQ_OP",0,yylineno);			return(EQ_OP); }
"!="	{ Count(); yylval.nd =create_tree("NE_OP",0,yylineno);			return(NE_OP); }
";"		{ Count(); yylval.nd =create_tree(";",0,yylineno);	return(';'); }
","		{ Count(); yylval.nd =create_tree(",",0,yylineno);	return(','); }
":"		{ Count(); yylval.nd =create_tree(":",0,yylineno);	return(':'); }
"="		{ Count(); yylval.nd =create_tree("=",0,yylineno);	return('='); }
"["		{ Count(); yylval.nd =create_tree("[",0,yylineno);	return('['); }
"]"		{ Count(); yylval.nd =create_tree("]",0,yylineno);	return(']'); }
"."		{ Count(); yylval.nd =create_tree(".",0,yylineno);	return('.'); }
"&"		{ Count(); yylval.nd =create_tree("&",0,yylineno);	return('&'); }
"!"		{ Count(); yylval.nd =create_tree("!",0,yylineno);	return('!'); }
"~"		{ Count(); yylval.nd =create_tree("~",0,yylineno);	return('~'); }
"-"		{ Count(); yylval.nd =create_tree("-",0,yylineno);	return('-'); }
"+"		{ Count(); yylval.nd =create_tree("+",0,yylineno);	return('+'); }
"*"		{ Count(); yylval.nd =create_tree("*",0,yylineno);	return('*'); }
"/"		{ Count(); yylval.nd =create_tree("/",0,yylineno);	return('/'); }
"%"		{ Count(); yylval.nd =create_tree("%",0,yylineno);	return('%'); }
"<"		{ Count(); yylval.nd =create_tree("<",0,yylineno);	return('<'); }
">"		{ Count(); yylval.nd =create_tree(">",0,yylineno);	return('>'); }
"^"		{ Count(); yylval.nd =create_tree("^",0,yylineno);	return('^'); }
"|"		{ Count(); yylval.nd =create_tree("|",0,yylineno);	return('|'); }
"?"		{ Count(); yylval.nd =create_tree("?",0,yylineno);	return('?'); }
"{"		{ Count(); yylval.nd =create_tree("{",0,yylineno);	return('{'); }
"}"		{ Count(); yylval.nd =create_tree("}",0,yylineno);	return('}'); }
"("		{ Count(); yylval.nd =create_tree("(",0,yylineno);	return('('); }
")"		{ Count(); yylval.nd =create_tree(")",0,yylineno);	return(')'); }

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
