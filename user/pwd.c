#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
	char buf[200] = "hello";
	cwd(buf, 200);
	exit(0);
}
