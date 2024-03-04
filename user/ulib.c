#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "user/user.h"

//
// wrapper so that it's OK if main() does not call exit().
//
void
_main()
{
  extern int main();
  main();
  exit(0);
}

char*
strcpy(char *s, const char *t)
{
  char *os;

  os = s;
  while((*s++ = *t++) != 0)
    ;
  return os;
}

int
strcmp(const char *p, const char *q)
{
  while(*p && *p == *q)
    p++, q++;
  return (uchar)*p - (uchar)*q;
}

uint
strlen(const char *s)
{
  int n;

  for(n = 0; s[n]; n++)
    ;
  return n;
}

void*
memset(void *dst, int c, uint n)
{
  char *cdst = (char *) dst;
  int i;
  for(i = 0; i < n; i++){
    cdst[i] = c;
  }
  return dst;
}

char*
strchr(const char *s, char c)
{
  for(; *s; s++)
    if(*s == c)
      return (char*)s;
  return 0;
}

/*char*
gets(char *buf, int max)
{
  int i, cc;
  char c;

  for(i=0; i+1 < max; ){
    cc = read(0, &c, 1);
    if(cc < 1)
      break;
    buf[i++] = c;
    if(c == '\n' || c == '\r')
      break;
  }
  buf[i] = '\0';
  return buf;
}*/

int
stat(const char *n, struct stat *st)
{
  int fd;
  int r;

  fd = open(n, O_RDONLY);
  if(fd < 0)
    return -1;
  r = fstat(fd, st);
  close(fd);
  return r;
}

int
atoi(const char *s)
{
  int n;

  n = 0;
  while('0' <= *s && *s <= '9')
    n = n*10 + *s++ - '0';
  return n;
}

void*
memmove(void *vdst, const void *vsrc, int n)
{
  char *dst;
  const char *src;

  dst = vdst;
  src = vsrc;
  if (src > dst) {
    while(n-- > 0)
      *dst++ = *src++;
  } else {
    dst += n;
    src += n;
    while(n-- > 0)
      *--dst = *--src;
  }
  return vdst;
}

int
memcmp(const void *s1, const void *s2, uint n)
{
  const char *p1 = s1, *p2 = s2;
  while (n-- > 0) {
    if (*p1 != *p2) {
      return *p1 - *p2;
    }
    p1++;
    p2++;
  }
  return 0;
}

void *
memcpy(void *dst, const void *src, uint n)
{
  return memmove(dst, src, n);
}

char*
gets(char *buf, int max)
{
  max = fgets(buf, max, 0);
  return buf;
}

int
fgets(char *buf, int max, int fd)
{
  int i, cc;
  char c;
	
  for(i=0; i+1 < max; ){
	cc = read(fd, &c, 1);
	if(cc < 1)
	  break;
	buf[i++] = c;
	if(c == '\n' || c == '\r')
	  break;
  }
  buf[i] = '\0';
  return i;
}

int
getline(char **lineptr, uint *sz, int fd)
{
  //initialize buffer if not already initialized (size = 0)
  if (*lineptr == 0 || *sz == 0) { // prof used && said lineptr = 0
     *sz = 128;
     *lineptr = (char *)malloc(*sz);
     //malloc error handling
     if (*lineptr == NULL) {
         return -1;
     }
  }
  int counter = 0;
  //defrencing line pointer and then can acess buf
  char *buf = *lineptr;
  
  //while we have more to read
  while(buf[counter-1] != '\n'){
  	//read into the buffer using fgets
  	int max = fgets(buf+counter, *sz-counter, fd);
  	
  	//track the total amount of bytes read
  	counter += max;
  	
  	//if we hit EOF or error --> stop, return number of bytes read or -1 for error
  	if (max == 0){
  	  	return counter;
  		
  	}else if (max < 0){
  		return -1;
  		
  	}else if(buf[counter-1] == '\n'){
  		return counter;
  		
  	}else{
  		// Resize the buffer (double the size)
        int newSize = *sz * 2;
        char *newBuffer = (char *)malloc(newSize);

        if (newBuffer == NULL) {
            // Memory allocation error
            return -1;
        }

        // Copy existing data to the new buffer
        memcpy(newBuffer, *lineptr, *sz);

        free(*lineptr);
        *lineptr = newBuffer;
        *sz = newSize;	
        buf = *lineptr;
  	}
  }
  return 0;
}

