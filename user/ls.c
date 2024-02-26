#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "user/colors.h"

char*
fmtname(char *path)
{
  static char buf[DIRSIZ+1];
  char *p;

  // Find first character after last slash.
  for(p=path+strlen(path); p >= path && *p != '/'; p--)
    ;
  p++;

  // Return blank-padded name.
  if(strlen(p) >= DIRSIZ)
    return p;
  memmove(buf, p, strlen(p));
  memset(buf+strlen(p), ' ', DIRSIZ-strlen(p));
  return buf;
}



void help() {
  printf("LS MANUAL PAGE\n");
  printf("-------\n");
  printf("Flags:\n");
  printf("-t: prints based off type\n");
  printf("-sz: prints based off size\n");
  printf("-c: prints the files in a nice set of columns (ONLY FOR DIR)\n");
  printf("-fun: prints files in a fun set of colors (ONLY FOR DIR)\n");
  printf("-rand: prints files in random colors\n");
  printf("-i: prints the index of the file\n");
}

void
ls(char *path, char *flag)
{
  char buf[512], *p;
  int fd;
  struct dirent de;
  struct stat st;
  int valid = 0;

  //default color
  int color = CYAN;

  if((fd = open(path, 0)) < 0){
    fprintf(2, "ls: cannot open %s\n", path);
    return;
  }

  if(fstat(fd, &st) < 0){
    fprintf(2, "ls: cannot stat %s\n", path);
    close(fd);
    return;
  }



  switch(st.type){
  case T_DEVICE:
  case T_FILE:
    //NORMAL
    if (strcmp(flag, "-") == 0) {
        valid = 1;
        printf("\033[%dm%s \033[0m\n", color, fmtname(path));
    }
    //LONG
    if (strcmp(flag, "-l") == 0) {
       valid = 1;
       printf("\033[%dm%s %d %d %l\033[0m\n", color, fmtname(path), st.type, st.ino, st.size);
    }
    //SIZE FLAG
    if (strcmp(flag, "-sz") == 0) {
       valid = 1;
       printf("\033[%dm%s %d\033[0m\n", color, fmtname(path), st.size);
    }

    //TYPE
    if (strcmp(flag, "-t") == 0) {
       valid = 1;
       printf("\033[%dm%s %d\033[0m\n", color, fmtname(path), st.type);
    }

    //INDEX FLAG
    if (strcmp(flag, "-i") == 0) {
       valid = 1;
       printf("\033[%dm%s %d \033[0m\n", color, fmtname(path), st.ino);
    }

    //RAND
    if (strcmp(flag, "-rand") == 0) {
       valid = 1;
       long rand = random() / 1000000;

       if (rand < 0) {
         rand = -rand;
       }

       if (rand % 5 == 0) {
         color = BLUE;
       } else if (rand % 5 == 1) {
         color = RED;
       } else if (rand % 5 == 2) {
         color = GREEN;
       } else if (rand % 5 == 3) {
         color = MAGENTA;
       } else if (rand % 5 == 4) {
         color = ORANGE;
       } else {
         color = WHITE;
       }
       printf("\033[%dm%s \033[0m\n", color, fmtname(path));
    }
    break;

  case T_DIR:
    if(strlen(path) + 1 + DIRSIZ + 1 > sizeof buf){
      printf("ls: path too long\n");
      break;
    }
    strcpy(buf, path);
    p = buf+strlen(buf);
    *p++ = '/';
    while(read(fd, &de, sizeof(de)) == sizeof(de)){
      if(de.inum == 0)
        continue;
      memmove(p, de.name, DIRSIZ);
      p[DIRSIZ] = 0;
      if(stat(buf, &st) < 0){
        printf("ls: cannot stat %s\n", buf);
        continue;
      }


      //SIZE FLAG
      if (strcmp(flag,"-sz") == 0) {
        valid = 1;
        if (st.size > 0 && st.size <= 1000) {
            color = BLUE;
            printf("\033[%dm%s %d\033[0m\n", color, fmtname(buf), st.size);
        } else if (st.size > 1000 && st.size <= 10000) {
            color = CYAN;
            printf("\033[%dm%s %d\033[0m\n", color, fmtname(buf), st.size);
        } else if (st.size > 10000 && st.size <= 100000) {
            color = MAGENTA;
            printf("\033[%dm%s %d\033[0m\n", color, fmtname(buf), st.size);
        } else if (st.size == 0) {
            color = WHITE;
            printf("\033[%dm%s %d\033[0m\n", color, fmtname(buf), st.size);
        } else {
            color = GREEN;
            printf("\033[%dm%s %d\033[0m\n", color, fmtname(buf), st.size);
        }
      }

      //TYPE FLAG
      if (strcmp(flag, "-t") == 0) {
        valid = 1;
        if (st.type == 0) {
            color = GREEN;
            printf("\033[%dm%s %d\033[0m\n", color, fmtname(buf), st.type);
        } else if (st.type == 1) {
            color = CYAN;
            printf("\033[%dm%s %d\033[0m\n", color, fmtname(buf), st.type);
        } else if (st.type == 2) {
            color = WHITE;
            printf("\033[%dm%s %d\033[0m\n", color, fmtname(buf), st.type);
        } else if (st.type == 3) {
            color = GREEN;
            printf("\033[%dm%s %d\033[0m\n", color, fmtname(buf), st.type);
        } else {
            printf("\033[%dm%s %d\033[0m\n", color, fmtname(buf), st.type);
        }
      }

      //LONG LISTING FLAG
      if (strcmp(flag, "-l") == 0) {
          valid = 1;
          color = WHITE;
          printf("\033[%dm%s %d %d %d\033[0m\n", color, fmtname(buf), st.type, st.ino, st.size);
      }
      
      //INDEX FLAG
      if (strcmp(flag, "-i") == 0) {
	  valid = 1;
          printf("\033[%dm%s %d \033[0m\n", color, fmtname(buf), st.ino);
      }

      //FUN FLAG
      if (strcmp(flag, "-fun") == 0) {
          valid = 1;
          if (st.ino % 6 == 1) {
              color = RED;
              printf("\033[%dm%s \033[0m\n", color, fmtname(buf));
          } else if (st.ino % 6 == 2) {
              color = DARK_YELLOW;
              printf("\033[%dm%s \033[0m\n", color, fmtname(buf));
          } else if (st.ino % 6 == 3) {
              color = ORANGE;
              printf("\033[%dm%s \033[0m\n", color, fmtname(buf));
          } else if (st.ino % 6 == 4) {
              color = GREEN;
              printf("\033[%dm%s \033[0m\n", color, fmtname(buf));
          } else if (st.ino % 6 == 5) {
              color = BLUE;
              printf("\033[%dm%s \033[0m\n", color, fmtname(buf));
          } else {
              color = MAGENTA;
              printf("\033[%dm%s \033[0m\n", color, fmtname(buf));
          }
      }

      //COLUMN FLAG
      if (strcmp(flag, "-c") == 0) {
         valid = 1;
         if (st.ino % 5 != 0) {
            printf("%s", fmtname(buf));
         } else {
            printf("\n%s", fmtname(buf));
         }
       }

      //RAND
      if (strcmp(flag, "-rand") == 0) {
         valid = 1;
         long rand = random() / 1000000;

         if (rand < 0) {
           rand = -rand;
         }

         if (rand % 5 == 0) {
            color = BLUE;
         } else if (rand % 5 == 1) {
            color = RED;
         } else if (rand % 5 == 2) {
            color = GREEN;
         } else if (rand % 5 == 3) {
            color = MAGENTA;
         } else if (rand % 5 == 4) {
            color = ORANGE;
         } else {
            color = WHITE;
         }

         printf("\033[%dm%s \033[0m\n", color, fmtname(buf));
      }

      //NORMAL FLAG
      if (strcmp(flag, "-") == 0) {
         valid = 1;
         if (st.type == 1) {
            color = BLUE;
            printf("\033[%dm%s \033[0m\n", color, fmtname(buf));
         } else {
            printf("%s\n", fmtname(buf));
         }
      }

    }
    break;
  }

  if (strcmp(flag, "-c") == 0) {
    printf("\n");
  }

  if (valid != 1) {
    printf("Invalid Flag\n");
    help();
  }
  close(fd);
}



int
main(int argc, char *argv[])
{
  int i;
  int j;
  int count = 0;
  int checked = 0;
  char flag[128];
 
  strcpy(flag, "-");
  if(argc < 2){
    ls(".", "-");
    exit(0);
  }

  for(i=1; i<argc; i++) {
    //locate flag
    if (checked != 1) {
      for(j=1; j<argc;j++) {
          if(argv[j][0] == '-') {
             strcpy(flag, argv[j]);
	     count++;	   
          }
	  checked = 1;
      }
    }

    if (count >= 2 && checked == 1) {
       printf("Too many flags detected. Please use one flag at a time\n");
       return 0;
    }

    //help flag
    if (strcmp(flag, "-h") == 0) {
       help();
       exit(0);
    }

   //only ls flags
    if (argv[i][0] != '-') {
      ls(argv[i], flag);
    } else if (argc == 2) {
      ls(".", flag);
    } else {
    }
  }

  exit(0);
}
