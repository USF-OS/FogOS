/**
 * @file sortfuncs.c a collection of helper functions used for 'sort'
 * @author Shyon Ghahghahi
 * @author Amin Joseph
*/

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
isFlag(char* flag)
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
 * @return 0 if lowercase, 1 if uppercase
*/
int
my_isUpper(const char c)
{
  return c >= 'A' && c <= 'Z';
}

/**
 * @brief Determines if at least 1 character in the line is uppercase
 * @return 0 for all lowercase or 1 for at least 1 uppercase character
*/
int
my_lineIsUpper(const char* line)
{
  int len = strlen(line);
  for (int i = 0; i < len; i++) {
    if (*(line + i) >= 'A' && *(line + i) <= 'Z') return 1;
  }

  return 0;
}

/**
 * @brief Converts a line to all lowercase characters
 * @return The lowercase line
*/
char*
my_toLower(char* line)
{
  int len = strlen(line);
  char *lowercase_line = (char *) malloc(len * sizeof(char));
  /* DO NOT FORGET TO FREE THIS */
  if (lowercase_line == NULL) return NULL;
  strcpy(lowercase_line, line);

  char curr_char;
  for (int i = 0; i < len; i++) {
    curr_char = *(line + i);
    if (my_isUpper(curr_char)) {
      *(lowercase_line + i) += 'a' - 'A';
    }
  }

  return lowercase_line;
}

int
compare(const char* s1, const char* s2, char* flag)
{
  if (strcmp(flag, "-f") == 0) {
    char *s1_lower = (char *) malloc((strlen(s1) + 1) * sizeof(char));
    char *s2_lower = (char *) malloc((strlen(s2) + 1) * sizeof(char));
    if (s1_lower == NULL || s2_lower == NULL) errorInt();

    strcpy(s1_lower, s1);
    strcpy(s2_lower, s2);

    s1_lower = my_toLower(s1_lower);
    s2_lower = my_toLower(s2_lower);

    return strcmp(s1_lower, s2_lower);

  } else if (strcmp(flag, "-b")) {
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
insertionSort(int num_lines, char *lines[], char* flag)
{
  int j;
  char *curr_line = NULL;
  for (int i = 1; i < num_lines; i++) {
    j = i - 1;
    curr_line = *(lines + i);
    while (j >= 0 && compare(*(lines + j), curr_line, flag) > 0) {
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
ignoreCase(int num_lines, char *lines[])
{
  /**
   * Ignore blanks when sorting
   * Convert all to lowercase before sorting, then output
   *    lines with original case (original input)
   * Might have to save lowercase lines into array
   *    But how do we then replace them with the original lines?
   * Create new line that will be lowercase version of original line
   * Sort based on this lowercase line
   * Then, we strcpy() original line back in? But how do we know location?
   * After sort, iterate through sorted output (which will be all lowercase),
   *    and strcmp() the lowercase line and the toLower() version of the original line (which we have in a separate array).
   * If they match, then strcpy() the original line into the lowercase line, thus maintaining sorted order
  */

  // printf("\nUnsorted, original case:\n");
  // printLines(num_lines, lines);

  // char **lines_to_ignore = (char **) malloc(num_lines * sizeof(char *));
  // if (lines_to_ignore == NULL) errorVoid();
  // int num_lines_to_ignore = 0, len = 0;

  // char *curr_line = NULL;
  // for (int i = 0; i < num_lines; i++) {
  //   curr_line = *(lines + i);
  //   len = strlen(curr_line);

  //   if (my_lineIsUpper(curr_line)) {
  //     *(lines_to_ignore + num_lines_to_ignore) = (char *) malloc(len * sizeof(char));
  //     strcpy(*(lines_to_ignore + num_lines_to_ignore++), curr_line);
  //     strcpy(curr_line, my_toLower(curr_line));
  //   }
  // }

  /**
   * At this point, lines are unsorted and lowercase
   * After sorting, we will iterate through and compare
   *    lowercase version of original lines to sorted, lowercase lines
   * If there's a match, swap the lines via strcpy()
  */

  // printf("\nUnsorted, lowercase:\n");
  // printLines(num_lines, lines);

  insertionSort(num_lines, lines, "-f");

  // char *sorted_line = NULL;
  // char *original_line = NULL;
  // int ignored_lines_index = 0;

  // printf("\nSorted, lowercase:\n");
  // printLines(num_lines, lines);

  // printf("\nOriginal lines containing uppercase chars:\n");
  // printLines(num_lines_to_ignore, lines_to_ignore);
  
  // for (int i = 0; i < num_lines; i++) {
  //   sorted_line = *(lines + i);
  //   original_line = *(lines_to_ignore + ignored_lines_index);
  // }

  //   if (strcmp(sorted_line, my_toLower(original_line)) == 0) {
  //     strcpy(sorted_line, original_line);
  //     ignored_lines_index++;
  //   }
  // }

  // printf("\nSorted, case ignored:\n");
  // printLines(num_lines, lines);
  
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