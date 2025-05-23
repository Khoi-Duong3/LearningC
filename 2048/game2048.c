// CODE: Inlcude necessary librar(y/ies)
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include "utility.h"

int main() {
    srand(time(NULL)); // set seed to NULL for randomness from time.h
    // CODE: if necessary
    
    int board[size][size];
    make_board(board);
    add_random_tile(board);
    add_random_tile(board);
    while (1) {
        // CODE: here we only call the functions
        // print the board in every iteration
        // create a function to check if the game is over
        // call getch_unix(), if the return is 'q' quit the game
        /// if not send it your game logic
        draw_board(board);
        char input = getch_unix();
        if (input == 'q'){
            break;
        }

        int moved = 0;
        switch(input){
            case 'w':
                moved = move_up(board);
                break;
            case 'a':
                moved = move_left(board);
                break;
            case 's':
                moved = move_down(board);
                break;
            case 'd':
                moved = move_right(board);
                break;
        }

        if(moved) {
            add_random_tile(board);
            if (!can_move(board)) {
                draw_board(board);
                printf("Game Over!\n");
                break;
            }

        }
    }
    
    return 0;
} 