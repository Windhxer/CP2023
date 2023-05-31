%{
#include <iostream>
#include <stdio.h>
#include "parser.hpp"
#include "tree.hpp"
using namespace std;
extern "C" int yywrap() {return 1;}

void count(void);
void comment();
int column = 0;

%}

%option yylineno
%option outfile="lexer.cpp"

D			[0-9]
L			[a-zA-Z_]
H			[a-fA-F0-9]
E			([Ee][+-]?{D}+)
P           ([Pp][+-]?{D}+)
FS			(f|F|l|L)
IS          ((u|U)|(u|U)?(l|L|ll|LL)|(l|L|ll|LL)(u|U))
%%

"/*"			{ comment();/*注释*/}
"//"[^\n]*      { /* consume //-comment */ }

"bool"			{ count(); yylval.tN =new treeNode("BOOL",0,yylineno); 		return(BOOL);	}
"int"			{ count(); yylval.tN =new treeNode("INT",0,yylineno);  		return(INT); }
"char"			{ count(); yylval.tN =new treeNode("CHAR",0,yylineno); 		return(CHAR); }
"double"		{ count(); yylval.tN =new treeNode("DOUBLE",0,yylineno); 	return(DOUBLE); }
"break"			{ count(); yylval.tN =new treeNode("BREAK",0,yylineno); 		return(BREAK); }
"case"			{ count(); yylval.tN =new treeNode("CASE",0,yylineno); 		return(CASE); }
"continue"		{ count(); yylval.tN =new treeNode("CONTINUE",0,yylineno); 	return(CONTINUE); }
"do"			{ count(); yylval.tN =new treeNode("DO",0,yylineno);			return(DO); }
"else"			{ count(); yylval.tN =new treeNode("ELSE",0,yylineno);		return(ELSE); }
"for"			{ count(); yylval.tN =new treeNode("FOR",0,yylineno);		return(FOR); }
"goto"			{ count(); yylval.tN =new treeNode("GOTO",0,yylineno);		return(GOTO); }
"if"			{ count(); yylval.tN =new treeNode("IF",0,yylineno);			return(IF); }
"return"		{ count(); yylval.tN =new treeNode("RETURN",0,yylineno);		return(RETURN); }
"switch"		{ count(); yylval.tN =new treeNode("SWITCH",0,yylineno);		return(SWITCH); }
"void"			{ count(); yylval.tN =new treeNode("VOID",0,yylineno);		return(VOID); }
"while"			{ count(); yylval.tN =new treeNode("WHILE",0,yylineno);		return(WHILE); }
"true"			{ count(); yylval.tN =new treeNode("TRUE",0,yylineno);		return(TRUE); }
"false"			{ count(); yylval.tN =new treeNode("FALSE",0,yylineno);		return(FALSE); }

{L}({L}|{D})* 	{count(); yylval.tN =new treeNode("IDENTIFIER",0,yylineno);	return(IDENTIFIER);/*IDENTIFIER*/ }

0[xX]{H}+{IS}?	{ count(); yylval.tN =new treeNode("CONSTANT_INT",0,yylineno);	return(CONSTANT_INT); /*16进制*/}
0[0-7]*{IS}?	{ count(); yylval.tN =new treeNode("CONSTANT_INT",0,yylineno);	return(CONSTANT_INT); /*8进制*/}
[1-9]{D}*{IS}?	{ count(); yylval.tN =new treeNode("CONSTANT_INT",0,yylineno);	return(CONSTANT_INT); /*10进制*/}

L?'(\\.|[^\\'\n])+'		{ count(); return(CONSTANT); }

{D}+{E}{FS}?				{ count(); yylval.tN =new treeNode("CONSTANT_DOUBLE",0,yylineno);	return(CONSTANT_DOUBLE); /*浮点数*/}
{D}*"."{D}+{E}?{FS}?		{ count(); yylval.tN =new treeNode("CONSTANT_DOUBLE",0,yylineno);	return(CONSTANT_DOUBLE); /*浮点数*/}
{D}+"."{D}*{E}?{FS}?		{ count(); yylval.tN =new treeNode("CONSTANT_DOUBLE",0,yylineno);	return(CONSTANT_DOUBLE); /*浮点数*/}
0[xX]{H}+{P}{FS}?			{ count(); return(CONSTANT); }
0[xX]{H}*"."{H}+{P}?{FS}?   { count(); return(CONSTANT); }
0[xX]{H}+"."{H}*{P}?{FS}?   { count(); return(CONSTANT); }


L?\"(\\.|[^\\"\n])*\"	{ count();  yylval.tN =new treeNode("STRING_LITERAL",0,yylineno);	return(STRING_LITERAL); /*字符串常量*/}

