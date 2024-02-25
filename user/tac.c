#include "kernel/types.h"   // for using uint
#include "user/user.h"      // for using printf
#include "kernel/fcntl.h"   // for using malloc and free

uint init_num_lines = 128;

int has_separator = 0;
int match_start = -1;
int math_line_index = -1;
int match_found = 0;
char needle[50] = {0};


int strStr(char* haystack, char* needle) {
  printf("haystack: %s\n", haystack);
  printf("needle: %s\n", needle);
    
  int needle_len = strlen(needle);
  int last_start = strlen(haystack) - needle_len;

  printf("needle_len: %d\n", needle_len);
  printf("last_start: %d\n", last_start);

  for (int start = 0; start <= last_start; start++) {
      for (int i = 0; i < needle_len; i++) {
          if (*(needle+i) != *(haystack+start+i)) {
            break;
          }
          if (i == (needle_len-1)) {
            return start;
          }
      }
  }

  return -1;
}

void
tac(int fd) 
{
  //printf("tac : fd is %d\n", fd); // fd == 3 when fd represents a fi

  //uint num_lines = 128; // can read 128 lines (the last line can have text)
  uint old_num_lines = 0;
  uint new_num_lines = init_num_lines;

  char **lines = malloc(new_num_lines * sizeof(char*));
  //printf("lines is %p\n", lines);

  if (lines == 0) 
  {
    printf("tac: malloc for lines failed\n");
  }

  char *line = 0;
  uint sz = 0;

  int line_index = 0, char_read = 0;
  char **new_lines;
  
  while (1)
  {
    //printf("new_num_lines: %d\n", new_num_lines);
    //printf("line_index: %d\n", line_index);
    //lines[line_index] = malloc(sz);
    //printf("lines[line_index]: %p\n", lines[line_index]);

    char_read = getline(&line, &sz, fd);

    //printf("char_read: %d\n", char_read);
    //printf("line: %s\n", line);
    
    
    if (char_read <= 0)
    {
      //printf("reached EOF\n");
      //printf("line_index: %d, char_read: %d\n", line_index, char_read);
      // reach EOF
      break;

    } 
    else if (line_index == (new_num_lines - 1)){ // the last line of the file read has some text instead of EOF
      // expand the capacity of memory storing lines
      //printf("LAST LINE\n");
      //printf("new_num_lines: %d\n", new_num_lines);
      //printf("line_index: %d\n", line_index);

      old_num_lines = new_num_lines;
      new_num_lines = old_num_lines * 2;

      new_lines = malloc(new_num_lines * sizeof(char*));


      //memcpy(new_lines, lines, line_index+1);
      
      //printf("new_line is storing:\n");
      // for (int i = 0; i <= line_index; i++) 
      // {
      //   if (i == line_index) {
      //     new_lines[line_index] = line; 
      //   } else {
      //     new_lines[i] = lines[i];
      //   }
        
      //   //memcpy(new_lines[i], lines[i], sizeof(char*));
      //   //printf("%s\n", new_lines[i]);
      // }

      memcpy(new_lines, lines, (line_index + 1) * sizeof(char*));

      new_lines[line_index] = line; 

      //printf("new_line is storing:\n");
      //for (int i = 0; i <= (new_num_lines-1); i++) 
      //{
        //printf("index %d: %s", i, new_lines[i]);
      //}
      //printf("%s\n", new_lines[i]);
      //printf("finished printing new_line\n");

      if (lines != 0)
      {
        free(lines);
      }

      lines = new_lines;

    } else {
      //printf("line: %p\n", line);
      //printf("line_index: %d\n", line_index);
      lines[line_index] = line; // won't store the line in the lines array if it's EOF
      //printf("else: line_index: %d, lines[line_index]: %s", line_index, lines[line_index]);
    }

    // printf("line_index: %d\n", line_index);
    // printf("has_separator: %d\n", has_separator);
    // printf("match_found: %d\n", match_found);
    // printf("needle: %s\n", needle);
    // printf("match_start: %d\n", match_start);
    // printf("math_line_index: %d\n", math_line_index);
    // printf("match_found: %d\n", match_found);
    
    if (has_separator == 1 && match_found == 0)
    {
      printf("has_separator == 1 && match_found == 0\n");
      
      int result = strStr(line, needle);
      printf("result: %d\n", result);
      if (result != -1)
      {
        match_start = result;
        math_line_index = line_index;
        match_found = 1;

        printf("match_start: %d\n", match_start);
        printf("math_line_index: %d\n", math_line_index);
        printf("match_found: %d\n", match_found);
      }
    }

    printf("-------------------------------------------------------\n");
    
    line = 0;
    sz = 0;
    //printf("Line %d, read %d character(s):\n%s\n\n", line_index, char_read, lines[line_index]);
    line_index++;
  }
   
  //printf("line_index: %d\n", line_index);

  //printf("\n\n-----------------Reversed text is-----------------: \n");
  // print the reversed text
  // if no -s, print and free lines in reversed order
  // if has -s, 
  while (--line_index >= 0) 
  {
    //printf("line_index: %d\n", line_index);
    //printf("Line %d, read %d character(s):\n%s\n\n", line_index, char_read, lines[line_index]);
    printf("%s", lines[line_index]);

    if (lines[line_index] != 0)
    {
      free(lines[line_index]);
    }

  }

  if (lines != 0)
  {
    free(lines);
  }
}

