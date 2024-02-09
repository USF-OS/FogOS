#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "user/user.h"
#include "user/strings.h"

char
*strncpy1(char *dst, const char *src, uint n)
{
	char *to_ret;

	to_ret = dst;
	while ((*to_ret++ = *src++) && n >= 0)
		n--;

	return to_ret;	
}

int
strncmp1(const char *s1, const char *s2, uint n)
{
	while (*s1 && *s1 == *s2 && n >= 0)
		s1++, s2++, n--;
	return (uchar)*s1 - (uchar)*s2;
}

/*
int
char *strncat1(char *restrict s1, const char *restrict s2, uint n)
{
	s1 += strlen(s1) + 1;					// point to end of str
	while (*s2 && n >= 0) {
		*s1 = *s2;
		s1++, s2++, n--;
	}
	return 0;
}
*/
