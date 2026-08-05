#include <stdio.h>
#include <string.h>
#include <ctype.h>

char *keywords[] = {
    "int","float","char","if","else","for","while",
    "return","void","double","break","continue"
};

int isKeyword(char str[])
{
    int n = sizeof(keywords)/sizeof(keywords[0]);

    for(int i=0;i<n;i++)
    {
        if(strcmp(str,keywords[i])==0)
            return 1;
    }
    return 0;
}

int main()
{
    FILE *fp;
    char ch, token[100];
    int i;

    fp = fopen("input.c","r");

    if(fp==NULL)
    {
        printf("File not found");
        return 0;
    }

    while((ch=fgetc(fp))!=EOF)
    {
        // Ignore spaces
        if(isspace(ch))
            continue;

        // Ignore single line comment
        if(ch=='/')
        {
            char next=fgetc(fp);

            if(next=='/')
            {
                while((ch=fgetc(fp))!='\n' && ch!=EOF);
                continue;
            }

            // Ignore multi line comment
            else if(next=='*')
            {
                while(1)
                {
                    ch=fgetc(fp);
                    if(ch=='*')
                    {
                        if((ch=fgetc(fp))=='/')
                            break;
                    }
                }
                continue;
            }

            else
            {
                printf("Operator : /\n");
                ungetc(next,fp);
                continue;
            }
        }

        // Identifier or Keyword
        if(isalpha(ch) || ch=='_')
        {
            i=0;
            token[i++]=ch;

            while((ch=fgetc(fp))!=EOF && (isalnum(ch)||ch=='_'))
            {
                token[i++]=ch;
            }

            token[i]='\0';

            if(ch!=EOF)
                ungetc(ch,fp);

            if(isKeyword(token))
                printf("Keyword    : %s\n",token);
            else
                printf("Identifier : %s\n",token);
        }

        // Constant
        else if(isdigit(ch))
        {
            i=0;
            token[i++]=ch;

            while((ch=fgetc(fp))!=EOF && isdigit(ch))
            {
                token[i++]=ch;
            }

            token[i]='\0';

            if(ch!=EOF)
                ungetc(ch,fp);

            printf("Constant   : %s\n",token);
        }

        // Operators
        else if(ch=='+'||ch=='-'||ch=='*'||ch=='='||
                ch=='<'||ch=='>'||ch=='%')
        {
            printf("Operator   : %c\n",ch);
        }
    }

    fclose(fp);

    return 0;
}
