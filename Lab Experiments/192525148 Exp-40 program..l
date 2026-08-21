%{
#include <stdio.h>
%}

%option noyywrap

%%
int|float|char|void|return|if|else|while {printf("%s : KEYWORD\n",yytext);}
[a-zA-Z_][a-zA-Z0-9_]* {printf("%s : IDENTIFIER\n",yytext);}
[0-9]+ {printf("%s : CONSTANT\n",yytext);}
[+\-*/=<>] {printf("%s : OPERATOR\n",yytext);}
[(]|[)]|[{]|[}]|[,]|[;] {printf("%s : SPECIAL SYMBOL\n",yytext);}
[ \t\n]+ ;
. {printf("%s : UNKNOWN\n",yytext);}
%%

int main()
{
yylex();
return 0;
}
