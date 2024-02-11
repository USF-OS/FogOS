#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "user/user.h"
#include "user/string.h"

int main(void) {
	char buf[128];
	strncpy(buf, "Hello", 128);	
	printf("%s\n", buf);

	int same = strncmp(buf, "Hello", 128);
	printf("%d\n", same);
	same = strncmp(buf, "Hell", 128);
	printf("%d\n", same);
	
	return 0;
}
