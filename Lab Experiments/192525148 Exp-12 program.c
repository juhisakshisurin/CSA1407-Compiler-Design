#include <stdio.h>
#include <string.h>

char input[100];
int i = 0;
int error = 0;

void E();
void EP();
void T();
void TP();
void F();

void E()
{
    T();
    EP();
}

void EP()
{
    if (input[i] == '+')
    {
        i++;
        T();
        EP();
    }
}

void T()
{
    F();
    TP();
}

void TP()
{
    if (input[i] == '*')
    {
        i++;
        F();
        TP();
    }
}

void F()
{
    if (error)
        return;

    if (input[i] == '(')
    {
        i++;
        E();

        if (input[i] == ')')
            i++;
        else
            error = 1;
    }
    else if (input[i] == 'i' && input[i + 1] == 'd')
    {
        i += 2;
    }
    else
    {
        error = 1;
    }
}

int main()
{
    printf("Grammar:\n");
    printf("E -> TE'\n");
    printf("E' -> +TE' | epsilon\n");
    printf("T -> FT'\n");
    printf("T' -> *FT' | epsilon\n");
    printf("F -> (E) | id\n\n");

    printf("Enter the input string: ");
    scanf("%s", input);

    E();

    if (error == 0 && input[i] == '\0')
        printf("String Accepted\n");
    else
        printf("String Rejected\n");

    return 0;
}
