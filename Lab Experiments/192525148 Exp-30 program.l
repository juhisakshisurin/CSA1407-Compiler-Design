%{
#include <stdio.h>

int count = 0;
%}

%option noyywrap

%%
[bcdfghjklmnpqrstvwxyzBCDFGHJKLMNPQRSTVWXYZ]    { count++; }
\n                                               ;
.                                                ;
%%

int main()
{
    printf("Enter a sentence: ");
    yylex();

    printf("Number of consonants = %d\n", count);

    return 0;
}
