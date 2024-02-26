/**
 * @file sortfuncs.c A collection of helper functions used for 'sort'
 * @author Shyon Ghahghahi
 * @author Amin Joseph
*/

#include "kernel/fcntl.h"
#include "kernel/types.h"
#include "user/user.h"

#define NULL ((void *) 0)
#define MAX_LINES 1000

/**
 * Struct to store program option flags.
 * 
 * This structure is used to represent the state of various options in a program, 
 * where each flag indicates whether a specific feature or behavior is enabled.
 * 
 * @param ig_blanks_flag Indicates if blank spaces should be ignored.
 * @param ig_case_flag Indicates if case sensitivity should be ignored.
 * @param rev_flag Indicates if the order should be reversed.
 * @param num_flag Indicates if numerical sorting is enabled.
 * @param unq_flag Indicates if only unique entries should be considered.
 * @param help_flag Indicates if help or usage information should be displayed.
 */
typedef struct {
  int ig_blanks_flag;
  int ig_case_flag;
  int rev_flag;
  int num_flag;
  int unq_flag;
  int help_flag;
} FlagStruct;

/**
 * Sets flags
 * @return struct with flags set/unset
*/
FlagStruct
processFlags(int num_flags, char *flags[])
{
  FlagStruct fs = { 0 }; // Initialize all flags to 0

  for (int i = 0; i < num_flags; i++) {
    if      (strcmp(flags[i], "-b") == 0) fs.ig_blanks_flag = 1;
    else if (strcmp(flags[i], "-f") == 0) fs.ig_case_flag = 1;
    else if (strcmp(flags[i], "-n") == 0) fs.num_flag = 1;
    else if (strcmp(flags[i], "-r") == 0) fs.rev_flag = 1;
    else if (strcmp(flags[i], "-u") == 0) fs.unq_flag = 1;
    else if (strcmp(flags[i], "-h") == 0) fs.help_flag = 1;
  }

  return fs;
}

/**
 * @return 1 for memory allocation error.
*/
int
errorInt()
{
  printf("Memory allocation error.\n");
  return 1;
}

/**
 * @brief Prints error message and returns.
*/
void
errorVoid()
{
  printf("Memory allocation error.\n");
  return;
}

