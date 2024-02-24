#include "kernel/types.h"   // for using uint
#include "user/user.h"      // for using printf
#include "kernel/fcntl.h"   // for using malloc and free


void
tac(int fd) 
{
  //printf("tac : fd is %d\n", fd); // fd == 3 when fd represents a fi

  uint num_lines = 128; // can read 128 lines (the last line can have text)
  char **lines = malloc(num_lines * sizeof(char*));
  //printf("lines is %p\n", lines);
  if (lines == 0) {
    printf("tac: malloc for lines failed\n");
  }

  char *line = 0;
  uint sz = 0;

  int line_index = 0;
  int char_read;
  char **new_lines;
  uint old_num_lines = 0;
  uint new_num_lines = num_lines;

  while (1)
  {
    //printf("new_num_lines: %d\n", new_num_lines);
    //printf("line_index: %d\n", line_index);
    //lines[line_index] = malloc(sz);
    //printf("lines[line_index]: %p\n", lines[line_index]);

  
    char_read = getline(&line, &sz, fd);
    // line[char_read] = '\0';
    //printf("char_read: %d\n", char_read);
    //printf("line: %s\n", line);
    
    
    if (char_read <= 0)
    {
      //printf("reached EOF\n");
      //printf("line_index: %d, char_read: %d\n", line_index, char_read);
      // reach EOF
      break;

    } 
    else if (line_index == (new_num_lines-1)){ // the last line of the file read is doesn't have EOF
      // expand the capacity of memory storing lines
      //printf("LAST LINE\n");
      //printf("line_index: %d\n", line_index);
      // 
      old_num_lines = new_num_lines;
      new_num_lines = old_num_lines * 2;

      new_lines = malloc(new_num_lines * sizeof(char*));


      //memcpy(new_lines, lines, line_index+1);
      
      //printf("new_line is storing:\n");
      for (int i = 0; i <= line_index; i++) 
      {
        if (i == line_index) {
          new_lines[line_index] = line; 
        } else {
          new_lines[i] = lines[i];
        }
        
        //memcpy(new_lines[i], lines[i], sizeof(char*));
        //printf("%s\n", new_lines[i]);
      }
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
      //printf("lines[line_index]: %p\n", lines[line_index]);
    }

    
    line = 0;
    sz = 0;
    //printf("Line %d, read %d character(s):\n%s\n\n", line_index, char_read, lines[line_index]);
    line_index++;
  }
   
  //line_index--;
  //printf("line_index: %d\n", line_index);

  //printf("\n\n-----------------Reversed text is-----------------: \n");
  while (--line_index >= 0) 
  {
    //printf("line_index: %d\n", line_index);
    //printf("Line %d, read %d character(s):\n%s\n\n", line_index, char_read, lines[line_index]);
    printf("%s", lines[line_index]);

    if (lines[line_index] != 0)
    {
      free(lines[line_index]);
    }
    //line_index--;
  }

  if (lines != 0)
  {
    free(lines);
  }
}

int 
main(int argc, char *argv[])
{
  if(argc <= 1)
  {
    printf("exiting as argc<=1\n");
    exit(1); // not handling reading from stdin for now
  }

  int i, fd;
  // print each argument after "tac"
  // (later change this to opening each argument (which should be a file) after "tac")
  for(i = 1; i < argc; i++)
  {
    //printf("argc[%d] is: %s\n", i, argv[i]);
    fd = open(argv[i], 0); //from user.h: int open(const char*, int);. file path = argv[i], omode = 0
    if(fd < 0) 
    {
      fprintf(2, "cat: cannot open %s\n", argv[i]);
      exit(1);
    }
  }

  //printf("fd is: %d\n", fd);
  tac(fd);
  close(fd);
  exit(0);
}