%{
#define Pi 3.14159265358979
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int yylex();
int yyerror(char *);
double last=0;
int i;
int flag=1;
%}
%token <dv> NUMBER
%type <dv> expr

%union
{  
  double dv;  
  char cv;  
}  
%token '+' '-' '*' '/' '^' '%' '`' '~' '!' '='

%left '='
%left '+' '-'
%left '*' '/' '%' 
%left '^'
%left '~' '!' 
%right '(' ')' 

%%
program:
        program expr '\n' { 
			    if(flag)
			    {
			     printf( "%g\n" , $2 );
			     last = $2;
			    }
			    else 
      			       {printf("");}
			    flag=1;
			  }
	   |
        ;

expr    :
        NUMBER        { $$ = $1; }
        | expr '+' expr  { $$ = $1 + $3; }
        | expr '-' expr  { $$ = $1 - $3; }
        | expr '*' expr  { $$ = $1 * $3; }
        | expr '/' expr  { $$ = $1 / $3; }
        | expr '^' expr  { $$ = pow($1, $3);}
	    | '~' expr	 
        { 
			$$=~(int)$2;				     
		}
        | '!' expr   
        {
		    if(!(int)$2)
			  	printf("true\n");
			else
				printf("false\n");
			flag=0;
		}
	    | expr '%' expr  { $$ = (int)$1 % (int)$3; }
	    | '-' expr 	  { $$ = -$2; }
      	| '(' expr ')'  { $$ = $2; }
        ;
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
