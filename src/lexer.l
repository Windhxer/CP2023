// 半成品状态
%{
#include <stdlib.h>
#include "y.tab.h"
extern int yyerror(const char *);
%}

%%


%%
int yywrap()
{
	return 1;
}