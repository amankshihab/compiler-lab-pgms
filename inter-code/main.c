#include <stdio.h>
#include <string.h>
#include <ctype.h>

char infix[20], postfix[20];
int post_i = 0;

char stack[10];
int top = -1;

char tac_stack[10];
int tac_top = -1;

int pre(char c)
{
	switch(c) 
	{
		case '^': return 5;
		case '*': return 4;
		case '/': return 4;
		case '+': return 3;
		case '-': return 3;
		case '$': return 2; 
	}
}

void infix_to_postfix()
{
	stack[++top] = '$';
	stack[++top] = '(';
	
	for (int i = 0; i < strlen(infix); i++)
	{
		if (isalpha(infix[i]))
		{
			postfix[post_i++] = infix[i];
		}
		else
		{
			// Three cases:
			// 1. The top of the stack has lesser priority or a '(' is encountered
			
			if (pre(stack[top]) < pre(infix[i]) || infix[i] == '(')
			{
				stack[++top] = infix[i];
			}

			// 2. When ')' is encountered, simply pop until we see '('

			else if (infix[i] == ')')
			{
				while (stack[top] != '(')
				{
					postfix[post_i++] = stack[top--];
				}
				top--;
			}
			
			// 3. When the top of stack has greater priority

			else
			{
				while (pre(stack[top]) >= pre(infix[i]) && stack[top] != '$')
				{
					postfix[post_i++] = stack[top--];
				}

				stack[++top] = infix[i];
			}
		}
	}

	// while (stack[top] != '$')
	// {
	// 	postfix[post_i++] = stack[top--];
	// }

	postfix[post_i++] = '\0';
}

void print_tac()
{
	char res = 'A';

	printf("\n------------------------------------------");
	printf("\n| Operator  |  arg1  |  arg2  |  Result  |");
	printf("\n------------------------------------------");
	for (int i = 0; i < strlen(postfix); i++)
	{
		if (isalpha(postfix[i]))
		{
			tac_stack[++tac_top] = postfix[i];
		}
		else
		{
			char x = tac_stack[tac_top--];
			char y = tac_stack[tac_top--];

			tac_stack[++tac_top] = res;

			printf("\n|    %c      |    %c   |    %c   |     %c    |", postfix[i], y, x, res++);
		}
	}
	printf("\n------------------------------------------\n");
}

int main()
{
	char temp[20];

	printf("\nEnter the infix expression:");
	scanf("%s", infix);

	int len = strlen(infix);

	infix[len] = ')';
	infix[len+1] = '\0';

	infix_to_postfix();

	printf("Postfix: %s", postfix);

	print_tac();

	return 0;
}