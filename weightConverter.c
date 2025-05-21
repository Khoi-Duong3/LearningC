#include <stdio.h>
#include <string.h>

int main(){

    float kg = 0.0;
    float lbs = 0.0;
    int choice = 0;

    printf("Weight Conversion Calculator\n");
    printf("1. Kilograms to Pounds\n");
    printf("2. Pounds to Kilograms\n");
    printf("Make a selection (1 or 2): ");
    scanf("%d", &choice);

    if (choice == 1) {
        printf("Enter your weight in kilograms (kg): ");
        scanf("%f", &kg);
        lbs = kg * 2.205;
        printf("Your weight in pounds is: %.2f", lbs);

    } else if (choice == 2){
        printf("Enter your weight in pounds(lbs): ");
        scanf("%f", &lbs);
        kg = lbs/2.205;
        printf("Your weight in kilograms is: %.2f", kg);
    } else {
        printf("Invalid input");
        return 1;
    }

    return 0;
}