#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "user/user.h"

 //#define NaN (0.0 / 0.0)

/**
 * pow computes the power of a base number raised to an exponent.
 * 
 * @param x the base number
 * @param y the exponent
 * @return the result of x raised to the power of y
 */
float pow1(float x, float y){
	//base case if base is 0
	if(x==0)
		return 0;

	//base case if exponent is 0
	if(y==0)
		return 1;

	//if exponent is a negative number
	if(y<0)
		return 1/(x*pow1(x, -y-1));

    //if it's a positive number
	else
		return x*pow1(x,y-1);
	
}

/**
 * sqrt computes the square root of a non-negative number using binary search.
 * 
 * @param x the number whose square root is to be calculated
 * @return the square root of x. Returns NaN if x is negative.
 */

//https://stackoverflow.com/questions/61936060/finding-the-square-root-of-a-number-by-using-binary-search#:~:text=Calculate%20the%20middle%20index%20mid,ans%20as%20the%20square%20root
float sqrt1(float x){
	 
     //base cases
    if (x < 0) {
        return 0; 
    } else if (x == 0 || x == 1) {
        return x; 
    }
 	
    float start = 0.0;
    float end= x;
    float mid;

    // Use binary search to find the square root
    while (end>start) {
        mid = (start + end) / 2;
        if (mid * mid > x) {
            end= mid;
        } else {
            start = mid;
        }
    }
    return start;
}

/**
 * exp computes the exponential function e^x
 * 
 * @param x the exponent.
 * @return the result of raising e to the power of x.
 */
float exp1(float x){
	float e=2.71828182845904523536028747135266249;
	return pow1(e,x);
}

/**
 * Returns the largest integer that is less than or equal to the given double value. For example, 2.9 becomes 2.
 *
 * @param val the input double value
 * @return the largest integer that is less than or equal to the given double value
 */
float floor1(float val) {
    if (val >= 0) {
        return (int)val;
    }
    else {
        if (val == (int)val) {
            return (int)val;
        } else {
            return (int)val - 1;
        }
    }
}

/**
 * Returns the smallest integer that is greater than or equal to the given double value. For example, 2.9 becomes 3.
 *
 * @param val the input double value
 * @return the smallest integer that is greater than or equal to the given double value
 */
float ceil1(float val) {
    if (val >= 0) {
        if (val == (int)val) {
            return (int)val;
        } else {
            return (int)val + 1;
        }
    } else {
        return (int)val;
    }
}

/**
 * Returns the closest integer value to the given double.
 *For example -1.1 equals -1.

 * @param val the input double value
 * @return the closest integer value to the given double
 */
int closestInt1(float val) {
    if (val > 0) {
        int upper_closest = (int)(val + 0.5);
        return upper_closest;
    } else {
        int lower_closest = (int)(val - 0.5);
        return lower_closest;
    }
}	

int main(void)
{

	float g = 3.2;
	printf("%f\n", g);
	return 0;	   
/*	// Test cases for pow function
    printf("Testing pow function:\n");
    printf("2^3 = %f\n", pow1(2.0, 3.0));
    printf("5^-2 = %f\n\n", pow1(5.0, -2.0));
   
    // Test cases for sqrt function
    printf("Testing sqrt function:\n");
    printf("Square root of 25 = %f\n", sqrt1(25));
    printf("Square root of 2 = %f\n\n", sqrt1(2));

    // Test cases for exp function
    printf("Testing exp function:\n");
    printf("e^2 = %.2lf\n", exp(2));
    printf("e^-1 = %.2lf\n", exp(-1));

     // Test cases for floor function
    printf("Testing floor function:\n");
    printf("floor(2.9) = %.2lf\n", floor(2.9)); 
    printf("floor(-2.9) = %.2lf\n\n", floor(-2.9));

    // Test cases for ceil function
    printf("Testing ceil function:\n");
    printf("ceil(2.1) = %.2lf\n", ceil(2.1)); 
    printf("ceil(-2.1) = %.2lf\n\n", ceil(-2.1)); 

    // Test cases for closestInt function
    printf("Testing closestInt function:\n");
    printf("closestInt(2.1) = %d\n", closestInt(2.1)); 
    printf("closestInt(-2.1) = %d\n\n", closestInt(-2.1));     
  */
  //  return 0;
}
