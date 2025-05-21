#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int getUserChoice();
int getCompChoice();
void checkWinner (int userChoice, int compChoice);

int main(){

    int compChoice = getCompChoice();
    int userChoice = getUserChoice();
    checkWinner(userChoice, compChoice);

    return 0;
}


int getCompChoice(){
    srand(time(NULL));

    int min = 1;
    int max = 3;
    int randomNum = (rand() % (max - min)) + min;

    return randomNum;
}

int getUserChoice(){
    int choice = 0;

    do {
        printf("Choose an option\n");
        printf("1. Rock\n");
        printf("2. Paper\n");
        printf("3. Scissors\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

    }while (choice < 1 || choice > 3);

    return choice;
}

void checkWinner(int userChoice, int compChoice){

    if (userChoice == 1 && compChoice == 3){
        printf("You win!");
    } else if (userChoice == 2 && compChoice == 1){
        printf("You win!");
    } else if (userChoice == 3 && compChoice == 2){
        printf("You win!");
    } else if (userChoice == compChoice){
        printf("Draw!");
    } else {
        printf("You lose!");
    }
    
}