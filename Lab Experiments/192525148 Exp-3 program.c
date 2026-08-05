#include <stdio.h>

int main()
{
    FILE *fp;
    char ch, next;

    fp = fopen("input.c", "r");

    if (fp == NULL)
    {
        printf("File not found!\n");
        return 0;
    }

    while ((ch = fgetc(fp)) != EOF)
    {
        // Ignore spaces, tabs and new lines
        if (ch == ' ' || ch == '\t' || ch == '\n')
            continue;

        // Ignore comments
        if (ch == '/')
        {
            next = fgetc(fp);

            // Single-line comment
            if (next == '/')
            {
                while ((ch = fgetc(fp)) != '\n' && ch != EOF);
                continue;
            }

            // Multi-line comment
            else if (next == '*')
            {
                while (1)
                {
                    ch = fgetc(fp);

                    if (ch == '*')
                    {
                        if ((ch = fgetc(fp)) == '/')
                            break;
                    }
                }
                continue;
            }

            else
            {
                putchar(ch);
                ungetc(next, fp);
            }
        }
        else
        {
            putchar(ch);
        }
    }

    fclose(fp);
    return 0;
}
