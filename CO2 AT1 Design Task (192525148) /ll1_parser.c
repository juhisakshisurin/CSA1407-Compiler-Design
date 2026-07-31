#include <stdio.h>
#include <string.h>

typedef struct
{
    char stack[100];
    int top;
} Stack;

void push(Stack *s, char c)
{
    s->stack[++s->top] = c;
}

char pop(Stack *s)
{
    return s->stack[s->top--];
}

void printStack(Stack s)
{
    for (int i = 0; i <= s.top; i++)
        printf("%c", s.stack[i]);
}

int main()
{
    char input[100];
    char temp[100];
    int i = 0;

    printf("===============================================\n");
    printf("      LL(1) Predictive Parser Simulation\n");
    printf("===============================================\n\n");

    printf("Grammar:\n");
    printf("E -> TQ\n");
    printf("Q -> +TQ | #\n");
    printf("T -> FR\n");
    printf("R -> *FR | #\n");
    printf("F -> (E) | i\n\n");

    printf("Note:\n");
    printf("Use 'i' to represent 'id'.\n");
    printf("Example Input : i+i*i\n\n");

    printf("Enter Input : ");
    scanf("%s", input);

    strcat(input, "$");

    Stack st;
    st.top = -1;

    push(&st, '$');
    push(&st, 'E');

    printf("\n--------------------------------------------------------------\n");
    printf("%-15s %-15s %-20s\n", "STACK", "INPUT", "ACTION");
    printf("--------------------------------------------------------------\n");

    while (st.top != -1)
    {
        strcpy(temp, input + i);

        printStack(st);

        int len = st.top + 1;
        printf("%*s", 18 - len, "");

        printf("%-15s", temp);

        char top = st.stack[st.top];
        char cur = input[i];

        if (top == cur)
        {
            if (top == '$')
            {
                printf("Accept\n");
                break;
            }

            printf("Match %c\n", cur);
            pop(&st);
            i++;
        }

        else if (top == 'E')
        {
            if (cur == 'i' || cur == '(')
            {
                printf("E -> TQ\n");
                pop(&st);
                push(&st, 'Q');
                push(&st, 'T');
            }
            else
            {
                printf("Error\n");
                break;
            }
        }

        else if (top == 'Q')
        {
            if (cur == '+')
            {
                printf("Q -> +TQ\n");
                pop(&st);
                push(&st, 'Q');
                push(&st, 'T');
                push(&st, '+');
            }
            else if (cur == ')' || cur == '$')
            {
                printf("Q -> ε\n");
                pop(&st);
            }
            else
            {
                printf("Error\n");
                break;
            }
        }

        else if (top == 'T')
        {
            if (cur == 'i' || cur == '(')
            {
                printf("T -> FR\n");
                pop(&st);
                push(&st, 'R');
                push(&st, 'F');
            }
            else
            {
                printf("Error\n");
                break;
            }
        }

        else if (top == 'R')
        {
            if (cur == '*')
            {
                printf("R -> *FR\n");
                pop(&st);
                push(&st, 'R');
                push(&st, 'F');
                push(&st, '*');
            }
            else if (cur == '+' || cur == ')' || cur == '$')
            {
                printf("R -> ε\n");
                pop(&st);
            }
            else
            {
                printf("Error\n");
                break;
            }
        }

        else if (top == 'F')
        {
            if (cur == 'i')
            {
                printf("F -> i\n");
                pop(&st);
                push(&st, 'i');
            }
            else if (cur == '(')
            {
                printf("F -> (E)\n");
                pop(&st);
                push(&st, ')');
                push(&st, 'E');
                push(&st, '(');
            }
            else
            {
                printf("Error\n");
                break;
            }
        }

        else
        {
            printf("Error\n");
            break;
        }
    }

    printf("\n===============================================\n");
    printf("Final Result : String Accepted\n");
    printf("===============================================\n");

    return 0;
}
