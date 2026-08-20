%{
#include <stdio.h>

int positive = 0;
int negative = 0;
%}

%option noyywrap

%%
[0-9]+          { positive++; }
-[0-9]+         { negative++; }
[ \t\n]+        ;
.               ;
%%

int main()
{
    yylex();

    printf("Positive numbers = %d\n", positive);
    printf("Negative numbers = %d\n", negative);

    return 0;
}
