/* 这个文件用来单独运行词法分析（后面写到语法分析再合并一下）*/
%{
#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;
extern "C" int yywrap();
%}

%option outfile="./src/lexer_only.cpp"

%%
"//"(.*)                                  { /* 忽略单行注释 */ }
"/*"([^*]|"**"[^/])*"*/"                  { /* 忽略多行注释 */ }

","							{fprintf(yyout, "COMMA ");}
"..."							{fprintf(yyout, "ELLIPSES ");}
"."							{fprintf(yyout, "DOT ");}
";"							{fprintf(yyout, "SEMI ");}
"("							{fprintf(yyout, "LPAREN ");}
")"							{fprintf(yyout, "RPAREN ");}
"["							{fprintf(yyout, "LBRACKET ");}
"]"							{fprintf(yyout, "RBRACKET ");}
"{"							{fprintf(yyout, "LBRACE ");}
"}"							{fprintf(yyout, "RBRACE ");}

"<<"							{fprintf(yyout, "SHL ");}
">>"							{fprintf(yyout, "SHR ");}
"=="							{fprintf(yyout, "EQ ");}
">="							{fprintf(yyout, "GE ");}
">"							{fprintf(yyout, "GT ");}
"<="							{fprintf(yyout, "LE ");}
"<"							{fprintf(yyout, "LT ");}
"!="							{fprintf(yyout, "NEQ ");}
"!"							{fprintf(yyout, "NOT ");}
"="							{fprintf(yyout, "ASSIGN ");}
"&&"							{fprintf(yyout, "AND ");}
"&"							{fprintf(yyout, "BAND ");}
"||"							{fprintf(yyout, "OR ");}
"|"							{fprintf(yyout, "BOR ");}
"->"							{fprintf(yyout, "ARW ");}
"^"							{fprintf(yyout, "BXOR ");}
"~"							{fprintf(yyout, "BNOT ");}
"+"							{fprintf(yyout, "ADD ");}
"-"							{fprintf(yyout, "SUB ");}
"*"							{fprintf(yyout, "MUL ");}
"/"							{fprintf(yyout, "DIV ");}
"%"							{fprintf(yyout, "MOD ");}
"?"							{fprintf(yyout, "QUES ");}
":"							{fprintf(yyout, "COLON ");}

"struct"						{fprintf(yyout, "STRUCT ");}
"if"							{fprintf(yyout, "IF ");}
"else"						{fprintf(yyout, "ELSE ");}
"for"							{fprintf(yyout, "FOR ");}
"while"						{fprintf(yyout, "WHILE ");}
"do"							{fprintf(yyout, "DO ");}
"switch"						{fprintf(yyout, "SWITCH ");}
"case"						{fprintf(yyout, "CASE ");}
"default"						{fprintf(yyout, "DEFAULT ");}
"continue"						{fprintf(yyout, "CONTINUE ");}
"return"						{fprintf(yyout, "RETURN ");}
"true"						{fprintf(yyout, "TRUE ");}
"false"						{fprintf(yyout, "FALSE ");}
"break"						{fprintf(yyout, "BREAK ");}
"sizeof"						{fprintf(yyout, "SIZEOF ");}
"bool"						{fprintf(yyout, "BOOL ");}
"short"						{fprintf(yyout, "SHORT ");}
"int"							{fprintf(yyout, "INT ");}
"long"						{fprintf(yyout, "LONG ");}
"char"						{fprintf(yyout, "CHAR ");}
"float"						{fprintf(yyout, "FLOAT ");}
"double"						{fprintf(yyout, "DOUBLE ");}
"void"						{fprintf(yyout, "VOID ");}

[a-zA-Z_][a-zA-Z0-9_]*                    {fprintf(yyout, "IDENTIFIER ");}
[0-9]+\.[0-9]+                            {fprintf(yyout, "REAL ");}
[0-9]+                                    {fprintf(yyout, "INTEGER ");}
.                                         {ECHO;}

%%
int main(int argc, char **argv)
{
  if (argc == 3) {
      FILE* fileIn;
      FILE* fileOut;
      fileIn = fopen(argv[1], "r");
      if(fileIn) {
            yyin = fileIn;
      }
      fileOut = fopen(argv[2], "w");
      if  (fileOut) {
            yyout = fileOut;
      }
  }
  yylex();
  yywrap();
  return 0;
}
int yywrap()
{
	return 1;
}
