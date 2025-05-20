#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int shoppingCart(){

    char item[50] = "";
    float price = 0.0f;
    int quantity = 0;
    char currency = '$';
    float total = 0.0f;

    printf("What items would you like to buy?: ");
    fgets(item, sizeof(item), stdin);

    printf("What is the price of this item?: ");
    scanf("%f", &price);

    printf("How many would you like?: ");
    scanf("%d", & quantity);

    total = price * quantity;


    printf("You have bought: %d %s", quantity, item);
    printf("Your total price is: %c%.2f", currency, total);

    return 0;
}

int main() {

}