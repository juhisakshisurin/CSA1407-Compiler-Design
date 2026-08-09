%{
#include<stdio.h>
%}

%%

int|char|float|double|if|else|while|for|return|void {
    printf("Keyword\n");
}

[a-zA-Z_][a-zA-Z0-9_]* {
    printf("Identifier\n");
}

\n {
    return 0;
}

. {
    printf("Invalid Input\n");
}

%%

int yywrap()
{
    return 1;
}

int main()
{
    printf("Enter a word: ");
    yylex();
    return 0;
}
