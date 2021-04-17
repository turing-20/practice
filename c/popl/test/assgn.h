#ifndef ASSGN_H
#define ASSGN_H

#define SIZE_OF_BOARD 4

typedef struct {
    int board[SIZE_OF_BOARD][SIZE_OF_BOARD];
} State;


// State *state;
void init(State *state);
void print_board(State *state);
void pack(State *state, int *dir);
int operation(int opn, int x);
void doOpns(State *state, int *dir, int opn);
void move(State *state, int d, int opn);
void assign(State *state, int val, int x, int y);


#endif
