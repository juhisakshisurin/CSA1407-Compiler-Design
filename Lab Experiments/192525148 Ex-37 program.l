%{
#include <stdio.h>

int count = 0;
%}

%option noyywrap

%%
hello       { count++; }
\n          ;
.           ;
%%

int main()
{
    printf("Enter a sentence:\n");
    yylex();

    printf("Frequency of hello = %d\n", count);

    return 0;
}
