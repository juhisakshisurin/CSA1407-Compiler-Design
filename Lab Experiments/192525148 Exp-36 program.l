%{
#include <stdio.h>

int a, b;
char op;
%}

%option noyywrap

%%
[0-9]+     { a = atoi(yytext); }
"+"        { op = '+'; }
"-"        { op = '-'; }
"*"        { op = '*'; }
"/"        { op = '/'; }
\n         ;
.          ;
%%

int main()
{
    printf("Enter first number: ");
    scanf("%d", &a);

    printf("Enter operator (+,-,*,/): ");
    scanf(" %c", &op);

    printf("Enter second number: ");
    scanf("%d", &b);

    switch(op)
    {
        case '+': printf("Result = %d\n", a + b); break;
        case '-': printf("Result = %d\n", a - b); break;
        case '*': printf("Result = %d\n", a * b); break;
        case '/':
            if(b != 0)
                printf("Result = %d\n", a / b);
            else
                printf("Cannot divide by zero\n");
            break;
        default:
            printf("Invalid operator\n");
    }

    return 0;
}
