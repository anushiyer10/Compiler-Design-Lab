%{
#include <ctype.h> 
#include <stdio.h>
#include <stdlib.h>
%}

%token digit
%token id // Token for identifiers (variables)

%%

S: E { printf("\n\n"); }

E: E '+' T { printf("+"); } 
 | E '-' T { printf("-"); } 
 | T 
 ; 

T: T '*' P { printf("*"); } 
 | T '/' P { printf("/"); } 
 | P 
 ; 

P: P '^' F { printf("^"); } 
 | F 
 ;

F: '(' E ')' 
 | id { printf("%c", $1); } // Print identifier (variable)
 | digit { printf("%d", $1); }
 ;

%%

int main() {
    printf("Enter infix expression: ");
    yyparse();
    return 0;
}

int yyerror(const char *msg) {
    fprintf(stderr, "Parsing Error: %s\n", msg);
    return 1;
}
