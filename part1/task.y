%{
#define Pi 3.14159265358979
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int yylex();
int yyerror(char *);

%}


%%

%%
int yyerror(char *s)
{
  printf("%s\n", s);
  return 1;
}

int main(int argc,char **argv)
{
  	yyparse();
}
