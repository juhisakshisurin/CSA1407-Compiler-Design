%{
#include <stdio.h>

int count = 0;
%}

%option noyywrap

%%
"//".*              { count++; }
"/*"([^*]|\*+[^*/])*"*/"  { count++; }
.|\n                { ECHO; }
%%

int main()
{
    yyout = fopen("output.c", "w");

    if (yyout == NULL)
    {
        printf("Cannot create output file");
        return 1;
    }

    yylex();

    fclose(yyout);

    printf("Number of comments = %d\n", count);
    printf("Comments removed successfully.\n");

    return 0;
}
