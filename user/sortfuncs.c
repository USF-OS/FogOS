#define NULL ((void *) 0)
#define NUM_LINES 1000

/**
 * @return -1 for memory allocation error
*/
int
errorInt()
{
  printf("Memory allocation error.\n");
  return -1;
}

void
errorVoid()
{
  printf("Memory allocation error.\n");
  return;
}

bool
isFlag(char *flag)
{
  return (
    strcmp(flag, "-n") == 0 ||
    strcmp(flag, "-r") == 0 ||
    strcmp(flag, "-u") == 0 ||
    strcmp(flag, "-b") == 0 ||
    strcmp(flag, "-f") == 0
  );
}

/**
 * Good for small input data
 * Use xv6's global 'ticks' variable to compare sort times
 * between insertion sort and merge sort
 * Once we know threshold, let that be the determinant
 * as whether to use insertion sort or merge sort
 * 
 * Hope that works
*/
void
insertionSort(int num_lines, char *lines[])
{
  int j;
  char *curr_line = NULL;
  for (int i = 1; i < num_lines; i++) {
    j = i - 1;
    curr_line = *(lines + i);
    while (j >= 0 && strcmp(*(lines + j), curr_line) > 0) {
      *(lines + j + 1) = *(lines + j);
      j--;
    }
    *(lines + j + 1) = curr_line;
  }
}

void
printLines(int num_lines, char *lines[])
{
  for (int i = 0; i < num_lines; i++) {
    printf("%s\n", *(lines + i));
  }
}

void
freeLines(int num_lines, char *lines[])
{
  for (int i = 0; i < num_lines; i++) {
    free(*(lines + i));
  }
  free(lines);
  lines = NULL;
}

void
unique(int num_lines, char *lines[])
{
  /**
   * Sort lines, compare adjacent lines, ignore duplicates
   * Iterate through lines and compare curr to next
   * If curr == next, ignore next
   * Put unique lines in a new array or change in place?
   * For now, start with new array
  */

  insertionSort(num_lines, lines);

  int num_unique_lines = 0;
  char **unique_lines = (char **) malloc(num_lines * sizeof(char *));
  if (unique_lines == NULL) errorVoid();
  int runner = 1;
  for (int i = 0; runner < num_lines; i++) {
    char *curr_line = *(lines + runner - 1);
    char *next_line = *(lines + runner);
    int len = strlen(curr_line) + 1;
    *(unique_lines + num_unique_lines) = (char *) malloc(len * sizeof(char));
    if (*(unique_lines + num_unique_lines) == NULL) errorVoid();

    strcpy(*(unique_lines + num_unique_lines++), curr_line);

    while (strcmp(curr_line, next_line) == 0) {
      next_line = *(lines + ++runner);
    }
    runner++;
  }

  // Should not be printing here. Testing purposes only
  // On second thought, might be ok for certain flags
  // On third thought, probably not a good idea -> hard to follow
  printf("\nSorted unique values:\n");
  printLines(num_unique_lines, unique_lines);
  freeLines(num_unique_lines, unique_lines);
}
