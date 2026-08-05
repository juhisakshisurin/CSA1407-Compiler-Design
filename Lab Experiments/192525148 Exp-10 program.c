#include <stdio.h>

int main()
{
    printf("Given Grammar:\n");
    printf("S -> iEtS | iEtSeS | a\n");
    printf("E -> b\n\n");

    printf("Grammar after Left Factoring:\n");
    printf("S  -> iEtSS' | a\n");
    printf("S' -> eS | epsilon\n");
    printf("E  -> b\n");

    return 0;
}
