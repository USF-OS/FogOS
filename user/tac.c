#include "kernel/types.h"   // for using uint
#include "user/user.h"      // for using printf
#include "kernel/fcntl.h"   // for using malloc and free


// separator input from command line can't contain more than 5 spaces

uint init_num_lines = 128;

int has_separator = 0;
int match_start = -1;
int math_line_index = -1;
int match_found = 0;
char needle[100] = {0};


int strStr(char* haystack, char* needle) {
  int needle_len = strlen(needle);
  int last_start = strlen(haystack) - needle_len;

  for (int start = 0; start <= last_start; start++) 
  {
      for (int i = 0; i < needle_len; i++) 
      {
          if (*(needle+i) != *(haystack+start+i)) 
          {
            break;
          }
          if (i == (needle_len-1)) 
          {
            return start;
          }
      }
  }

  return -1;
}

void print_substring(const char *str, int start, int end)
{
  for (int i = start; i <= end; i++)
  {
    printf("%c", str[i]);
  }
}

void
print_lines(char **lines, int num_lines)
{
  if (has_separator == 1) 
  {
     if (match_found == 0) 
     {
        printf("tac: the string is not contained in the input text\n");
        exit(1);
     }
    // 1. print lines[math_line_index] starting from index "match_start" to the end of this line
    print_substring(lines[math_line_index], match_start, strlen(lines[math_line_index])-1);

    // 2. print all lines beginning from (math_line_index+1) to the end of file (the last line_index)
    for (int i = math_line_index+1; i < num_lines; i++) 
    {
      printf("%s", lines[i]);
      free(lines[i]);
    }

    // 3. print all lines from lines[0] to lines[math_line_index-1]
    for (int i = 0; i <= math_line_index-1; i++) 
    {
      printf("%s", lines[i]);
      free(lines[i]);
    }

    // 4. print lines[math_line_index] starting from index 0 to lines[match_start-1]
    print_substring(lines[math_line_index], 0, match_start-1);

    free(lines[math_line_index]);
  }
  else // no separator
  {
    int line_index = num_lines;
    while (--line_index >= 0) 
    {
      printf("%s", lines[line_index]);

      if (lines[line_index] != 0)
      {
        free(lines[line_index]);
      }
    }
  }



}

void
tac(int fd) 
{
  uint old_num_lines = 0;
  uint new_num_lines = init_num_lines;

  char **lines = malloc(new_num_lines * sizeof(char*));

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
    char_read = getline(&line, &sz, fd);
  
    if (char_read <= 0)
    {
      // reach EOF
      break;
    } 
    else if (line_index == (new_num_lines - 1))
    { // the last line of the file read has some text instead of EOF
      // expand the capacity of memory storing lines
      old_num_lines = new_num_lines;
      new_num_lines = old_num_lines * 2;

      new_lines = malloc(new_num_lines * sizeof(char*));

      memcpy(new_lines, lines, (line_index + 1) * sizeof(char*));

      new_lines[line_index] = line; 

      if (lines != 0)
      {
        free(lines);
      }

      lines = new_lines;

    } 
    else 
    {
      lines[line_index] = line; // won't store the line in the lines array if it's EOF
    }
    
    if (has_separator == 1 && match_found == 0)
    { 
      int result = strStr(line, needle);

      if (result != -1)
      {
        match_start = result;
        math_line_index = line_index;
        match_found = 1;
      }
    }
    
    line = 0;
    sz = 0;

    line_index++;
  }

  // print the reversed text
  // if no -s, print and free lines in reversed order
  // if has -s, 

  int line_count = line_index;
  print_lines(lines, line_count);

  if (lines != 0)
  {
    free(lines);
  }
}

