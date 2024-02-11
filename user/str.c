#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "user/user.h"
#include "user/string.h"

# define LEN 128

int main(void) {
	char buf[LEN];

	strncpy(buf, "geeks for geeks", LEN);
	int len = strcspn(buf, "geek");
	printf("%d\n", len);
	return 0;
}
