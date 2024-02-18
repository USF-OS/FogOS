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
  int runner = 1;
  for (int i = 0; runner < num_lines; i++) {
    char *curr_line = *(lines + runner - 1);
    char *next_line = *(lines + runner);
    int len = strlen(curr_line) + 1;
    *(unique_lines + num_unique_lines) = (char *) malloc(len * sizeof(char));
    if (*(unique_lines + num_unique_lines) == NULL) return;

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

void
ignoreBlanks(int num_lines, char **lines)
{
  /**
   * Ignore leading blank chars
   * We sort based on alphanumeric ASCII chars,
   *   but we still output the line with the blanks.
   * We're sorting w/o blanks, but we need to preserve the line
   *   with blanks so we can print it to stdout.
   * How? We can put lines with blanks in an array.
   * We're not sorting these lines, but instead keeping them
   *   for when we print to stdout.
  */

  /* Array of lines with leading blanks */
  int num_blank_lines = 0;
  char **leading_blanks = (char **) malloc(num_lines * sizeof(char *));
  if (leading_blanks == NULL) errorVoid();

  // Check all lines for leading blanks. If any found, add to blanks array
  char *curr_line = NULL;
  int blank_index;
  int len;
  for (int i = 0; i < num_lines; i++) {
    curr_line = *(lines + i);
    len = strlen(curr_line) + 1;
    blank_index = 0;
    while (*(curr_line + blank_index) == ' ' || *(curr_line + blank_index) == '\t') { blank_index++; /* Skip leading blanks */ }
    // Save line with blanks to blank_lines
    if (blank_index > 0) {
      *(leading_blanks + num_blank_lines) = (char *) malloc(len * sizeof(char));
      if (*(leading_blanks + num_blank_lines) == NULL) errorVoid();
      strcpy(*(leading_blanks + num_blank_lines++), curr_line);
      curr_line += blank_index;
      // printf("%s\n", curr_line);
    }
  }

  // insertionSort(num_lines, lines);
  // printLines(num_lines, lines);
  printLines(num_blank_lines, leading_blanks);
}
