#include <stdio.h>
#include <string.h>

int main()
{
    char expr[50];
    int i = 0, temp = 1;

    printf("Enter the expression: ");
    scanf("%s", expr);

    printf("\nThree Address Code:\n");

    while (expr[i] != '\0')
    {
        if (expr[i] == '+' || expr[i] == '-' ||
            expr[i] == '*' || expr[i] == '/')
        {
            printf("t%d = %c %c %c\n",
                   temp,
                   expr[i - 1],
                   expr[i],
                   expr[i + 1]);

            expr[i + 1] = '0' + temp;
            temp++;
        }
        i++;
    }

    printf("Result = t%d\n", temp - 1);

    return 0;
}
