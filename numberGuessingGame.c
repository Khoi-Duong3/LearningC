#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

int main(){

    srand(time(NULL));

    int min = 0;
    int max = 100;
    int tries = 0;

    int randomNum = (rand() % (max - min)) + min;

    int guess;
    bool won = false;

    printf("Guess the number (0-100): ");
    scanf("%d", &guess);

    if (guess == randomNum) {
        tries++;
        printf("You win!");
        return 0;
    }

    while (!won) {
        tries++;
        printf("Wrong Answer! Guess again: ");
        scanf("%d", & guess);

        if (guess == randomNum) {
            printf("You win!");
            return 0;
        }
    }
}