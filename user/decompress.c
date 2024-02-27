#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/spinlock.h"
#include "kernel/sleeplock.h"
#include "kernel/fs.h"
#include "kernel/file.h"
#include "user/user.h"
#include "kernel/fcntl.h"
int main(int argc, char *argv[])
{
	decompress(argv[1]);
	printf("1111\n");
	return 0;
}
