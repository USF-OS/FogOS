#include "shuf.h"
#include "user.h"

int main()
{
  // shuf certain number of lines, print to stdio
  char* test1[]={"shuf","README.md","-n","10", "-t", "5432"};

  // shuf file, print to stdio
  char* test2[]={"shuf","README.md", "-t", "54"};

  // shuf with specified seed, print to stdio
  char* test3[]={"shuf","README.md", "-t", "90", "-n", "0"};

  printf("\n");
  printf("***************\n");
  printf("STARTING TEST 1\n");
  printf("Args = %s %s %s %s %s %s\n","shuf","README.md","-n","10", "-t", "5432");
  printf("***************\n");
  shuf_start(6, test1);
  printf("\n");
  printf("***************\n");
  printf("STARTING TEST 2\n");
  printf("Args = %s %s %s %s\n","shuf","README.md", "-t", "54");
  printf("***************\n");
  shuf_start(4, test2);
  printf("\n");
  printf("***************\n");
  printf("STARTING TEST 3\n");
  printf("Args = %s %s %s %s %s %s\n","shuf","README.md", "-t", "90", "-n", "0");
  printf("***************\n");
  shuf_start(6, test3);
  printf("\n");

  return 0;
}

