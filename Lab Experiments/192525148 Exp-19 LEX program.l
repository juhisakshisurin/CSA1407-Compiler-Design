%{
#include<stdio.h>

int words = 0;
int chars = 0;
int lines = 0;
%}

%%

"//".*                     ;
"/*"([^*]|\*+[^*/])*\*+"/" ;

[ \t]+                     ;
\n                         { lines++; }

[A-Za-z0-9_]+              { words++; chars += yyleng; }

.                          { chars++; }

%%

int yywrap()
{
    return 1;
}

int main()
{
    yyin = fopen("sample.c","r");

    if(yyin == NULL)
    {
        printf("Cannot open file\n");
        return 0;
    }

    yylex();

    printf("\nCharacters = %d\n", chars);
    printf("Words = %d\n", words);
    printf("Lines = %d\n", lines);

    fclose(yyin);

    return 0;
}
