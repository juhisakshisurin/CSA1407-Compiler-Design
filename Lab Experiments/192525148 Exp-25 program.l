%{
#include <stdio.h>
%}

%option noyywrap

%%
[A-Z]+    { printf("%s\n", yytext); }
.|\n      ;
%%

int main()
{
    printf("Capital words are:\n");
    yylex();
    return 0;
}
