%{
#include <stdio.h>
%}

%option noyywrap

%%
hello       { printf("hi"); }
\n          { printf("\n"); }
.           { ECHO; }
%%

int main()
{
    yylex();
    return 0;
}
