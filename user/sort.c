#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"


//#include "user/sortfuncs.h"


//This should be called from sortfuncs.h
void 
getFlags(int argc, char *argv[], char** flags, int* flagCount) {
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] == '-') {
            flags[*flagCount] = argv[i]; 
            (*flagCount)++;
            
            if (*flagCount >= 100) { 
                printf("Maximum number of flags reached (100).\n");
                break;
            }
        }
    }
}


int
main(int argc, char *argv[])
{	
	
	int fd = 0;
	char **flags = (char **)malloc(argc * sizeof(char *));
    int num_flags = 0;
	char *file_name = NULL;

	getFlags(argc, argv, flags, &num_flags);

    for (int i = 1; i < argc; i++) {
    	if (argv[i][0] != '-') {
        	file_name = argv[i];
     		break;
        }
    }

	if (file_name) {
		fd = open(file_name, O_RDONLY);
	} else {
		fd = 0;
	}
	
	char **arg_vec = (char **) malloc((argc - 1) * sizeof(char *));
	int len;

	for (int i = 0; i + 1 < argc; i++) {
		len = strlen(*(argv + i + 1)) + 1;
		*(arg_vec + i) = (char *) malloc(len * sizeof(char));
		if (*(arg_vec + i) == NULL) {
			printf("Memory allocation error.\n");
			return -1;
		}

		strcpy(*(arg_vec + i), *(argv + i + 1));
	}
	
	sort(argc - 1, arg_vec, fd, flags, num_flags);

	if (fd != 0) close(fd);

	return 0;
}
