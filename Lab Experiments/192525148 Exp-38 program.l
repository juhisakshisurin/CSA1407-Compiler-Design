%{
#include <stdio.h>
#include <string.h>

int max = 0;
%}

%option noyywrap

%%
[A-Za-z]+ {
    if (yyleng > max)
        max = yyleng;
}

[ \t\n]+ ;

. ;
%%

int main()
{
    printf("Enter a sentence: ");
    yylex();

    printf("Length of longest word = %d\n", max);

    return 0;
}