int 
main(int argc, char *argv[])
{
  if (argc == 1) 
  {
    fprintf(2, "tac: missing file argument\n");
    exit(1);
  }

  for (int i = 1; i < argc; i++)
  {
    printf("argv: %s\n", argv[i]);
  }

  // if argc is not 2, make sure argc is 4 (make sure quoted string is treated as one argument)
  // after quote string is treated as one argument, if argc is still not 4, print error message and exit
  if (argc != 2) 
  {
    
    int c = 0;
    // 1. go through each current argument, find the first '"' (should be the first char of an argument)
    for (int i = 1; i < argc; i++)
    {
      
      if (argv[i][0] == '"')   // "a
      {
        char *arg = argv[i];  // for holding the string arg

        
        char new_str_arg[100] = {0};
    
        const char *space = " \0";
        // printf("---------------------------\n");
        // printf("arg is: %s\n", arg);
        // printf("new_str_arg is: %s\n", new_str_arg);

        strcpy(new_str_arg, arg);
        strcpy(new_str_arg + strlen(arg), "\0");
        // printf("new_str_arg is: %s\n", new_str_arg);
        //strcpy(new_str_arg + strlen(arg), space);

        // printf("strlen(arg) is: %d\n", strlen(new_str_arg));
        // printf("strlen(new_str_arg) is: %d\n", strlen(new_str_arg));
        // printf("---------------------------\n");


        int arg_start_index = i;

        if (arg_start_index == 1) {
          fprintf(2, "tac: invalid arguments\n");
          exit(1);
        }
        printf("i: %d, str arg is: %s\n", i, arg);
        // if the current argument start with ", search for " at the end of this argument
        // otherwise, move on to the next argument in argv
        // if the close " is at the end of the same argument, no need to change argc and argv
        // if the close " is found at the end of other argument, change argc and argv
        // if the close " is not found in the end of other argument, print error message and exit (invalid string argument)
        while (new_str_arg[strlen(new_str_arg) - 1] != '"')
        {
          printf("new_str_arg[strlen(new_str_arg) - 1] is: %c\n", new_str_arg[strlen(new_str_arg) - 1]);
          i++;

          if (i < argc) 
          { // char* strcpy(char*, const char*);
            printf("----------A-------------------\n");
            printf("argv[0]: %s\n", argv[0]);
            printf("argv[1]: %s\n", argv[1]);
            printf("argv[2]: %s\n", argv[2]);
            printf("argv[3]: %s\n", argv[3]);
            

            //const char *space = " \0";
            printf("strlen(new_str_arg): %d\n", strlen(new_str_arg));
            printf("Before strcpy, i: %d, new_str_arg is: %s\n", i, new_str_arg);

            
            strcpy(new_str_arg + strlen(new_str_arg), space);
            strcpy(new_str_arg + strlen(new_str_arg), argv[i]);

            strcpy(new_str_arg + strlen(new_str_arg) + strlen(argv[i]), "\0");


            
            printf("After strcpy, i: %d, new_str_arg is: %s\n", i, new_str_arg);

            //printf("----------B-------------------\n");
            // printf("argv[0]: %s\n", argv[0]);
            // printf("argv[1]: %s\n", argv[1]);
            // printf("argv[2]: %s\n", argv[2]);
            // printf("argv[3]: %s\n", argv[3]);
            
            c++;
          }
          else
          {
            break;
          }
        }
        printf("arg_start_index: %d\n", arg_start_index);


        argv[arg_start_index] = new_str_arg;
        printf("argv[arg_start_index]: %s\n", argv[arg_start_index]);

        if (arg_start_index == 2 )
        {
          argv[3] = argv[argc - 1];
        }
      }
    }

    
    argc -= c;

    for (int i = 1; i < argc; i++)
    {
      printf("argv: %s\n", argv[i]);
    }

    printf("argc: %d\n", argc);
  }

  // remove this block later (if string argument includes spaces, it will mess up argc)
  if (argc != 2 && argc != 4)
  {
    fprintf(2, "tac: invalid arguments\n");
    exit(1); // not handling reading from stdin for now
  }

  //return 0; // remove later

  int fd;
  const char* file_path;

  if (argc == 2)    // if argc is 2, the second argument must be a fileName. Example: tac fileName.c  
  {
    file_path = argv[1];
  }
  else // argc == 4, example: tac fileName.c -s "main"   ||  tac -s "main" fileName.c
  {                      //   tac fileName.c -s "A B C"  ||  tac -s "A B C" fileName.c      
    // check if -s and a string are contained in the arguments
    //  go through arguemnts one by one, if -s is found, check if the next argument is a "string"
    //  invalid cases:  no -s
    //                  -s is not followed by a "string"
    // if true, search for the fileName argument (if pos of -s is 1/2, pos of file is 3/1; )
    // otherwise, invalid arguments
    int i;
    for (i = 1; i < argc; i++) 
    {
      //int strncmp(const char *p, const char *q, uint n)
      int arg_len = strlen(argv[i]);
      if (arg_len == 2 && strcmp("-s", argv[i]) == 0) 
      {
        // find -s
        // check if argv[i+1] is a string
        printf("i+1: %d, argc is: %d\n", i+1, argc);

        if (i+1 < argc && strlen(argv[i+1]) > 2 
              && argv[i+1][0] == '"' && argv[i+1][strlen(argv[i+1]) - 1] == '"') 
        {
          break;
        } 
        else 
        {
          fprintf(2, "tac: invalid separator (separator argument should be a non-empty quoted string)\n");
          exit(1);
        }
      }
    }

    if (i == argc) 
    {
      fprintf(2, "tac: invalid arguments (missing -s)\n");
      exit(1);
    }

    // arguments contain -s followed by a valid string 
    file_path = (i == 1) ? argv[3] : argv[1];
    has_separator = 1;
    char *str_arg = (i == 1) ? argv[2] : argv[3];
    memcpy(needle, str_arg+1, strlen(str_arg)-2);
  }


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