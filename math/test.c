#include "math.h"
#include <stdio.h>

int main() {
    float base, exponent, number;


    // Test pow function
    printf("Enter base for pow function: ");
    scanf("%f", &base);
    printf("Enter exponent for pow function: ");
    scanf("%f", &exponent);
    printf("Result of pow(%f, %f) is %f\n", base, exponent, osPow(base, exponent));

    // Test sqrt function
    printf("Enter a number for sqrt function: ");
    scanf("%f", &number);
    printf("Square root of %f is %f\n", number, osSqrt(number));

    // Test exp function
    printf("Enter exponent for exp function: ");
    scanf("%f", &exponent);
    printf("Result of exp(%f) is %f\n", exponent, osExp(exponent));

    // Test floor function
    printf("Enter a number for floor function: ");
    scanf("%f", &number);
    printf("Floor of %f is %f\n", number, osFloor(number));

    // Test ceil function
    printf("Enter a number for ceil function: ");
    scanf("%f", &number);
    printf("Ceil of %f is %f\n", number, osCeil(number));

    // Test closestInt function
    printf("Enter a number for closestInt function: ");
    scanf("%f", &number);
    printf("Closest integer to %f is %d\n", number, osClosestInt(number));

    return 0;
}
