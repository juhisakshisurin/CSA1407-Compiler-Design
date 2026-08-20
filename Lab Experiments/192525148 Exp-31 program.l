%{
#include <stdio.h>
%}

%option noyywrap

%%
auto|break|case|char|const|continue|default|do|double|else|enum|extern|float|for|goto|if|int|long|register|return|short|signed|sizeof|static|struct|switch|typedef|union|unsigned|void|volatile|while { printf("%s : KEYWORD\n", yytext); }
[a-zA-Z_][a-zA-Z0-9_]* { printf("%s : IDENTIFIER\n", yytext); }
[ \t\n]+ ;
. ;
%%

int main()
{
    yylex();
    return 0;
}
