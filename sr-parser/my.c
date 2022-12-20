#include <stdio.h>
#include <string.h>

char input[10], stack[20];

int top = -1;

void push(char a)
{
    stack[++top] = a;
}

void pop()
{
    stack[top--] = '\0';
}

void check()
{
    int c = strlen(stack) - 2;
    
    for (int i = 0; i <= top - 1; i++)
    {
        if (stack[i] == 'i' && stack[i + 1] == 'd')
        {
            pop();
            pop();
            push('E');
            printf("\n%s\t\t%s\t\tREDUCE TO E", stack, input);
        }
    }

    for (int i = 0; i <= top - 2; i++)
    {
        if (stack[i] == 'E' && stack[i + 1] == '+' && stack[i + 2] == 'E')
        {
            pop();
            pop();
            printf("\n%s\t\t%s\t\tREDUCE TO E", stack, input);
        }
    }

    for (int i = 0; i <= top-2; i++)
    {
        if (stack[i] == 'E' && stack[i + 1] == '*' && stack[i + 2] == 'E')
        {
            pop();
            pop();
            printf("\n%s\t\t%s\t\tREDUCE TO E", stack, input);
        }
    }

    for (int i = 0; i <= top-2; i++)
    {
        if (stack[i] == '(' && stack[i + 1] == 'E' && stack[i + 2] == ')')
        {
            pop();
            pop();
            pop();
            push('E');
            printf("\n%s\t\t%s\t\tREDUCE TO E", stack, input);
        }
    }
}

int main()
{

    printf("\nEnter the string to parse:");
    scanf("%s", input);

    push('$');

    for (int i = 0; i < strlen(input); i++)
    {
        char temp = input[i];
        push(input[i]);
        input[i] = ' ';
        if (temp == 'i')
            continue;
        printf("\n%s\t\t%s\t\tSHIFT", stack, input);

        if (temp == '+' || temp == '*' || temp == '(')
            continue;
        check();
    }

    int counter = 0;

    while (top > 1)
    {
        check();

        if (strcmp(stack, "$E") == 0)
            break;
        else
            counter++;

        if (counter > 20)
            break;
    }

    printf("\n%s", stack);

    return 0;
}
