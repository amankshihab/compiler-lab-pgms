%{
    #include <stdio.h>
    #include <stdlib.h>
%}

%token num
%left '+''-'
%left '*''/'
%right '^'

%%

S           :           E           { printf("\nResult: %d", $$); }
            ;
E           :           E'+'E       { $$ = $1 + $3; }
            |           '('E')'     { $$ = $2; }
            |           num         { $$ = $1; }
            ;

%%

int yyerror(char *msg)
{
    printf("\nError in parsing");
}

int main()
{
    printf("\nEnter the expression:");
    yyparse();
}