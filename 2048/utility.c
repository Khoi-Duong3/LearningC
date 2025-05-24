// CODE: Inlcude necessary librar(y/ies)
#include <termios.h> // used in getch_unix()
#include <unistd.h>  // used in getch_unix()
#include <stdio.h>
#include <stdlib.h>
#include "utility.h"

// CODE: the implementation of functions and related variables 


/*Receiving an input from keyboard
IMPORTANT: DO NOT CHANGE ANYTHING IN getch_unix() FUNCTION.
To test this function and see if it works on your OS you can use testMyInput.c. 
It should work on any UNIX based OS.
This function receives all possible charaters from a keyboard.
The returned character `ch` will be used in "your game logic" as:
if ch='w' // Move Up
if ch='s' // Move Down
if ch='a' // Move Left
if ch='d' // Move Right
if ch='q' // break the game loop and quit
otherwise  do nothing
*/
char getch_unix() {
    struct termios oldt, newt;
    char ch;
    tcgetattr(STDIN_FILENO, &oldt); // Gets the current terminal settings
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}

int move_left(int board[size][size]){
    int moved = 0; // This is used as a boolean to show tell the program whether the player has inputted a move command or not
    for (int i = 0; i < size; i++){
        int temp[size];
        int result[size];
        int x = 0;
        for (int j = 0; j < size; j++){
            if (board[i][j] != 0){
                temp[x] = board[i][j]; // Assign the value at of the board onto the temp array at index x before incrementing
                x++;
            }
        }

        for (int j = x; j < size; j++){
            temp[j] = 0;
        }

        // This loop here is to merge all of the tiles with the same number together and doubling them
        for (int j = 0; j < size-1; j++){
            if (temp[j] != 0 && temp[j] == temp[j+1]){
                temp[j] *= 2;
                temp[j+1] = 0;
                moved = 1;
                j++;
            }
        }
        int y = 0;
        for (int j = 0; j < size; j++){
            if (temp[j] != 0){
                result[y] = temp[j];
                y++;
            }
        }
        for (int j = y; j < size; j++){
            result[j] = 0;
        }

        for (int j = 0; j < size; j++){
            if (board[i][j] != result[j]){
                moved = 1;
            }
            board[i][j] = result[j];
        }
    }

    return moved;
}

int move_right(int board[size][size]){
    int moved = 0;
    for (int i = 0; i < size; i++){
        int temp[size];
        int result[size];
        int x = 0;
        for (int j = size - 1; j >= 0; j--){
            if(board[i][j] != 0){
                temp[x] = board[i][j];
                x++;
            }
        }
        for (int j = x; j < size; j++){
            temp[j] = 0;
        }

        for (int j = 0; j < size - 1; j++){
            if(temp[j] != 0 && temp[j] == temp[j+1]){
                temp[j] *= 2;
                temp[j + 1] = 0;
                moved = 1;
                j++;
            }
        }
        int y = 0;
        for (int j = 0; j < size; j++){
            if(temp[j] != 0){
                result[y] = temp[j];
                y++;
            }
        }

        for (int j = y; j < size; j++){
            result[j] = 0;
        }

        for (int j = 0; j < size; j++){
            if (board[i][size-j-1] != result[j]){
                moved = 1;
            }
            board[i][size-j-1] = result[j];
        }
    }

    return moved;
}

int move_up(int board[size][size]){
    int moved = 0;
    for (int j = 0; j < size; j++){
        int temp[size];
        int result[size];
        int x = 0;
        for (int i = 0; i < size; i++){
            if (board[i][j] != 0){
                temp[x] = board[i][j];
                x++; 
            }
        }
        for (int i = x; i < size; i++){
            temp[i] = 0;
        }

        for (int i = 0; i < size - 1; i++){
            if(temp[i] != 0 && temp[i] == temp[i+1]){
                temp[i] *= 2;
                temp[i+1] = 0;
                moved = 1;
                i++;
            }
        }
        int y = 0;
        for (int i = 0; i < size; i++){
            if (temp[i] != 0){
                result[y] = temp[i];
                y++;
            }
        }
        for (int i = y; i < size; i++){
            result[i] = 0;
        }
        for (int i = 0; i < size; i++){
            if(board[i][j] != result[i]){
                moved = 1;
            }
            board[i][j] = result[i];
        }
    }
    return moved;
}

int move_Down(int board[size][size]){
    int moved = 0;
    for (int j = 0; j < size; j++){
        int temp[size];
        int result[size];
        int x = 0;
        for (int i = size - 1; i >= 0; i--){
            if (board[i][j] != 0){
                temp[x] = board[i][j];
                x++;
            }
        }

        for (int i = x; i < size; i++){
            temp[i] = 0;
        }

        for (int i = 0; i < size - 1; i++){
            if (temp[i] != 0 && temp[i] == temp[i+1]){
                temp[i] *= 2;
                temp[i + 1] = 0;
                moved = 1;
                i++;
            }
        }

        int y = 0;
        for (int i = 0; i < size; i++){
            if (temp[i] != 0){
                result[y] = temp[i];
                y++;
            }
        }
        for (int i = y; i < size; i++){
            result[i] = 0;
        }

        for (int i = 0; i < size; i++){
            if (board[size-i-1][j] != result[i]){
                moved = 1;
            }
            board[size-i-1][j] = result[i];
        }
    }

    return moved;
}

