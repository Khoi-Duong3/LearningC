#ifndef UTILITY_H
#define UTILITY_H


#define size 4

// CODE: the declarations [only the necessary ones] of functiona and related variables 
void make_board(int board[size][size]);

void add_random_tile(int board[size][size]);

void draw_board(int board[size][size]);

char getch_unix(void);

int move_left(int board[size][size]);
int move_right(int board[size][size]);
int move_up(int board[size][size]);
int move_down(int board[size][size]);

int is_full(int board[size][size]);
int can_move(int board[size][size]);

#endif