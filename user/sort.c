#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"
#include "user/sortfuncs.h"

int
main(int argc, char *argv[])
{
    int num_flags = 0;
    char **flags = (char **)malloc(argc * sizeof(char *));
    if (flags == NULL) errorInt();

    getFlags(argc, argv, &num_flags, flags);

    char *file_name = NULL;
    for (int i = 1; i < argc; i++) {
        if (argv[i][0] != '-') {
            file_name = argv[i];
            break;
        }
    }

    int fd = 0;
    if (file_name) {
        fd = open(file_name, O_RDONLY);
        if (fd < 0) {
            printf("sort: cannot open %s\n", file_name);
            return -1;
        }
    }
    
    if (sort(fd, num_flags, flags) != 0) {
        printf("Error: Sorting failed\n");
        if (fd > 0) {
            close(fd);
        }
        return 1;
    }

    if (fd > 0 && close(fd) < 0) { 
        printf("Warning: Failed to close file descriptor properly\n");
    }
    return 0;
}
