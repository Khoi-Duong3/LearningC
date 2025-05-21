#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

int main() {

    srand(time(NULL));

    int min = 0;
    int max = 100;

    int randomNum = (rand() % (max - min)) + min;

    printf("%d", randomNum);

    return 0;

}