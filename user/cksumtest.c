#include "kernel/fcntl.h"
#include "kernel/types.h"
#include "user/user.h"


int
main(void)
{
	int status;
	char* buf[3];
	buf[0] = "cksum";

	char short_buf[25] = {[0 ... 24] = 'a'};
	char long_buf[3000] = {[0 ... 2999] = 'a'};
	//printf("%s", long_buf);

	/* Create test files */
	printf("Creating test files...\n\n");
	int fd1 = open("empty.txt", O_RDWR | O_CREATE);
	int fd2 = open("short.txt", O_RDWR | O_CREATE);
	int fd3 = open("long.txt",  O_RDWR | O_CREATE);

	/* Fill the files */
	write(fd2, short_buf, sizeof(short_buf));
	
	for (int i = 0; i < 35; i++)
	{
		write(fd3, long_buf, sizeof(long_buf));
	}

	/* Close the files */
	close(fd1);
	close(fd2);
	close(fd3);

	/* Create a child process to test the empty file */
	if (fork() == 0)
	{
		buf[1] = "empty.txt";
		printf("Empty File Test (cksum empty.txt):\nActual:\t  ");
		exec(buf[0], buf);
		return 0;
	}
	else
	{
		wait(&status);
		printf("Expected: 4294967295 0 empty.txt\n");
		printf("Valid:\t  -1 0 empty.txt\n\n");
		printf("Note:\t4294967295 = -1 in binary\n");
		printf("This will be fixed when unsigned ints are added to printf\n\n");
	}

	/* Create a child process to test the short file */
	if (fork() == 0)
	{
		buf[1] = "short.txt";
		printf("Short File Test (cksum short.txt):\nActual:\t  ");
		exec(buf[0], buf);
		return 0;
	}
	else
	{
		wait(&status);
		printf("Expected: 970868420 25 short.txt\n\n");
	}

	/* Create a child process to test the long file */
	if (fork() == 0)
	{
		buf[1] = "long.txt";
		printf("Long File Test (cksum long.txt):\nActual:\t  ");
		exec(buf[0], buf);
		return 0;
	}
	else
	{
		wait(&status);
		printf("Expected: 1909244717 105000 long.txt\n\n");
	}

	/* Create a child process to test multiple files */
	if (fork() == 0)
	{
		buf[1] = "short.txt";
		buf[2] = "long.txt";
		printf("Multiple File Test (cksum short.txt long.txt):\nActual:\n");
		exec(buf[0], buf);
		return 0;
	}
	else
	{
		wait(&status);
		printf("Expected:\n970868420 25 short.txt\n1909244717 105000 long.txt\n\n");
	}

	/* Create a child process to test a directory */
	if (fork() == 0)
	{
		buf[1] = ".";
		printf("Directory Test (cksum .):\nActual:\t  ");
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
		printf("Device Test (cksum console):\nActual:\t  ");
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
		printf("Non-Existent File Test (cksum non-existent.txt):\nActual:\t  ");
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
