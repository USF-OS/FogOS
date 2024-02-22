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

int
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

int
compare(char *s1, char *s2, int ignore_leading_blanks)
{
  if (ignore_leading_blanks) {
    while (*s1 == ' ' || *s1 == '\t') s1++;
    while (*s2 == ' ' || *s2 == '\t') s2++;
  }

  return strcmp(s1, s2);
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
insertionSort(int num_lines, char *lines[], int ignore_leading_blanks)
{
  int j;
  char *curr_line = NULL;
  for (int i = 1; i < num_lines; i++) {
    j = i - 1;
    curr_line = *(lines + i);
    while (j >= 0 && compare(*(lines + j), curr_line, ignore_leading_blanks) > 0) {
      *(lines + j + 1) = *(lines + j);
      j--;
    }
    *(lines + j + 1) = curr_line;
  }
}

int 
my_isdigit(char c) {
    return c >= '0' && c <= '9';
}

// Helper function to check if the first character of a string is numeric
int 
isNumeric(const char *str) {
    return my_isdigit(str[0]);
}

// parseLong function to manually parse a long from a string
long 
parseLong(const char *str) {
    long value = 0;
    while (my_isdigit(*str)) {
        value = value * 10 + (*str - '0');
        str++;
    }
    return value;
}

int 
compareStringsAsNumbers(const char* a, const char* b) {
    if (my_isdigit(a[0]) && my_isdigit(b[0])) {
        long numA = parseLong(a);
        long numB = parseLong(b);

        if (numA < numB) return -1;
        if (numA > numB) return 1;
    }

    return strcmp(a, b);
}

void 
insertionSortWithNumeric(int num_lines, char **lines) {
    int j;
    char *curr_line;
    for (int i = 1; i < num_lines; i++) {
        curr_line = lines[i];
        j = i - 1;

        // Use compareStringsAsNumbers for comparison
        while (j >= 0 && compareStringsAsNumbers(lines[j], curr_line) > 0) {
            lines[j + 1] = lines[j];
            j--;
        }
        lines[j + 1] = curr_line;
    }
}


void 
getFlags(int argc, char *argv[], char*** flags, int* flagCount) {
    *flags = (char**)malloc(100 * sizeof(char*)); 
    if (*flags == NULL) {
        printf("Memory allocation failed\n");
        exit(1); 
    }

    *flagCount = 0;
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            (*flags)[*flagCount] = argv[i]; 
            (*flagCount)++;
            
            if (*flagCount >= 100) { 
                printf("Maximum number of flags reached (100).\n");
                break;
            }
        }
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

  insertionSort(num_lines, lines, 0);

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

void
numeric(int num_lines, char *lines[]) {

  char **numericalLines = (char **)malloc(NUM_LINES * sizeof(char *));
  char **alphabeticLines = (char **)malloc(NUM_LINES * sizeof(char *));
  int numericCount = 0, alphabeticCount = 0;

  for (int i = 0; i < num_lines; i++) {
    if (isNumeric(lines[i])) {
        numericalLines[numericCount++] = lines[i];
    } else {
        alphabeticLines[alphabeticCount++] = lines[i];
    }
  }

  insertionSortWithNumeric(numericCount, numericalLines);
  insertionSort(alphabeticCount, alphabeticLines, 0);


  int index = 0;
  for (int i = 0; i < alphabeticCount; i++, index++) {
    lines[index] = alphabeticLines[i];
  }
  // Continue with numerical lines
  for (int i = 0; i < numericCount; i++, index++) {
    lines[index] = numericalLines[i];
  }

  // Assuming the rest of lines beyond index should be nullified if not all lines are overwritten
  //Probably not needed but safe
  for (int i = index; i < num_lines; i++) {
    lines[i] = NULL; 
  }
  

  // Clean up
  free(numericalLines);
  free(alphabeticLines);
}

//Swaps idnexes for reversing
void swap(char** a, char** b) {
    char* temp = *a;
    *a = *b;
    *b = temp;
}

void 
reverse(int num_lines, char *lines[]) {
    int start = 0;              
    int end = num_lines - 1;  

    while (start < end) {
        swap(&lines[start], &lines[end]);
        start++;
        end--;
    }
}


//True = 1
//False = 0
int
reverseCheck(char** flags, int flagCount) {
  for (int i = 0; i < flagCount; i++) {
    if (strcmp(flags[i], "-r") == 0) {
      return 1;
    }
    printf("%s\n", flags[i]);
  }
  return 0;
}