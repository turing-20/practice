%{
#include <stdio.h>
int yylex();

int n = 0;

void yyerror(char *s) {
  fprintf(stderr, "yyerror %s %d\n", s, n);
}


%}

%union {
  char *key;
  int num;
  char *varname;
};

%type <num> expression
// %type <key> operation direction
%token <varname> VARNAME
%token <num> NUMBER
%token <key> ADD SUBTRACT MULTIPLY DIVIDE LEFT RIGHT UP DOWN ASSIGN TO VAR IS VALUE IN EOL COMMA 

%%

program: expression program | expression;

expression: ADD LEFT { printf("parser chla\n"); };


%%
// operation: ADD {printf("add\n"); $$ = 1;} | MULTIPLY | SUBTRACT | DIVIDE;
// direction: LEFT {$$ = 2;} | RIGHT | UP | DOWN;
// val: VALUE IN pos | NUMBER;
// pos: POSITION | VARNAME;

int main() {
    yyparse();
    return 0;
}