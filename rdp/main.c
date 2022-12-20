// E -> iE'
// E' -> iE'|e

#include <stdio.h>

char ip[20];
int i = 0;

int Edash(int i)
{
    if (ip[i] == 'i')
    {
        return Edash(++i);
    }
    else if (ip[i] == 'e')
    {
        return 1;
    }
    return 0;
}

int E(int i)
{
    if (ip[i] == 'i')
    {
        return Edash(++i);
    }
    return 0;
}

int main()
{
    printf("\nEnter the string:");
    scanf("%s", ip);
    
    if (E(0))
        printf("\nParsed");
    else
        printf("\nNot parsed");

    return 0;
}