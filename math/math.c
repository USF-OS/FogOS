#include "math.h"

#define NaN (0.0 / 0.0)

/**
 * pow computes the power of a base number raised to an exponent.
 * 
 * @param x the base number
 * @param y the exponent
 * @return the result of x raised to the power of y
 */
float osPow(float x, float y){
	//base case if base is 0
	if(x==0)
		return 0;

	//base case if exponent is 0
	if(y==0)
		return 1;

	//if exponent is a negative number
	if(y<0)
		return 1/(x*osPow(x, -y-1));

    //if it's a positive number
	else
		return x*osPow(x,y-1);
	
}

/**
 * sqrt computes the square root of a non-negative number using binary search.
 * 
 * @param x the number whose square root is to be calculated
 * @return the square root of x. Returns NaN if x is negative.
 */

//https://stackoverflow.com/questions/61936060/finding-the-square-root-of-a-number-by-using-binary-search#:~:text=Calculate%20the%20middle%20index%20mid,ans%20as%20the%20square%20root
float osSqrt(float x){	 
     //base cases
    if (x < 0) {
        return NaN; 
    } else if (x == 0 || x == 1) {
    	return x;
    }
    float start = 0.0;
    float end= x;
    float mid;

    // Use binary search to find the square root
    while (end - start > 0.00001) {
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
float osExp(float x){
	float e=2.71828182845904523536028747135266249;
	return osPow(e,x);
}

/**
 * Returns the largest integer that is less than or equal to the given float value. For example, 2.9 becomes 2.
 *
 * @param val the input float value
 * @return the largest integer that is less than or equal to the given float value
 */
float osFloor(float val) {
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
 * Returns the smallest integer that is greater than or equal to the given float value. For example, 2.9 becomes 3.
 *
 * @param val the input float value
 * @return the smallest integer that is greater than or equal to the given float value
 */
float osCeil(float val) {
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

 * @param val the input float value
 * @return the closest integer value to the given double
 */
int osClosestInt(float val) {
    if (val > 0) {
        int upper_closest = (int)(val + 0.5);
        return upper_closest;
    } else {
        int lower_closest = (int)(val - 0.5);
        return lower_closest;
    }
}
