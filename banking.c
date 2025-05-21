#include <stdio.h>

void checkBalance(float balance);
float deposit();
float withdraw(float balance);

int main(){

    float balance = 1000.0;
    int choice = 0;
    do {
        printf("***Banking App***\n");
        printf("1. Check Balance\n");
        printf("2. Deposit Money\n");
        printf("3. Withdraw Money\n");
        printf("4. Exit\n");
        printf("Please make your choice: ");
        scanf("%d", &choice);

        switch(choice){
            case 1:
                checkBalance(balance);
                break;
            
            case 2:
                balance += deposit(balance);
                break;

            case 3:
                balance -= withdraw(balance);
                break;

            default:
                printf("\nInvalid choice!, select 1-4\n");
        }
    }while (choice != 4);

    balance += deposit();
}

void checkBalance(float balance){
    printf("Your balance is currently: %f\n", balance);
}

float deposit(){
    float amount = 0.0;

    printf("Please enter the amount you want to deposit: ");
    scanf("%f", &amount);

    return amount;
}

float withdraw(float balance){
    float amount = 0;
    printf("Please enter the amount you want to withdraw: ");
    scanf("%f", &amount);

    if (amount < 0) {
        printf("Invalid amount\n");
        return 0.0f;

    } else if (amount > balance){
        printf("You do not have enough money in your balance\n");
        return 0.0f;
    } else {
        printf("You have withdrawn %f\n", amount);
        return amount;
    }

    return 0.0f;
}
