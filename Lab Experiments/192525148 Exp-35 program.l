%{
#include <stdio.h>
%}

%option noyywrap

%%
[0-9]    { printf("It is a digit\n"); }
\n       ;
.        { printf("It is not a digit\n"); }
%%

int main()
{
    printf("Enter a character: ");
    yylex();
    return 0;
}
