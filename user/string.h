//string.h
char *strncpy(char *dst, const char *src, uint n);
int strncmp(const char *s1, const char *s2, uint n);
char *strncat(char *restrict s1, const char *restrict s2, uint n);
char *strstr(const char *haystack, const char *needle);
uint strspn(const char *s, const char *charset);
/*
char *strtok(char *restrict str, const char *restrict sep);
char *strtok_r(char *restrict str, const char *restrict sep, char **restrict lasts);
size_t strcspn(const char *s, const char *charset);
char *strsep(char **stringp, const char *delim);
*/

//stdio.h
//int scanf(const char *restrict format, ...);
