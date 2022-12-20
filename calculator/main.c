#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct Constant
{
    char variable;
    char value;
};

struct Constant *const_list[10];

char expressions[10][20];

int main()
{
    FILE *ip = fopen("input.txt", "r");

    char operator, arg1, arg2, result;
    char res[10];

    int const_count = 0, i = 0;

    printf("\nThe unoptimized code is :\n");
    printf("<OP>   <ARG1>   <ARG2>   <RES>");

    while (1)
    {
       if (feof(ip))
        break;

        fscanf(ip, "%c %c %c %c ", &operator, &arg1, &arg2, &result);

        if (operator == '=')
        {
            const_list[const_count] = (struct Constant*)malloc(sizeof(struct Constant));

            const_list[const_count] -> variable = result;
            const_list[const_count++] -> value = arg1;
        }
        else
        {   
            int idx = 0;
            res[idx++] = operator;
            res[idx++] = arg1;
            res[idx++] = arg2;
            res[idx++] = result;
            res[idx++] = '\0';

            strcpy(expressions[i++], res);

            printf("\n %c       %c        %c        %c", operator, arg1, arg2, result);
        }
    }

    for (int j = 0; j < i; j++)
    {
        for (int k = 0; k < strlen(expressions[j]); k++)
        {
            for (int l = 0; l < const_count; l++)
            {
                if (expressions[j][k] == const_list[l] -> variable)
                {
                    expressions[j][k] = const_list[l] -> value;
                }
            }
        }
    }

    for(int a = 0; a < const_count; a++)
    {
        free(const_list[a]);
    }

    printf("\n\nThe optimized code is :\n");
    printf("<OP>   <ARG1>   <ARG2>   <RES>");

    for (int a = 0; a < i; a++)
    {
        printf("\n %c       %c        %c        %c", expressions[a][0], expressions[a][1], expressions[a][2], expressions[a][3]);
    }

    return 0;
}