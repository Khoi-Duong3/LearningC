#include <stdio.h>
#include <math.h>
#include <string.h>

int main(){
    double initial = 0.0;
    int years = 0;
    const int timesCompounded = 4;
    double rate = 0.0;
    double total = 0;

    printf("Enter your deposite amount: ");
    scanf("%lf", &initial);

    printf("Enter the interest rate: ");
    scanf("%lf", &rate);

    printf("Enter the number of years you want to invest: ");
    scanf("%d", &years);

    rate = rate / 100;
    total = initial * pow(1 + rate / timesCompounded, timesCompounded * years);

    printf("The amount of money you will have after investing for %d is: %.2lf", years, total);

    return 0;

}