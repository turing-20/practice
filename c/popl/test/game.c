#include<stdio.h>
#include<stdlib.h>
#include "assgn.h"

void init(State *state) {
    for (int i = 0; i < SIZE_OF_BOARD; i++)
    {
        for (int j = 0; j < SIZE_OF_BOARD; j++)
        {
            state->board[i][j] = 0;
        }
    }
}

void print_board(State *state) {
    for (int i = 0; i < SIZE_OF_BOARD; i++)
    {
        printf("---------------------\n");
        for (int j = 0; j < SIZE_OF_BOARD; j++)
        {
            if(state->board[i][j]) printf("|%4d", state->board[i][j]);
            else printf("|    ");
        }
        printf("|\n");
    }
    printf("---------------------\n");
}

void pack(State *state, int *dir) {
    if(dir[0] + dir[1] < 0) {
        for (int i = 0; i < SIZE_OF_BOARD; i++) {
            for (int j = 0; j < SIZE_OF_BOARD; j++) {
                if(state->board[i][j]) {
                    int y = j, x = i;
                    while(x + dir[0] >= 0 && x + dir[0] < SIZE_OF_BOARD && y + dir[1] >= 0 && y + dir[1] < SIZE_OF_BOARD && !state->board[x + dir[0]][y + dir[1]]) {
                        state->board[x + dir[0]][y + dir[1]] = state->board[x][y];
                        state->board[x][y] = 0;
                        x += dir[0];
                        y += dir[1];
                    }
                }
            }
        }
    }
    else {
        for (int i = SIZE_OF_BOARD - 1; i >= 0; i--) {
            for (int j = SIZE_OF_BOARD - 1; j >= 0; j--) {
                if(state->board[i][j]) {
                    int y = j, x = i;
                    while(x + dir[0] >= 0 && x + dir[0] < SIZE_OF_BOARD && y + dir[1] >= 0 && y + dir[1] < SIZE_OF_BOARD && !state->board[x + dir[0]][y + dir[1]]) {
                        state->board[x + dir[0]][y + dir[1]] = state->board[x][y];
                        state->board[x][y] = 0;
                        x += dir[0];
                        y += dir[1];
                    }
                }
            }
        }
    }

    // int mode = (dir[0] + dir[1] < 0);

    // for (int i = mode ? 0 : SIZE_OF_BOARD - 1; mode ? i < SIZE_OF_BOARD : i >= 0; mode? i++ : i--) {
    //     for (int j = mode ? 0 : SIZE_OF_BOARD - 1; mode ? j < SIZE_OF_BOARD : j >= 0; mode? j++ : j--) {
    //         if(state->board[i][j]) {
    //             int y = j, x = i;
    //             while(x + dir[0] >= 0 && x + dir[0] < SIZE_OF_BOARD && y + dir[1] >= 0 && y + dir[1] < SIZE_OF_BOARD && !state->board[x + dir[0]][y + dir[1]]) {
    //                 state->board[x + dir[0]][y + dir[1]] = state->board[x][y];
    //                 state->board[x][y] = 0;
    //                 x += dir[0];
    //                 y += dir[1];
    //             }
    //         }
    //     }
    // }
}

int operation(int opn, int x) {
    switch (opn)
    {
    case 1:
        // +
        return 2 * x;
    case 2:
        // -
        return 0;
    case 3:
        // *
        return x * x;
    case 4:
        // ÷
        return 1;
    
    default:
        printf("ERROR\noperation: Invalid operation! Allowed operations are ADD, SUBTRACT, MULTIPLY and DIVIDE.\n");
        exit(EXIT_FAILURE);
    }
}

void doOpns(State *state, int *dir, int opn) {
    if(dir[0] + dir[1] < 0) {
        for (int i = 0; i < SIZE_OF_BOARD; i++) {
            for (int j = 0; j < SIZE_OF_BOARD; j++) {
                if(state->board[i][j]) {
                    if(i - dir[0] >= 0 && i - dir[0] < SIZE_OF_BOARD && j - dir[1] >= 0 && j - dir[1] < SIZE_OF_BOARD) {
                        if(state->board[i][j] == state->board[i - dir[0]][j - dir[1]]) {
                            state->board[i][j] = operation(opn, state->board[i][j]);
                            state->board[i - dir[0]][j - dir[1]] = 0;
                        }
                    }
                }
            }
        }
    }
    else {
        for (int i = SIZE_OF_BOARD - 1; i >= 0; i--) {
            for (int j = SIZE_OF_BOARD - 1; j >= 0; j--) {
                if(state->board[i][j]) {
                    if(i - dir[0] >= 0 && i - dir[0] < SIZE_OF_BOARD && j - dir[1] >= 0 && j - dir[1] < SIZE_OF_BOARD) {
                        if(state->board[i][j] == state->board[i - dir[0]][j - dir[1]]) {
                            state->board[i][j] = operation(opn, state->board[i][j]);
                            state->board[i - dir[0]][j - dir[1]] = 0;
                        }
                    }
                }
            }
        }
    }
}

void move(State *state, int d, int opn) {

    int dir[2];
    switch (d)
    {
    case 1:
        dir[0] = 0;
        dir[1] = -1;
        break;
    case 2:
        dir[0] = 0;
        dir[1] = 1;
        break;
    case 3:
        dir[0] = -1;
        dir[1] = 0;
        break;
    case 4:
        dir[0] = 1;
        dir[1] = 0;
        break;
    
    default:
        break;
    }
    pack(state, dir);
    doOpns(state, dir, opn);
    pack(state, dir);
}

void assign(State *state, int val, int x, int y) {
    // printf("game.c assign\n");
    // print_board(state);
    state->board[x][y] = val;
}



// int mai1n() {
//     State *state = (State *)malloc(sizeof(State));

//     _init(state);
//     state->board[3][3] = 4;
//     state->board[3][2] = 4;
//     state->board[2][2] = 4;
//     state->board[2][1] = 4;
//     state->board[0][0] = 4;
//     state->board[1][0] = 4;
//     state->board[2][0] = 4;
//     state->board[3][0] = 4;

//     print_board(state);
//     printf("\n");
//     int dir[2] = {1, 0};
//     move(state, dir, 4);
//     print_board(state);

//     return 0;
// }