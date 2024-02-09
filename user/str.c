#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "user/user.h"
#include "user/strings.h"

int main(void) {
	char buf[128];
	strncpy1(buf, "Hello", 128);	
	printf("%s\n", buf);
	return 0;
}
