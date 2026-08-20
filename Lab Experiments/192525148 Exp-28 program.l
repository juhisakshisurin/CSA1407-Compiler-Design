%{
#include <stdio.h>
%}

%option noyywrap

%%
[6-9][0-9]{9}    { printf("Valid Mobile Number\n"); }
[0-9]+           { printf("Invalid Mobile Number\n"); }
.                { printf("Invalid Mobile Number\n"); }
\n               ;
%%

int main()
{
    printf("Enter mobile number: ");
    yylex();
    return 0;
}
