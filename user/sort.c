#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
	char **arg_vec = (char **) malloc(argc - 1 * sizeof(char *));

	for (int i = 0; i + 1 < argc; i++) {
		*(arg_vec + i) = (char *) malloc(strlen(*(argv + i + 1)) + 1);
		if (*(arg_vec + i) == NULL) {
			printf("Memory allocation error.\n");
			return -1;
		}

		strcpy(*(arg_vec + i), *(argv + i + 1));
	}

	sort(argc - 1, arg_vec);

	return 0;
}
