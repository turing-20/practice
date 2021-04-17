#ifndef GAME_H
#define GAME_H

typedef struct
{
    int board[4][4];
} State;

int get_value_val(int x, int y);
void print_stderr(int code);
void print_var_names();
void add_var_name(char *name, int x, int y);
void transpose();
void reverse();
void left_merge(int operation);
void left_compress();
void left_move(int operation);
void right_move(int operation);
void up_move(int operation);
void make_move(int operation, int direction);
void assign_value(int value, int x, int y);
int get_value(int x, int y);
void add_random();
void initialize();
void print_board();
void down_move(int operation);

#endif