#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "user/user.h"
#include "user/string.h"

# define LEN 128

int main(void) {
	int d[10];
	int error = scanf("%d\n", d);
	printf("%d %d\n", error, *d);

	/*
	char buf[LEN];

	strncpy(buf, "geeks for geeks", LEN);
	int len = strcspn(buf, "geek");
	printf("%d\n", len);

	// strtok_r test
	char str[] = "Hello, World! Geeks for Geeks.";
    const char outer_delimiters[] = "!.";
    const char inner_delimiters[] = " ,";
 
    char* token;
    char* outer_saveptr = 0;
    char* inner_saveptr = 0;
 
    token = strtok_r(str, outer_delimiters, &outer_saveptr);
 
    while (token != 0) {
        printf("Outer Token: %s\n", token);
 
        char* inner_token = strtok_r(
            token, inner_delimiters, &inner_saveptr);
 
        while (inner_token != 0) {
            printf("Inner Token: %s\n", inner_token);
            inner_token = strtok_r(0, inner_delimiters, &inner_saveptr);
        }
 
        token = strtok_r(0, outer_delimiters, &outer_saveptr);
    }
    */
    
	return 0;
}
