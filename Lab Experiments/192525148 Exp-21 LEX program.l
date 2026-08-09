%{
#include<stdio.h>

int words = 0;
int lines = 0;
int spaces = 0;
int special = 0;
%}

%%

[ \t]              { spaces++; }

\n                 { lines++; }

[A-Za-z0-9]+       { words++; }

[^A-Za-z0-9 \t\n]  { special++; }

%%

int yywrap()
{
    return 1;
}

int main()
{
    printf("Enter the text (Press Ctrl+Z then Enter to stop):\n");

    yylex();

    printf("\nWords              : %d", words);
    printf("\nLines              : %d", lines);
    printf("\nSpaces             : %d", spaces);
    printf("\nSpecial Characters : %d\n", special);

    return 0;
}
