#include <stdio.h>

int main(){

    int numbers[] = {1,2,3,4,5,6,7}; // Arrays in C cannot have elements of different types, they must contain elements of the declared type

    printf("%d\n", numbers); // If we print this it's printing out the pointer

    for (int i = 0; i < 7; i++){
        printf("%d\n", numbers[i]);
    }

    printf("%d", sizeof(numbers)); // sizeof() gives the size of a variable in bytes
    
    int length = sizeof(numbers) / sizeof(numbers[0]);


    return 0;
}