int 
main(int argc, char *argv[])
{
  printf("argc: %d\n", argc);

  if (argc == 1) {
    fprintf(2, "tac: missing file argument\n");
    exit(1);
  }

  if(argc != 2 && argc != 4)
  {
    fprintf(2, "tac: invalid arguments\n");
    exit(1); // not handling reading from stdin for now
  }

  int fd;
  const char* file_path;

  if (argc == 2)    // Example: tac fileName.c  
  {
    file_path = argv[1];
  }
  else // argc == 4, example: tac fileName.c -s "main"   ||  tac -s "main" fileName.C
  {
    // check if -s and a string are contained in the arguments
    //  go through arguemnts one by one, if -s is found, check if the next argument is a "string"
    //  invalid cases:  no -s
    //                  -s is not followed by a "string"
    // if true, search for the fileName argument (if pos of -s is 1/2, pos of file is 3/1; )
    // otherwise, invalid arguments
    int i;
    for (i = 1; i < argc; i++) {
      //int strncmp(const char *p, const char *q, uint n)
      int arg_len = strlen(argv[i]);
      if (arg_len == 2 && strcmp("-s", argv[i]) == 0) {
        // find -s
        printf("argv[%d] is: %s\n", i, argv[i]);
        printf("argv[%d] first char is: %c\n", i+1, argv[i+1][0]);
        printf("argv[%d] last char is: %c\n", i+1, argv[i+1][strlen(argv[i+1]) - 1]);
        
        // check if argv[i+1] is a string
        if (i + 1 < argc && strlen(argv[i+1]) > 2 
              && argv[i+1][0] == '"' && argv[i+1][strlen(argv[i+1]) - 1] == '"') 
        {
          printf("argv[%d] is a String: %s\n", i+1, argv[i+1]);
          break;
        } else {
          fprintf(2, "tac: invalid separator (separator argument should be a non-empty quoted string)\n");
          exit(1);
        }
      }
    }

    if (i == argc) {
      fprintf(2, "tac: invalid arguments (missing -s)\n");
      exit(1);
    }

    // arguments contain -s followed by a valid string 
    file_path = (i == 1) ? argv[3] : argv[1];
    has_separator = 1;
    char *str_arg = (i == 1) ? argv[2] : argv[3];
    memcpy(needle, str_arg+1, strlen(str_arg)-2);
  }


  // open the fileName
  fd = open(file_path, 0); //from user.h: int open(const char*, int);. file path = argv[i], omode = 0
  if (fd < 0) 
  {
    fprintf(2, "tac: cannot open %s\n", file_path);
    exit(1);
  }

  tac(fd);
  close(fd);
  exit(0);
}