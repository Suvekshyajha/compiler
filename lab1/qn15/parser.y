%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
void yyerror(const char *s);
%}

/* Tokens */
%token ID

/* Operator precedence */
%left '+'
%left '*'

%start S

%%

S:
    E
    {
        printf("\nParsing Successful!\n");
        printf("Valid Arithmetic Expression.\n");
    }
    ;

E:
      E '+' T
    | T
    ;

T:
      T '*' F
    | F
    ;

F:
      '(' E ')'
    | ID
    ;

%%

void yyerror(const char *s)
{
    printf("\nParsing Failed: %s\n", s);
}

int main()
{
    printf("====================================\n");
    printf("Lab No.: 1\n");
    printf("Name: Suvekshya Jha\n");
    printf("Roll No.: 80117729\n");
    printf("====================================\n");

    printf("\nEnter an arithmetic expression:\n");

    yyparse();

    return 0;
}