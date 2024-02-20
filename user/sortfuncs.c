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

void insertionSortNumeric(int *arr, int n) {
    int i, j, key;
    for (i = 1; i < n; i++) {
        key = arr[i];
        j = i - 1;

        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
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

int my_isdigit(char c) {
    return c >= '0' && c <= '9';
}

// Helper function to check if the first character of a string is numeric
int isNumeric(const char *str) {
    return my_isdigit(str[0]);
}

void
numeric(int num_lines, char *lines[]) {

  int *numericalLines = (int *)malloc(NUM_LINES * sizeof(int));
  char **alphabeticLines = (char **)malloc(NUM_LINES * sizeof(char *));
  int numericCount = 0, alphabeticCount = 0;

  for (int i = 0; i < num_lines; i++) {
    if (isNumeric(lines[i])) {
        numericalLines[numericCount++] = atoi(lines[i]);
    } else {
        alphabeticLines[alphabeticCount++] = lines[i];
    }
  }

  insertionSortNumeric(numericalLines, numericCount);
  insertionSort(alphabeticCount, alphabeticLines);


  for (int i = 0; i < numericCount; i++) {
    printf("%d\n", numericalLines[i]);
  }
  for (int i = 0; i < alphabeticCount; i++) {
    printf("%s\n", alphabeticLines[i]);
  }

  // Clean up
  free(numericalLines);
  free(alphabeticLines);
}
