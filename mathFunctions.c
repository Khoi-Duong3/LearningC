#include <stdio.h>
#include <math.h>

int main (){
    int x = 9;
    int y = 2;
    float z = 3.6;
    int a = -5;

    x = sqrt(9);
    y = pow(y, 2);
    z = round(z); // Or use ceil(z) or floor(z) to always round up or down
    a = abs(a);

    printf("%d\n", x);
    printf("%d\n", y);
    printf("%f\n", z);
    printf("%d", a);

    return 0;

}