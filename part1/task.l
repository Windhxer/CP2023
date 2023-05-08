%{
#include <stdlib.h>
#include "y.tab.h"
extern int yyerror(const char *);
%}

%%
[" "; \t]   		{ }  
(0(\.[0-9]+)?)|([1-9][0-9]*(\.[0-9]+)?)     { yylval.dv = strtod(yytext,0);return NUMBER;}  


[-+*/()^%~!=\n]		{return *yytext;}

%%
int yywrap()
{
	return 1;
}