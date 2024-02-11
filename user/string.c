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

	// null-terminates regardless; slightly different from C library
	*walk = '\0'; 

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
	// copies without overriding chars already in s1
	strncpy(s1 + strlen(s1), s2, n);
	return s1;
}

char
*strstr(const char *haystack, const char *needle)
{
	if (!*needle) {
		return (char *)haystack;
	}	

	int substr_len = strlen(needle);

	// const char* shows that func will not change char str
	char *walk = (char *)haystack;
	while (*walk) {
		if (*walk == *needle) {
			if (!strncmp(walk, needle, substr_len)) {
				return walk;
			}
		}
		walk++;
	}
	return 0;
}
