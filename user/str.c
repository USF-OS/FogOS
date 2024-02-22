#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "user/user.h"
#include "user/string.h"

# define LEN 16

int main(void) {
	char buf[LEN];
	
	// strncpy
	printf("strncpy:\n");
	strncpy(buf, "Hello", LEN);
	printf("%s\n", buf);

	// strncmp
	printf("\nstrncmp:\n");
	
	if (!strncmp(buf, "Hello", LEN))
		printf("%s matches Hello\n", buf);
		
	if (strncmp(buf, "World", LEN))
		printf("%s does not match World\n", buf);

	// strncat
	printf("\nstrncat:\n");
	strncat(buf, " World12345678910", LEN - strlen(buf));
	printf("%s\n", buf);

	// strstr
	printf("\nstrstr:\n");
	char *substr = strstr(buf, "");
	printf("%s\n", substr);

	substr = strstr(buf, "Hell");
	printf("%s\n", substr);

	substr = strstr(buf, "123");
	printf("%s\n", substr);	

	substr = strstr(buf, "Yell");
	printf("%s\n", substr);	

	printf("\nstrspn:\n");

	// strspn
	int len = strspn(buf, "Hel");
	printf("len: %d, should be 4\n", len);

	len = strspn(buf, "hel");
	printf("len: %d, should be 0\n", len);

	printf("\nstrcspn:\n");

	// strcspn
	len = strcspn(buf, "Hel");
	printf("len: %d, should be 0\n", len);

	len = strcspn(buf, "hel");
	printf("len: %d, should be 1\n", len);

	len = strcspn(buf, " ");
	printf("len: %d, should be 5\n", len);

	// strtok
	printf("\nstrtok:\n");
    char strtokstr[] = "first second third";
    char *strtoktoken = strtok(strtokstr, " ");
    printf("%s\n", strtoktoken);

	// strtok_r
	printf("\nstrtok_r:\n");
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

    // strsep
    printf("\nstrsep:\n");
    char strsepstr[] = "I love string functions";
    char strsepdelim[] = " ";
    char *strsepptr = strsepstr;
    char *strseptoken = strsep(&strsepptr, strsepdelim);
    
    while (strseptoken != 0) {
        printf("%s\n", strseptoken);
    	strseptoken = strsep(&strsepptr, strsepdelim);
    }

	// scanf tests
    printf("\nscanf:\n");
	int num1, num2;
	printf("Input two integers(space separated, can be negative): ");
	int result = scanf("%d %d", &num1, &num2);
	printf("%d %d %d\n", result, num1, num2);

	char *uninitialised = 0;
	char *initialised = malloc(128);
	printf("Input two strings(space separated): ");
	result = scanf("%s %s", initialised, uninitialised);
	printf("%d %s %s\n", result, initialised, uninitialised);
	
	return 0;
}
