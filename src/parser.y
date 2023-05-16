%{
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int yylex();
int yyerror(char *);

%}
%token ANS
%token <dv> NUMBER
%token <cv> IDENTIFIER
%type <dv> expr
%type <cv> variable

%union
{  

  double dv;  
  char cv;  
}  

%token ADD SUB MUL DLV BXOR MOD BNOT ASSIGN OR BOR AND BAND SHL SHR
%token EQ NEQ LE LT GE GT NOT 
%token QUES COLON

%left ASSIGN
%left ADD SUB
%left MUL DLV MOD 
%left AND OR and or
%left COS SIN TAN LOG PP SS LOR LOL COT
%left '^'
%left '~' '!' 
%right '(' ')' 

%%

%%
int yyerror(char *s)
{
  printf("%s\n", s);
  return 1;
}
void convert(int num ,int mode)
  {
	   if(num/mode==0)
	   {
	    
	   	printf("\t%d",num);return;}
		 else 
		{
		  convert(num/mode,mode);
		  printf("%d",num%mode);
	    }
  }

int main(int argc,char **argv)
{
  	yyparse();
}
