#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "user/user.h"
#include "user/string.h"

char
*strncpy(char *dst, const char *src, uint n)
{
	char *walk = dst;
	while ((*walk++ = *src++) && n > 0)
		n--;

	*walk = '\0'; 	// null-terminate regardless

	return dst;	
}

int
strncmp(const char *s1, const char *s2, uint n)
{
	while (*s1 && *s1 == *s2 && n >= 0)
		s1++, s2++, n--;
	return (uchar)*s1 - (uchar)*s2;
}

char 
*strncat(char *restrict s1, const char *restrict s2, uint n)
{
	strncpy(s1 + strlen(s1), s2, n);
	return s1;
}

