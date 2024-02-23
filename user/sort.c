#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{	
	/**
	 * Error check here
	*/
	
	
	// This means we're reading from stdin
	// via a pipe -> "ls | sort"
	if (argc <= 1) {
		// Reading from stdin withoug flags
	}

	/**
	 * Check argv for file
	 * If no file, we're reading from stdin (fd 0) via pipe
	 * If file, open to get fd and send to sort()
	*/

	
	char **arg_vec = (char **) malloc((argc - 1) * sizeof(char *));
	int len;

	// Must open file somewhere here and pass to sort()
	// on line 48

	for (int i = 0; i + 1 < argc; i++) {
		len = strlen(*(argv + i + 1)) + 1;
		*(arg_vec + i) = (char *) malloc(len * sizeof(char));
		if (*(arg_vec + i) == NULL) {
			printf("Memory allocation error.\n");
			return -1;
		}

		strcpy(*(arg_vec + i), *(argv + i + 1));
	}

	/**
	 * Change sort args to include file descriptor
	 * That means we must open file here instead of sort() in uilb.c
	 * Can check if reading from stdin if argc <= 1
	*/
	
	sort(argc - 1, arg_vec, fd); // arg_vec gets freed here

	return 0;
}
