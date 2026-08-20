%{
#include <stdio.h>

int line = 1;
%}

%%
^       { printf("%d: ", line); }
\n      { printf("\n"); line++; }
.       { ECHO; }
%%

int main()
{
    yylex();
    return 0;
}
