#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>


struct Grammar
{
  char non_terminal;
  char productions[10];

  char first[10];
  int first_count;

  char follow[10];
  int follow_count;

  bool epislon;
};

struct Grammar *grammar[10];

void free_grammar(int num_productions)
{
  for (int i = 0; i < num_productions; i++)
  {
    free(grammar[i]);
  }
}

void find_first(int num_productions)
{
  for (int i = num_productions - 1; i > -1; i--)
  {
    // Lock exists to handle '|' in the grammar
    bool lock = true;
    
    for (int j = 0; j < strlen(grammar[i] -> productions); j++)
    {

      if (grammar[i] -> productions[j] == '|'){
        lock = true;
        continue;
      }

      if (lock)
      {
        // Case 1: if the first production is lower
        if (islower(grammar[i] -> productions[j]) || !isalpha(grammar[i] -> productions[j]))
        {
          if (grammar[i] -> productions[j] != '|')
          grammar[i] -> first[grammar[i] -> first_count++] = grammar[i] -> productions[j];
        }

        // Case 2: if the first production is a non-terminal
        // Search for the non-terminal in the grammar list
        // Simply append it's first to the currents first.
        else if (isupper(grammar[i] -> productions[j]))
        {
          int k = 0;
          for (k = 0; k < num_productions; k++)
          {
            if (grammar[k] -> non_terminal == grammar[i] -> productions[j])
              break;
          }

          for (int l = 0; l < grammar[k] -> first_count; l++)
          {
            grammar[i] -> first[grammar[i] -> first_count++] = grammar[k] -> first[l];
          }
        }
        
        lock = false;
      }
    }
  }
}

void find_follow(int num_productions)
{
  int i, j;

  grammar[0] -> follow[grammar[0] -> follow_count++] = '$';

  for (int a = 0; a < num_productions; a++)
  {
    for (i = 0; i < num_productions; i++)
    {
      for (j = 0; j < strlen(grammar[i] -> productions); j++)
      {
        if (grammar[a] -> non_terminal == grammar[i] -> productions[j])
        {
          // Case 1: It's the last term, so follow is same as follow of start symbol
          if (j == strlen(grammar[i] -> productions) - 1)
          {
            int b =0;
            for (b = 0; b < num_productions; b++)
            {
              if (grammar[b] -> non_terminal == grammar[b] -> non_terminal)
                break;
            }

            for (int c = 0; c < grammar[b] -> follow_count; c++)
            {
              grammar[a] -> follow[grammar[a] -> follow_count++] = grammar[b] -> follow[c];
            }
          }

          // Case 2: terminal next to the non-terminal
          else if (islower(grammar[i] -> productions[j+1]) || !(isalpha(grammar[i] -> productions[j+1])))
          {
            grammar[a] -> follow[grammar[a] -> follow_count++] = grammar[i] -> productions[j+1];
          }
          // Case 3.1: Non-terminal next to non-terminal,
          // Case 3.1: This non-terminal may have epsilon in it
          else if (isupper(grammar[i] -> productions[j+1]))
          {
            int b =0;
            for (b = 0; b < num_productions; b++)
            {
              if (grammar[b] -> non_terminal == grammar[i] -> productions[j+1])
                break;
            }

            for (int g = 0; g < grammar[b] -> first_count; g++)
            {
              grammar[a] -> follow[grammar[a] -> follow_count++] = grammar[g] -> first[g];
            }
          }
          break;
        }
      }
    }
  }
}

void display(int num_productions)
{
  for (int i = 0; i < num_productions;i++)
  {
    printf("\nFirst of %c: {", grammar[i] -> non_terminal);
    for (int j = 0; j < grammar[i] -> first_count; j++)
    {
      printf(" %c  ", grammar[i] -> first[j]);
    }
    printf("\b}");
  }

  printf("\n");
  for (int i = 0; i < num_productions;i++)
  {
    printf("\nFollow of %c: ", grammar[i] -> non_terminal);
    for (int j = 0; j < grammar[i] -> follow_count; j++)
    {
      printf("%c  ", grammar[i] -> follow[j]);
    }
  }
}

int main()
{
  int num_productions = 0;

  printf("\nEnter the no. of productions:");
  scanf("%d", &num_productions);

  FILE *ip = fopen("input.txt", "r");

  char non_terminal, prods[10];

  int i = 0;

  while (true)
  {
    if (feof(ip))
      break;
    fscanf(ip, "%c %s ", &non_terminal, prods);


    grammar[i] = (struct Grammar*)malloc(sizeof(struct Grammar));
    grammar[i] -> epislon = false;
    for (int k = 0; k < strlen(prods); k++)
    {
      if (prods[k] == '#')
        grammar[i] -> epislon = true;
    }

    grammar[i] -> non_terminal = non_terminal;
    strcpy(grammar[i] -> productions, prods);
    grammar[i] -> first_count = 0;
    grammar[i++] -> follow_count = 0;
  }

  find_first(num_productions);
  find_follow(num_productions);

  display(num_productions);

  fclose(ip);
  free_grammar(num_productions);

  return 0;
}