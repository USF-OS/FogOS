#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "user/user.h"
#include "user/math.h"

#define NaN (0.0 / 0.0)

/**
 * pow computes the power of a base number raised to an exponent.
 * 
 * @param x the base number
 * @param y the exponent
 * @return the result of x raised to the power of y
 */
double pow(double x, double y){
	//base case if base is 0
	if(x==0)
		return 0;

	//base case if exponent is 0
	if(y==0)
		return 1;

	//if exponent is a negative number
	if(y<0)
		return 1/(x*pow(x, -y-1));

    //if it's a positive number
	else
		return x*pow(x,y-1);
	
}

/**
 * sqrt computes the square root of a non-negative number using binary search.
 * 
 * @param x the number whose square root is to be calculated
 * @return the square root of x. Returns NaN if x is negative.
 */

//https://stackoverflow.com/questions/61936060/finding-the-square-root-of-a-number-by-using-binary-search#:~:text=Calculate%20the%20middle%20index%20mid,ans%20as%20the%20square%20root
double sqrt(double x){
	 
     //base cases
    if (x < 0) {
        return NaN; 
    } else if (x == 0 || x == 1) {
        return x; 
    }
 	
 	double start = 0.0;
    double end= x;
    double mid;

    // Use binary search to find the square root
    while (end > start) {
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
double exp(double x){
	double e=2.71828182845904523536028747135266249;
	return pow(e,x);
}

/**
 * The floor function is a function that takes in a valid double and retruns the smallest whole value it can be.
 * For example, 2.9 becomes 2.
 */
double floor(double val) {
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
 * The ceil function is a function that takes in a valid double and returns the largest whole value it can be.
 * For example, 2.9 becomes 3.
 */
double ceil(double val) {
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
 * The ceil function is a function that takes in a valid double and returns the closest whole value.
 * For example -1.1 equals -1.
 */
int closestInt(double val) {
    if (val > 0) {
        int upper_closest = (int)(val + 0.5);
        return upper_closest;
    } else {
        int lower_closest = (int)(val - 0.5);
        return lower_closest;
    }
}
