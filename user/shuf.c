#include "shuf.h"

/* Requirements for use 
* 1. Makefile
*     - Add shuf to UPROGS
*     - Add vec.o to ULIB
*     - Add shuffler.o to ULIB
* 2. Additional
*     - System call for unix-time
*/



int main(int argc, char** argv)
{
  shuf_start(argc, argv);
  return 0;
}
