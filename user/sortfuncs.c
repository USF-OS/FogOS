#define NULL ((void *) 0)

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
printLines(int fd, int num_lines, char *lines[])
{
  for (int i = 0; i < num_lines; i++) {
    printf("%s\n", *(lines + i));
    free(*(lines + i));
  }

  free(lines);
  close(fd);
}
