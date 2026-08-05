#include <stdio.h>

int main()
{
    char exp[100];
    int i = 0;

    printf("Enter an expression: ");
    fgets(exp, sizeof(exp), stdin);

    printf("\nArithmetic Operators Found:\n");

    while (exp[i] != '\0')
    {
        switch (exp[i])
        {
            case '+':
                printf("+ : Addition Operator\n");
                break;

            case '-':
                printf("- : Subtraction Operator\n");
                break;

            case '*':
                printf("* : Multiplication Operator\n");
                break;

            case '/':
                printf("/ : Division Operator\n");
                break;
        }
        i++;
    }

    return 0;
}
