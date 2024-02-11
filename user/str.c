#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "user/user.h"
#include "user/string.h"

# define LEN 128

int main(void) {
	char buf[LEN];

	strncpy(buf, "i am", LEN);
	int len = strspn(buf, "xyz");
	printf("%d\n", len);
	return 0;
}
