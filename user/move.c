#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "user/user.h"

char buf[2048];

int
main(int argc, char *argv[])
{
	int source;
	
	if (argc <= 1){
		printf("Usage: rm source destination...\n");
		exit(1);
	} 

	if ((source = open(argv[1], O_RDONLY)) == 0) {
		printf("Unable to open source file");
		exit(1);
	}

	dup(source);
	exit(1);
}
