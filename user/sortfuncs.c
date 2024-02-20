#define NULL ((void *) 0)
#define NUM_LINES 1000

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
printLines(int num_lines, char *lines[])
{
  for (int i = 0; i < num_lines; i++) {
    printf("%s\n", *(lines + i));
  }
}

void
freeLines(int fd, int argc, char *argv[], int num_lines, char *lines[])
{
  for (int i = 0; i < argc; i++) {
    free(*(argv + i));
  }
  free(argv);
  argv = NULL;

  for (int i = 0; i < num_lines; i++) {
    free(*(lines + i));
  }
  free(lines);
  lines = NULL;

  close(fd);
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
  insertionSort(alphabeticCount, alphabeticLines);



  for (int i = 0; i < numericCount; i++) {
    printf("%s\n", numericalLines[i]);
  }
  for (int i = 0; i < alphabeticCount; i++) {
    printf("%s\n", alphabeticLines[i]);
  }

  // Clean up
  free(numericalLines);
  free(alphabeticLines);
}
