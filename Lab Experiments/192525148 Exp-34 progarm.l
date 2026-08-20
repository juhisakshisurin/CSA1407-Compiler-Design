%{
#include <stdio.h>
%}

%option noyywrap

%%
[0-9][0-9]"/"[0-9][0-9]"/"[0-9][0-9][0-9][0-9] { printf("Valid DOB\n"); }
[0-9/]+ { printf("Invalid DOB\n"); }
[ \t\n]+ ;
. ;
%%

int main()
{
    printf("Enter DOB (DD/MM/YYYY): ");
    yylex();
    return 0;
}
