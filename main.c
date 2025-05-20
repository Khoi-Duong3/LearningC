#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int arithmetic(){

    int x = 5;
    int y = 3;
    int z = 0;

    //z = x + y;
    //z = x - y;
    //z = x * y;
    z = x / y;

    printf("%d\n", z);

    return 0;
}

int main() {
/*
    arithmetic();

    int age = 21;
    int year = 2025;
    float gpa = 3.9;
    double pi = 3.14159265358979;
    char grade = 'A';
    char symbol = '!';

    char artist[] = "Zutomayo";
    bool isSleeping = false; // Instead of true or false we can use 1 or 0 here and it will also work!

    printf("Hello World, I'm %d years old\n", age);
    printf("The current year is %d\n", year);
    printf("My current GPA: %f\n", gpa);
    printf("Your grade is: %c%c\n", grade, symbol);

    printf("The value of pi is: %.15f\n", pi);
    printf("%s makes very good music\n", artist);

    if (isSleeping){
        printf("You are asleep");
    } else {
        printf("You are awake");
    }
        


    int age;
    float gpa;
    char grade;
    char name[12];
    char fullname[30];

    printf("Please enter your age: ");
    scanf("%d", &age);

    printf("Enter your GPA: ");
    scanf("%f", &gpa);

    printf("Enter your grade: ");
    scanf(" %c", &grade);

    printf("Enter your name: ");
    scanf("%s", &name);

    getchar();

    printf("Enter your full name: ");
    fgets(fullname, sizeof(fullname), stdin);
    fullname[strlen(fullname) - 1] = '\0';


    printf("%d\n", age);
    printf("%.1f\n", gpa);
    printf("%c\n", grade);
    printf("%s\n", name);
    printf("%s\n", fullname);
     */

    shoppingCart();

    return 0;
}