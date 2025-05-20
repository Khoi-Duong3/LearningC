#include <stdio.h>
#include <math.h>
#include <string.h>


int main(){
    double radius = 0.0;
    double area = 0.0;
    double circumference = 0.0;
    double surfaceArea = 0.0;
    double volume = 0.0;
    const double pi = 3.14159;

    printf("Enter in the radius of your circle: ");
    scanf("%lf", &radius);

    area = pow(radius, 2) * pi;
    circumference = radius * 2 * pi;
    surfaceArea = 4 * pi * pow(radius, 2);
    volume = (4.0/3.0) * pi * pow(radius, 3);

    printf("Circle with a radius of %.1lf has an area of: %.1lf\n", radius, area);
    printf("Circle with a radius of %.1lf has a circumference of: %.1lf\n", radius, circumference);
    printf("Sphere with a radius of %.1lf has a surface area of: %.1lf\n", radius, surfaceArea);
    printf("Sphere with a radius of %.1lf has a volume of: %.1lf\n", radius, volume);
    


    return 0;
}