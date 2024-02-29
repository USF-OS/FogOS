#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "user/user.h"

/*
* Given a buffer and size, calls a system call cwd 
* that writes the current working directory that is 
* found in myproc()->cwd to a user space buffer.
*/

int
main(int argc, char *argv[])
{
	char *buf = malloc(200);
	if (cwd(buf, 200) < 0) {
		fprintf(2, "pwd: unable to print out current working directory\n");
		exit(1);
	}
	printf("The current working directory is: %s\n", buf);
	exit(0);
}