">>="	{ count(); yylval.tN =new treeNode("RIGHT_ASSIGN",0,yylineno);	return(RIGHT_ASSIGN); }
"<<="	{ count(); yylval.tN =new treeNode("LEFT_ASSIGN",0,yylineno);	return(LEFT_ASSIGN); }
"+="	{ count(); yylval.tN =new treeNode("ADD_ASSIGN",0,yylineno);		return(ADD_ASSIGN); }
"-="	{ count(); yylval.tN =new treeNode("SUB_ASSIGN",0,yylineno);		return(SUB_ASSIGN); }
"*="	{ count(); yylval.tN =new treeNode("MUL_ASSIGN",0,yylineno);		return(MUL_ASSIGN); }
"/="	{ count(); yylval.tN =new treeNode("DIV_ASSIGN",0,yylineno);		return(DIV_ASSIGN); }
"%="	{ count(); yylval.tN =new treeNode("MOD_ASSIGN",0,yylineno);		return(MOD_ASSIGN); }
"&="	{ count(); yylval.tN =new treeNode("AND_ASSIGN",0,yylineno);		return(AND_ASSIGN); }
"^="	{ count(); yylval.tN =new treeNode("XOR_ASSIGN",0,yylineno);		return(XOR_ASSIGN); }
"|="	{ count(); yylval.tN =new treeNode("OR_ASSIGN",0,yylineno);		return(OR_ASSIGN); }
">>"	{ count(); yylval.tN =new treeNode("RIGHT_OP",0,yylineno);		return(RIGHT_OP); }
"<<"	{ count(); yylval.tN =new treeNode("LEFT_OP",0,yylineno);		return(LEFT_OP); }
"++"	{ count(); yylval.tN =new treeNode("INC_OP",0,yylineno);			return(INC_OP); }
"--"	{ count(); yylval.tN =new treeNode("DEC_OP",0,yylineno);			return(DEC_OP); }
"->"	{ count(); yylval.tN =new treeNode("PTR_OP",0,yylineno);			return(PTR_OP); }
"&&"	{ count(); yylval.tN =new treeNode("AND_OP",0,yylineno);			return(AND_OP); }
"||"	{ count(); yylval.tN =new treeNode("OR_OP",0,yylineno);			return(OR_OP); }
"<="	{ count(); yylval.tN =new treeNode("LE_OP",0,yylineno);			return(LE_OP); }
">="	{ count(); yylval.tN =new treeNode("GE_OP",0,yylineno);			return(GE_OP); }
"=="	{ count(); yylval.tN =new treeNode("EQ_OP",0,yylineno);			return(EQ_OP); }
"!="	{ count(); yylval.tN =new treeNode("NE_OP",0,yylineno);			return(NE_OP); }
";"		{ count(); yylval.tN =new treeNode(";",0,yylineno);	return(';'); }
","		{ count(); yylval.tN =new treeNode(",",0,yylineno);	return(','); }
":"		{ count(); yylval.tN =new treeNode(":",0,yylineno);	return(':'); }
"="		{ count(); yylval.tN =new treeNode("=",0,yylineno);	return('='); }
"["		{ count(); yylval.tN =new treeNode("[",0,yylineno);	return('['); }
"]"		{ count(); yylval.tN =new treeNode("]",0,yylineno);	return(']'); }
"."		{ count(); yylval.tN =new treeNode(".",0,yylineno);	return('.'); }
"&"		{ count(); yylval.tN =new treeNode("&",0,yylineno);	return('&'); }
"!"		{ count(); yylval.tN =new treeNode("!",0,yylineno);	return('!'); }
"~"		{ count(); yylval.tN =new treeNode("~",0,yylineno);	return('~'); }
"-"		{ count(); yylval.tN =new treeNode("-",0,yylineno);	return('-'); }
"+"		{ count(); yylval.tN =new treeNode("+",0,yylineno);	return('+'); }
"*"		{ count(); yylval.tN =new treeNode("*",0,yylineno);	return('*'); }
"/"		{ count(); yylval.tN =new treeNode("/",0,yylineno);	return('/'); }
"%"		{ count(); yylval.tN =new treeNode("%",0,yylineno);	return('%'); }
"<"		{ count(); yylval.tN =new treeNode("<",0,yylineno);	return('<'); }
">"		{ count(); yylval.tN =new treeNode(">",0,yylineno);	return('>'); }
"^"		{ count(); yylval.tN =new treeNode("^",0,yylineno);	return('^'); }
"|"		{ count(); yylval.tN =new treeNode("|",0,yylineno);	return('|'); }
"?"		{ count(); yylval.tN =new treeNode("?",0,yylineno);	return('?'); }
"{"		{ count(); yylval.tN =new treeNode("{",0,yylineno);	return('{'); }
"}"		{ count(); yylval.tN =new treeNode("}",0,yylineno);	return('}'); }
"("		{ count(); yylval.tN =new treeNode("(",0,yylineno);	return('('); }
")"		{ count(); yylval.tN =new treeNode(")",0,yylineno);	return(')'); }

[\t\v\n\f ]		{ count();}
.			{ /* Add code to complain about unmatched characters */ }

%%
void comment() {
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

void count(void)
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