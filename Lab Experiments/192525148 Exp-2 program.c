#include <stdio.h>
#include <string.h>

int main()
{
    char str[200];

    printf("Enter a line:\n");
    fgets(str, sizeof(str), stdin);

    // Check for single-line comment
    if(str[0]=='/' && str[1]=='/')
    {
        printf("Single-line Comment\n");
    }

    // Check for multi-line comment
    else if(str[0]=='/' && str[1]=='*')
    {
        int len = strlen(str);

        if(len >= 4 && str[len-3]=='*' && str[len-2]=='/')
            printf("Multi-line Comment\n");
        else
            printf("Invalid Multi-line Comment\n");
    }

    else
    {
        printf("Not a Comment\n");
    }

    return 0;
}
