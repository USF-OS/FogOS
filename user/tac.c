#include "kernel/types.h"   
#include "user/user.h"      
#include "kernel/fcntl.h"   


// separator input from command line can't contain more than 5 spaces
// separator can't contain ()
// separator must have no more than 50 characters

uint init_num_lines = 128;
int has_separator = 0;
int match_start = -1;
int math_line_index = -1;
int match_found = 0;
char needle[100] = {0};


int search_str(char* haystack, char* needle) {
  int needle_len = strlen(needle);
  int last_start = strlen(haystack) - needle_len;

  for (int start = 0; start <= last_start; start++) 
  {
      for (int i = 0; i < needle_len; i++) 
      {
          if (*(needle + i) != *(haystack + start + i)) 
          {
            break;
          }
          if (i == (needle_len - 1)) 
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
        fprintf(2, "tac: the string is not contained in the input text\n");
        exit(1);
     }

    print_substring(lines[math_line_index], match_start, strlen(lines[math_line_index])-1);

    for (int i = math_line_index+1; i < num_lines; i++) 
    {
      printf("%s", lines[i]);
      free(lines[i]);
    }

    for (int i = 0; i <= math_line_index-1; i++) 
    {
      printf("%s", lines[i]);
      free(lines[i]);
    }

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
    fprintf(2, "tac: malloc failed\n");
    exit(1);
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
      // reach end of file
      break;
    } 
    else if (line_index == (new_num_lines - 1))
    { 
      old_num_lines = new_num_lines;
      new_num_lines = old_num_lines * 2;

      new_lines = malloc(new_num_lines * sizeof(char*));

      if (new_lines == 0) 
      {
        fprintf(2, "tac: malloc failed\n");
        exit(1);
      }

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
      lines[line_index] = line; 
    }
    
    if (has_separator == 1 && match_found == 0)
    { 
      int result = search_str(line, needle);

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

  // if argc is not 2, make sure argc is 4 (make sure quoted string is treated as one argument)
  // after quote string is treated as one argument, if argc is still not 4, print error message and exit
  if (argc != 2) 
  {
    
    int c = 0;

    for (int i = 1; i < argc; i++)
    {
      
      if (argv[i][0] == '"')   
      {
        char *arg = argv[i];  

        char new_str_arg[100] = {0};
    
        strcpy(new_str_arg, arg);
        strcpy(new_str_arg + strlen(arg), "\0");

        int arg_start_index = i;

        if (arg_start_index == 1) {
          fprintf(2, "tac: invalid arguments\n");
          exit(1);
        }

        while (new_str_arg[strlen(new_str_arg) - 1] != '"')
        {
          i++;

          if (i < argc) 
          { 
            strcpy(new_str_arg + strlen(new_str_arg), " \0");
            strcpy(new_str_arg + strlen(new_str_arg), argv[i]);
            strcpy(new_str_arg + strlen(new_str_arg) + strlen(argv[i]), "\0");   

            c++;
          }
          else
          {
            break;
          }
        }

        argv[arg_start_index] = new_str_arg;

        if (arg_start_index == 2 )
        {
          argv[3] = argv[argc - 1];
        }
      }
    }

    argc -= c;
  }

  if (argc != 2 && argc != 4)
  {
    fprintf(2, "tac: invalid arguments\n");
    exit(1);
  }

  int fd;
  const char* file_path;

  if (argc == 2)  
  {
    file_path = argv[1];
  }
  else 
  {                     
    int i;
    for (i = 1; i < argc; i++) 
    {
      //int strncmp(const char *p, const char *q, uint n)
      int arg_len = strlen(argv[i]);
      if (arg_len == 2 && strcmp("-s", argv[i]) == 0) 
      {
        // find -s
        // check if argv[i+1] is a string
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


  fd = open(file_path, 0);
  if (fd < 0) 
  {
    fprintf(2, "tac: cannot open %s\n", file_path);
    exit(1);
  }

  tac(fd);
  close(fd);
  exit(0);
}