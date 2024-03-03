#include "kernel/fcntl.h"
#include "kernel/types.h"
#include "user/user.h"


int
main(void)
{
	int status;
	char* buf[3];
	buf[0] = "cksum";

	/* Create an empty file */
	int fd = open("empty.txt", O_RDONLY | O_CREATE);
	close(fd);

	/* Create a child process to test the empty file */
	if (fork() == 0)
	{
		buf[1] = "empty.txt";
		printf("Empty (cksum empty.txt):\nActual:\t  ");
		exec(buf[0], buf);
		return 0;
	}
	else
	{
		wait(&status);
		printf("Expected: 4294967295 0 empty.txt\n");
		printf("Valid:\t  -1 0 empty.txt\n");
		printf("Note:\n4294967295 = -1 in binary\n");
		printf("This will be fixed when unsigned ints are added to printf\n\n");
	}

	/* Create a child process to test the short file */
	if (fork() == 0)
	{
		buf[1] = "README.md";
		printf("Short (cksum README.md):\nActual:\t  ");
		exec(buf[0], buf);
		return 0;
	}
	else
	{
		wait(&status);
		printf("Expected: 32786460 34 README.md\n\n");
	}

	/* Create a child process to test the long file */
	if (fork() == 0)
	{
		buf[1] = "usertests";
		printf("Long (cksum usertests):\nActual:\t  ");
		exec(buf[0], buf);
		return 0;
	}
	else
	{
		wait(&status);
		printf("Expected: 1302825311 182416 usertests\n\n");
	}

	/* Create a child process to test multiple files */
	if (fork() == 0)
	{
		buf[1] = "zombie";
		buf[2] = "kill";
		printf("Multiple (cksum zombie kill):\nActual:\n");
		exec(buf[0], buf);
		return 0;
	}
	else
	{
		wait(&status);
		printf("Expected:\n638060132 33160 zombie\n522381205 33744 kill\n\n");
	}

	/* Create a child process to test a directory */
	if (fork() == 0)
	{
		buf[1] = ".";
		printf("Directory (cksum .):\nActual:\t  ");
		exec(buf[0], buf);
		return 0;
	}
	else
	{
		wait(&status);
		printf("Expected: cksum: .: Is a directory\n\n");
	}

	/* Create a child process to test a device */
	if (fork() == 0)
	{
		buf[1] = "console";
		printf("Device (cksum console):\nActual:\t  ");
		exec(buf[0], buf);
		return 0;
	}
	else
	{
		wait(&status);
		printf("Expected: cksum: console: Is a device\n\n");
	}

	/* Create a child process to test a non-existent file */
	if (fork() == 0)
	{
		buf[1] = "non-existent.txt";
		printf("Non-Existent (cksum non-existent.txt):\nActual:\t  ");
		exec(buf[0], buf);
		return 0;
	}
	else
	{
		wait(&status);
		printf("Expected: cksum: non-existent.txt: No such file or directory\n");
	}

	return 0;
}