/**
 * @return 0 if user input is valid flag, other number if not.
*/
int
isFlag(char* flag)
{
  return (
    strcmp(flag, "-n") == 0 ||
    strcmp(flag, "-r") == 0 ||
    strcmp(flag, "-u") == 0 ||
    strcmp(flag, "-b") == 0 ||
    strcmp(flag, "-f") == 0 ||
    strcmp(flag, "-h") == 0
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
 * @return 0 if all lowercase or 1 if at least 1 uppercase character
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
  int len = strlen(line) + 1;
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

/**
 * Compares two strings based on specific criteria indicated by a flag.
*/
int
compare(const char* s1, const char* s2, char* flag)
{
  if (strcmp(flag, "-f") == 0) {
    char *s1_lower = (char *) malloc((strlen(s1) + 1) * sizeof(char));
    char *s2_lower = (char *) malloc((strlen(s2) + 1) * sizeof(char));
    /* DO NOT FORGET TO FREE THESE */
    if (s1_lower == NULL || s2_lower == NULL) errorInt();

    strcpy(s1_lower, s1);
    strcpy(s2_lower, s2);

    s1_lower = my_toLower(s1_lower);
    s2_lower = my_toLower(s2_lower);

    return strcmp(s1_lower, s2_lower);

  } else if (strcmp(flag, "-b") == 0) {
    while (*s1 == ' ' || *s1 == '\t') s1++;
    while (*s2 == ' ' || *s2 == '\t') s2++;
  }

  return strcmp(s1, s2);
}

/**
 * @brief Good for small data input (up to 1000 lines)
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

/**
 * Regular insertion sort algo for soritng lines
 * that dont have any specified flags.
 * 
 * Sorts according to ascii value of strings
*/
void
insertionSortOrig(int num_lines, char *lines[])
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

/**
 * Checks of if first char of line is a digit
*/
int
my_isdigit(char c)
{
  return c >= '0' && c <= '9';
}

/**
 * @brief Checks if the first character of a string is numeric
*/
int
isNumeric(const char *str)
{
  return my_isdigit(str[0]);
}

/**
 * @brief Manually parses a long from a string
*/
long
parseLong(const char *str)
{
  long value = 0;
  while (my_isdigit(*str)) {
    value = value * 10 + (*str - '0');
    str++;
  }
  return value;
}

/**
 * Used by insertionSortWithNumeric() to compare the 
 * numerical strings as ints/numbers
*/
int
compareStringsAsNumbers(const char* a, const char* b)
{
  if (my_isdigit(a[0]) && my_isdigit(b[0])) {
    long numA = parseLong(a);
    long numB = parseLong(b);

    if (numA < numB) return -1;
    if (numA > numB) return 1;
  }

  return strcmp(a, b);
}

/**
 * Sorts according to lines that begin with an int
 * or lines that are only filled with ints
 * 
 * Seperate line of chars numbers are passed in and then 
 * temporarily converted to compare in an insertion sort 
 * algo that updates the structure, which is then mem copied
 * into the main array "lines"
 * 
*/
void
insertionSortWithNumeric(int num_lines, char **lines)
{
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

/**
 * Parses through command line arguemtns and looks
 * for flags, which are determined by "-" before a char.
 * Limits flag count to 100
*/
void
getFlags(int argc, char *argv[], int* num_flags, char *flags[])
{
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      flags[*num_flags] = argv[i];
      (*num_flags)++;
      if (*num_flags >= 100) {
        printf("Maximum number of flags reached (100).\n");
        break;
      }
    }
  }
}

/**
 * @brief Print *lines[]
*/
void
printLines(int num_lines, char *lines[])
{
  for (int i = 0; i < num_lines; i++) {
    printf("%s\n", *(lines + i));
  }
}

/**
 * @brief Free *lines[]
*/
void
freeLines(int num_lines, char *lines[])
{
  for (int i = 0; i < num_lines; i++) {
    free(*(lines + i));
  }
  free(lines);
  lines = NULL;
}

/**
 * 1) Advance line pointer to first alphanumeric character
 * 2) Disregard leading blanks when sorting
*/
void
ignoreBlanks(int num_lines, char *lines[])
{
  insertionSort(num_lines, lines, "-b");
}

/**
 * 1) Sort lines
 * 2) Compare adjacent lines, ignoring duplicates
 * Removes duplicate lines after sorting
 * Called by using -u flag 
*/
void
unique(int *num_lines, char *lines[])
{
  insertionSortOrig(*num_lines, lines);

  int num_unique_lines = 0;
  char **unique_lines = (char **) malloc(*num_lines * sizeof(char *));
  if (unique_lines == NULL) errorVoid();

  int runner = 1;
  char *curr_line = NULL, *next_line = NULL;
  while (runner < *num_lines) {
    curr_line = *(lines + runner - 1);
    next_line = *(lines + runner);

    int len = strlen(curr_line) + 1;
    *(unique_lines + num_unique_lines) = (char *) malloc(len * sizeof(char));
    if (*(unique_lines + num_unique_lines) == NULL) errorVoid();

    strcpy(*(unique_lines + num_unique_lines++), curr_line);

    while (strcmp(curr_line, next_line) == 0) {
      next_line = *(lines + ++runner);
    }
    runner++;
  }

  *num_lines = num_unique_lines;
  memcpy(lines, unique_lines, *num_lines * sizeof(char *));

  freeLines(num_unique_lines, unique_lines);
}

/**
 * Ignores cases in the sorting process
 * Converts the line/string into lowercase and then sorts
 * Called by using the -f flag
*/
void
ignoreCase(int num_lines, char *lines[])
{
  insertionSort(num_lines, lines, "-f");
}

/**
 * Sorts according to the numerical value of each line 
 * or sorts the first digit in a line that contains chars
 * Called by using the -n flag 
*/
void
numeric(int num_lines, char *lines[])
{
  char **numericalLines = (char **)malloc(MAX_LINES * sizeof(char *));
  char **alphabeticLines = (char **)malloc(MAX_LINES * sizeof(char *));
  if (numericalLines == NULL || alphabeticLines == NULL) errorVoid();

  int numericCount = 0, alphabeticCount = 0;

  for (int i = 0; i < num_lines; i++) {
    if (isNumeric(lines[i])) {
      numericalLines[numericCount++] = lines[i];
    } else {
      alphabeticLines[alphabeticCount++] = lines[i];
    }
  }

  insertionSortWithNumeric(numericCount, numericalLines);
  insertionSortOrig(alphabeticCount, alphabeticLines);

  memcpy(lines, alphabeticLines, alphabeticCount * sizeof(char *));
  // Continue with numerical lines
  memcpy(lines + alphabeticCount, numericalLines, numericCount * sizeof(char *));

  // Clean up
  free(numericalLines);
  free(alphabeticLines);
}

/**
 * @brief Swaps indeces for reversing
*/
void
swap(char** a, char** b)
{
  char* temp = *a;
  *a = *b;
  *b = temp;
}

/**
 * Simply reverses the list of sorted lines
 * Called with the -r flag
*/
void
reverse(int num_lines, char *lines[])
{
  insertionSortOrig(num_lines, lines);

  int start = 0;
  int end = num_lines - 1;

  while (start < end) {
    swap(&lines[start], &lines[end]);
    start++;
    end--;
  }
}

/**
 * Prints the help page for the sort utility.
 *
 * Includes information about:
 *  - instructions
 *  - flags
 *  - limitations
*/
void
help()
{
  uint size = 128;
  char *line = NULL;

  // int fd = open("../docs/sort.txt", O_RDONLY);
  int fd = open("docs/sort.txt", O_RDONLY);
  printf("%d\n", fd);
  while (1) {
    if (getline(&line, &size, fd) <= 0) break;
    printf("%s\n", line);
  }
  close(fd);
}
