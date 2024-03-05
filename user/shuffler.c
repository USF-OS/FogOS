#include "shuf.h"
#include "user.h"

#define RAND_MAX ((1U << 31) - 1)

/* The following code for LCG cited from:
 * https://rosettacode.org/wiki/Linear_congruential_generator
*/

int rseed = 0;

void srand(int x) 
{
  rseed = x;
}

int lcg() 
{
  return rseed = (rseed * 1103515245 + 12345) & RAND_MAX;
}

/* Fisher-Yates Modern Shuffling Algorithm */

void fisher_yates(vec_t* vec, int flag) 
{
  // random seed range
  if (flag == 0){
  	  srand((uint32)(time() % 1000000));

  } 

  if (flag != 0){
  	  srand((uint32)(flag % 1000000));
  }

  int i, j;
  char* tmp;

  for (i = vec->len - 1; i > 0; i--) {
    j = lcg() % (i + 1);
    tmp = vec->strings[j];
    vec->strings[j] = vec->strings[i];
    vec->strings[i] = tmp;
  }
}

