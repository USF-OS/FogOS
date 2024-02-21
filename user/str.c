#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "user/user.h"
#include "user/string.h"

# define LEN 128

int main(void) {
	// strncpy tests
	/*
	// Buffer overflow
	char buf_terminated[5];
	char buf_overflow[] = "HEHEHE";
	strncpy(buf_terminated, buf_overflow, strlen(buf_overflow));
	printf("%s\n", buf_terminated);
	*/
	
	// strcspn tests
	/*
	char buf[LEN];

	strncpy(buf, "geeks\n for geeks", LEN);
	int len = strcspn(buf, " \t\n\r");
	printf("%d %l\n", len, strlen("geeks"));
	*/

	// strtok tests
	/*
    char strtokstr[] = "first second third";
    char *strtoktoken = strtok(strtokstr, " ");
    printf("%s\n", strtoktoken);
	*/
	
	// strtok_r test
	/*
	char str[] = "Hello, World! Geeks for Geeks.";
    const char outer_delimiters[] = "!.";
    const char inner_delimiters[] = " ,";
 
    char* token;
    char* outer_saveptr = 0;
    char* inner_saveptr = 0;
 
    token = strtok_r(str, outer_delimiters, &outer_saveptr);
 
    while (token != 0) {
        printf("Outer Token: %s\n", token);
 
        char* inner_token = strtok_r(token, inner_delimiters, &inner_saveptr);
 
        while (inner_token != 0) {
            printf("Inner Token: %s\n", inner_token);
            inner_token = strtok_r(0, inner_delimiters, &inner_saveptr);
        }
 
        token = strtok_r(0, outer_delimiters, &outer_saveptr);
    }
    */

    // strsep tests
    /*
    char strsepstr[] = "I love string functions";
    char strsepdelim[] = " ";
    char *strsepptr = strsepstr;
    char *strseptoken = strsep(&strsepptr, strsepdelim);
    
    while (strseptoken != 0) {
        printf("%s\n", strseptoken);
    	strseptoken = strsep(&strsepptr, strsepdelim);
    }
    */

	// scanf tests
	char s[100];
	int result = scanf("%d\n", s);
	printf("%d %d\n", result, s);
	
	/*
	// Uninitialised str ptr
	int in;
	char *str = 0;

	int err = scanf("%d %s\n", str, &in);
	printf("%d %s %d\n", str, in);
	*/

	
	
	return 0;
}
