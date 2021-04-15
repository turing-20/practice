%{
#include <stdio.h>
#include<stdlib.h>
#include<string.h>
#include "assgn.h"
int yylex();
State *state;
/* state = (State *) malloc(SIZE_OF_BOARD * sizeof(State)); */
char* varnames[4][4][1000];
int ind[4][4];

int n = 0;

void yyerror(char *s) {
  fprintf(stderr, "yyerror %s %d\n", s, n);
}

void add_varname(char *name, int x, int y);
void find_pos(char *name, int *pos);


%}

%union {
  int key;
  int num;
  char *varname;
};

%start program

%type <num> expression
%type <num> val x y
%type <key> opn dir

%token <varname> VARNAME
%token <num> NUMBER
%token <key> ADD SUBTRACT MULTIPLY DIVIDE LEFT RIGHT UP DOWN ASSIGN TO VAR IS VALUE IN EOL COMMA 

%%

program:  expression program
|         /* NULL */
;

expression: opn dir EOL { move(state, $2, $1); print_board(state); }
|           ASSIGN val TO x COMMA y EOL { print_board(state); assign(state, $2, $4, $6); print_board(state); }
|           ASSIGN val TO VARNAME EOL { int pos[2]; find_pos($4, pos);  assign(state, $2, pos[0], pos[1]); print_board(state); };
|           val EOL
|           VAR VARNAME IS x COMMA y EOL { char *tok = strtok($2, " "); printf("parser exp varname %s\n", tok); add_varname(tok, $4, $6); }
;

val:  VALUE IN VARNAME { 
  int pos[2];
  find_pos($3, pos);
  $$ = state->board[pos[0]][pos[1]];
  printf("val in var => %d\n", $$);
}
|     VALUE IN x COMMA y { $$ = state->board[$3][$5]; printf("val => %d\n", $$); }
|     VARNAME { 
  printf("parser val %s\n", $1);
  int pos[2];
  find_pos($1, pos);
  $$ = state->board[pos[0]][pos[1]];
  printf("val in var => %d\n", $$);
}
|     NUMBER;
x: NUMBER;
y: NUMBER;

opn:  ADD { printf("parser opn %d\n", $1); $$ = 1; } 
|     SUBTRACT { $$ = 2; }
|     MULTIPLY { $$ = 3; } 
|     DIVIDE { $$ = 4; }
;
dir:  LEFT { $$ = 1; }
|     RIGHT { $$ = 2; }
|     UP { $$ = 3; }
|     DOWN { $$ = 4; }
;
%%

void add_varname(char *name, int x, int y) {
  printf("add_varname %s || %d %d\n", name, x, y);
  printf(" add _ varname %d\n", ind[x][y]);
  varnames[x][y][ind[x][y]] = (char *)malloc(strlen(name) * sizeof(char));
  strcpy(varnames[x][y][ind[x][y]++], name);
}

void find_pos(char *name, int *pos) {
  for(int i = 0; i < 4; i++) {
    for(int j = 0; j < 4; j++) {
      for(int k = 0; k < ind[i][j]; k++) {
        if(strcmp(name, varnames[i][j][k]) == 0) {
          pos[0] = i;
          pos[1] = j;
          return;
        }
      }
    }
  }
}

int main() {
  state = (State *) malloc(SIZE_OF_BOARD * sizeof(State));
  /* varnames = (char *) malloc(16 * sizeof(char *)); */
  for(int i = 0; i < 4; i++) {
    for(int j = 0; j < 4; j++) {
      ind[i][j] = 0;
    }
  }
  init(state);
  print_board(state);
  yyparse();
  return 0;
}