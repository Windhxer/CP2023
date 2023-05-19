/* 半成品状态 */
%{
#include <iostream>
#include "AST.hpp"
#include "parser.hpp"

using namespace std;
using namespace AST;

extern int yyerror(const char *);
extern "C" int yywrap() {return 1;}

char handleEscape(char escape) {
	switch(ch){
		case 'a': return '\a';
		case 'b': return '\b';
		case 'f': return '\f';
		case 'n': return '\n';
		case 'r': return '\r';
		case 't': return '\t';
		case 'v': return '\v';
		case '\\': return '\\';
		case '\'': return '\'';
		case '\"': return '\"';
	}
}
%}

%option never-interactive /* 不使用标准输入输出 */
%option outfile="lexer.cpp"

ESCAPE "\\"([abfnrtv\'\"\\])
%%

","														{return COMMA;}
"..."													{return ELLIPSES;}
"."														{return DOT;}
";"														{return SEMI;}
"("														{return LPAREN;}
")"														{return RPAREN;}
"["														{return LBRACKET;}
"]"														{return RBRACKET;}
"{"														{return LBRACE;}
"}"														{return RBRACE;}
"\""													{return DQUOTE;}
"\'"													{return SQUOTE; }
"<<="													{return SHLEQ;}
"<<"													{return SHL;}
">>="													{return SHREQ;}
">>"													{return SHR;}
"=="													{return EQ;}
">="													{return GE;}
">"														{return GT;}
"<="													{return LE;}
"<"														{return LT;}
"!="													{return NEQ;}
"!"														{return NOT;}
"="														{return ASSIGN;}
"&&"													{return AND;}
"&="													{return BANDEQ;}
"&"														{return BAND;}
"||"													{return OR;}
"|="													{return BOREQ;}
"|"														{return BOR;}
"->"													{return ARW;}
"^="													{return BXOREQ;}
"^"														{return BXOR;}
"~"														{return BNOT;}
"++"													{return DADD;}
"+="													{return ADDEQ;}
"+"														{return ADD;}
"--"													{return DSUB;}
"-="													{return SUBEQ;}
"-"														{return SUB;}
"*="													{return MULEQ;}
"*"														{return MUL;}
"/="													{return DIVEQ;}
"/"														{return DIV;}
"%="													{return MODEQ;}
"%"														{return MOD;}
"?"														{return QUES;}
":"														{return COLON;}
"struct"												{return STRUCT;}
"union"													{return UNION;}
"typedef"												{return TYPEDEF;}
"const"													{return CONST;}
"enum"													{return ENUM;}
"array"													{return ARRAY;}
"if"													{return IF;}
"else"													{return ELSE;}
"for"													{return FOR;}
"while"													{return WHILE;}
"do"													{return DO;}
"switch"												{return SWITCH;}
"case"													{return CASE;}
"default"												{return DEFAULT;}
"continue"												{return CONTINUE;}
"return"												{return RETURN;}
"break"													{return BREAK; }
"sizeof"												{return SIZEOF; }
"short"													{return SHORT; }
"int"													{return INT; }
"long"													{return LONG; }
"char"													{return CHAR; }
"float"													{return FLOAT; }
"double"												{return DOUBLE; }
"void"													{return VOID; }

"//"(.*)												{/* 单行注释 */}
"/*"([^*]|"**"[^/])*"*/"								{/* 多行注释 */}
"\'"([^\\\'])"\'"										{/* 非转义字符的单个字符 */
															Value value;
															value.VALUR_CHAR = yytext[1];

													 		yylval.node = new Node(NODE_TYPE_CHAR, "", value);
															return CHARACTER;
														}
"\'"{ESCAPE}"\'"										{/* 单个转义字符 */
															Value value;
															value.VALUR_CHAR = handleEscape(yytext[2]);

															yylval.node = new Node(NODE_TYPE_CHAR, "", value);
															return CHARACTER;
														}
"\""({ESCAPE}|[^"\\])*"\""								{/* 字符串 */
															string* temp = new string("");
															Value value;
															value.VALUR_STRING = temp;

															for (int i = 1; i < yylength - 1; i++) {
																if (yytext[i] == '\\'){
																	i++;
																	*temp += handleEscape(yytext[i]);
																}else{
																	*temp += handleEscape(yytext[i]);
																}
															}
															yylval.node = new Node(NODE_TYPE_CONST_STRING, "", value);
															return STRING;
														}
[a-zA-Z_][a-zA-Z0-9_]*									{/* 标识符 */
															Value value;

															yylval.node = new Node(NODE_TYPE_IDENTIFIER, yytext, value);
															return IDENTIFIER;
														}

[0-9]+\.[0-9]+											{/* 实数 */
															Value value;
															value.VALUE_FLOAT = stof(yytext);

															yylval.node = new Node(NODE_TYPE_CONST_FLOAT, "", value);
															return REAL;
														}
[0-9]+													{/* 整数 */
															Value value;
															value.VALUE_INTEGER = stoi(yytext);

															yylval.node = new Node(NODE_TYPE_CONST_INTEGER, "", value);
															return INTEGER;
														}
%%