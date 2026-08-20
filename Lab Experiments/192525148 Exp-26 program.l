%{
#include <stdio.h>
%}

%option noyywrap

%%
[A-Za-z0-9._%+-]+@[A-Za-z0-9.-]+\.[A-Za-z]+    printf("Valid Email Address\n");
[A-Za-z0-9._%+-]+                                printf("Invalid Email Address\n");
\n                                              ;
.                                               ;
%%

int main()
{
    printf("Enter email: ");
    yylex();
    return 0;
}
