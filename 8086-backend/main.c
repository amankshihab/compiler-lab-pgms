#include <stdio.h>
#include <string.h>

int main()
{
    FILE *ip = fopen("input.txt", "r");

    char op[10], arg1[10], arg2[10], res[10];

    char operator[4];

    while (1)
    {
        if (feof(ip))
            break;

        fscanf(ip, "%s %s %s %s ", op, arg1, arg2, res);

        switch(op[0])
        {
            case '+':   strcpy(operator, "ADD"); break;
            case '-':   strcpy(operator, "SUB"); break;
            case '*':   strcpy(operator, "MUL"); break;
            case '/':   strcpy(operator, "DIV"); break;
        }

        printf("\nMOV R0, %s", arg1);
        printf("\n%s R0, %s", operator, arg2);
        printf("\nMOV %s, R0\n", res);
    }
}