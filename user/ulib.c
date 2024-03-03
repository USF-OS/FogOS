#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "user/user.h"
#include "user/crctable.h"

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

uint32 
crc(int fd, int size)
{
	char buffer[1024] = {0};
	char* current_byte = buffer;
	uint32 bytes = 0;
	uint32 checksum = 0;
	uint32 file_size = size;
	uint32 buffer_size = sizeof(buffer);

	// Reads chunks of the file into the buffer in a loop and runs the CRC algorithm on each byte read 
	while (file_size > 0)
	{
		// Handles small files and the last bytes of large files
		if (file_size < 1024) 
		{
			buffer_size = file_size;
		}

		// Reads data from the file into the buffer and checks that the read operation was successful
		bytes = read(fd, buffer, buffer_size);
		if (bytes != buffer_size)
		{
			printf("Problem reading file.\n");
			return -1;
		}

		// Sets the pointer to the beginning of the buffer
		current_byte = buffer;

		// Runs the CRC algorithm on each byte in the buffer
		while (bytes-- > 0)
		{
			checksum = lookup_table[((checksum >> 24) ^ *current_byte++) & 0xFF] ^ (checksum << 8);
		}

		// Keeps track of the remaining unread bytes in the file
		file_size -= buffer_size;
	}

	// Extends the algorithm, using each byte of the original 32-bit size as part of the CRC algorithm
	while (size != 0)
	{
		checksum = lookup_table[((checksum >> 24) ^ size) & 0xFF] ^ (checksum << 8);
		size = size >> 8;
	}
	

	// Inverts the checksum and returns the value
	return ~checksum;
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

char*
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
}

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
