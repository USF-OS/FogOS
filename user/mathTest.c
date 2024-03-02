#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "user/user.h"
#include "user/math.h"

int main(void)
{
	//trying to print float (currently xv6 not supporting) 
	float g = 3.2;
	printf("%f\n", g);

	// Test cases for pow function
   	printf("Testing pow function:\n");
	printf("2^3 = %f\n", pow(2.0, 3.0));
    	printf("5^-2 = %f\n\n", pow(5.0, -2.0));
   
    	// Test cases for sqrt function
	 printf("Testing sqrt function:\n");
   	 printf("Square root of 25 = %f\n", sqrt(25));
   	 printf("Square root of 2 = %f\n\n", sqrt(2));

   	 // Test cases for exp function
   	 printf("Testing exp function:\n");
   	 printf("e^2 = %f\n", exp(2));
   	 printf("e^-1 = %f\n", exp(-1));

    	 // Test cases for floor function
   	 printf("Testing floor function:\n");
   	 printf("floor(2.9) = %f\n", floor(2.9)); 
   	 printf("floor(-2.9) = %f\n\n", floor(-2.9));

   	 // Test cases for ceil function
   	 printf("Testing ceil function:\n");
   	 printf("ceil(2.1) = %f\n", ceil(2.1)); 
   	 printf("ceil(-2.1) = %f\n\n", ceil(-2.1)); 

   	 // Test cases for closestInt function
   	 printf("Testing closestInt function:\n");
   	 printf("closestInt(2.1) = %d\n", closestInt(2.1)); 
   	 printf("closestInt(-2.1) = %d\n\n", closestInt(-2.1));     
  
  	 return 0;
}
