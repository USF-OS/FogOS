#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "user/user.h"
#include "user/math.h"

int main(void){
	printf("try\n");   
    // Test cases for pow function
    printf("Testing pow function:\n");
    printf("2^3 = %.2f\n", pow(2.0, 3.0));
    printf("5^-2 = %.2f\n\n", pow(5.0, -2.0));
   
    // Test cases for sqrt function
    printf("Testing sqrt function:\n");
    printf("Square root of 25 = %.2f\n", sqrt(25));
    printf("Square root of 2 = %.2f\n\n", sqrt(2));

    // Test cases for exp function
    printf("Testing exp function:\n");
    printf("e^2 = %.2f\n", exp(2));
    printf("e^-1 = %.2f\n", exp(-1));

    return 0;
}
