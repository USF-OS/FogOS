#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
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

	sort(argc - 1, arg_vec); // arg_vec gets freed here

	return 0;
}
