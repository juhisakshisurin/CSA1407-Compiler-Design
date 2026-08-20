%{
#include <stdio.h>
%}

%option noyywrap

%%
"https://"[a-zA-Z0-9./]+    { printf("Valid URL\n"); }
"http://"[a-zA-Z0-9./]+     { printf("Valid URL\n"); }
[a-zA-Z0-9.]+               { printf("Invalid URL\n"); }
[ \t\n]+                    ;
.                           ;
%%

int main()
{
    yylex();
    return 0;
}
