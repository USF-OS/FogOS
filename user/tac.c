#include "kernel/types.h"   // for using uint
#include "user/user.h"      // for using printf
#include "kernel/fcntl.h"   // for using malloc and free


// struct Line {
//   uint index;
//   char *content;
// }; 

void
tac(int fd) 
{
  //printf("tac : fd is %d\n", fd); // fd == 3 when fd represents a fi

  char *lines[1024];

  char *line = 0;
  uint sz = 0;

  int line_index = 0;
  int char_read;

  while (1) 
  {
    //printf("line_index: %d\n", line_index);
    //lines[line_index] = malloc(sz);
    //printf("lines[line_index]: %p\n", lines[line_index]);
  
    char_read = getline(&line, &sz, fd);
    line[char_read] = '\0';
    //printf("line: %s\n", line);
    lines[line_index] = line;
    if (char_read <= 0)
    {
      //printf("line_index: %d, char_read: %d\n", line_index, char_read);
      // reach EOF
      break;
    }
    
    line = 0;
    sz = 0;
    //printf("Line %d, read %d character(s):\n%s\n\n", line_index, char_read, lines[line_index]);
    line_index++;
  }
   
  line_index--;
  //printf("line_index: %d\n", line_index);


  while (line_index >= 0) 
  {
    //printf("Line %d, read %d character(s):\n%s\n\n", line_index, char_read, lines[line_index]);
    printf("%s", lines[line_index]);

    if (lines[line_index] != 0)
    {
      free(lines[line_index]);
    }
    line_index--;
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
    printf("argc[%d] is: %s\n", i, argv[i]);
    fd = open(argv[i], 0); //from user.h: int open(const char*, int);. file path = argv[i], omode = 0
    if(fd < 0) 
    {
      fprintf(2, "cat: cannot open %s\n", argv[i]);
      exit(1);
    }
  }

  printf("fd is: %d\n", fd);
  tac(fd);
  close(fd);
  exit(0);
}