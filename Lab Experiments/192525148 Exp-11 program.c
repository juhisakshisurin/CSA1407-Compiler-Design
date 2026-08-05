#include <stdio.h>
#include <string.h>

struct Symbol
{
    char name[20];
    char type[20];
};

struct Symbol table[100];
int count = 0;

void insert()
{
    printf("Enter Identifier Name: ");
    scanf("%s", table[count].name);

    printf("Enter Data Type: ");
    scanf("%s", table[count].type);

    count++;
    printf("Symbol Inserted Successfully!\n");
}

void display()
{
    int i;

    if(count == 0)
    {
        printf("Symbol Table is Empty!\n");
        return;
    }

    printf("\n---------------------------------\n");
    printf("Identifier\tData Type\n");
    printf("---------------------------------\n");

    for(i = 0; i < count; i++)
    {
        printf("%s\t\t%s\n", table[i].name, table[i].type);
    }
}

void search()
{
    char key[20];
    int i, found = 0;

    printf("Enter Identifier to Search: ");
    scanf("%s", key);

    for(i = 0; i < count; i++)
    {
        if(strcmp(table[i].name, key) == 0)
        {
            printf("Symbol Found!\n");
            printf("Identifier: %s\n", table[i].name);
            printf("Data Type : %s\n", table[i].type);
            found = 1;
            break;
        }
    }

    if(found == 0)
        printf("Symbol Not Found!\n");
}

void deleteSymbol()
{
    char key[20];
    int i, j, found = 0;

    printf("Enter Identifier to Delete: ");
    scanf("%s", key);

    for(i = 0; i < count; i++)
    {
        if(strcmp(table[i].name, key) == 0)
        {
            for(j = i; j < count - 1; j++)
            {
                table[j] = table[j + 1];
            }

            count--;
            found = 1;
            printf("Symbol Deleted Successfully!\n");
            break;
        }
    }

    if(found == 0)
        printf("Symbol Not Found!\n");
}

int main()
{
    int choice;

    while(1)
    {
        printf("\n===== SYMBOL TABLE =====\n");
        printf("1. Insert\n");
        printf("2. Display\n");
        printf("3. Search\n");
        printf("4. Delete\n");
        printf("5. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                insert();
                break;

            case 2:
                display();
                break;

            case 3:
                search();
                break;

            case 4:
                deleteSymbol();
                break;

            case 5:
                return 0;

            default:
                printf("Invalid Choice!\n");
        }
    }
}
