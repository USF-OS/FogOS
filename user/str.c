#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "user/user.h"
#include "user/string.h"

int main(void) {
	char buf[128];
	strncpy(buf, "Hello", 128);	
	printf("%s\n", buf);

	strncat(buf, " food", 128 - strlen(buf));
	printf("%s\n", buf);

	char *sub = strstr(buf, "food");
	printf("%s\n", sub);

	sub = strstr(buf, "");
	printf("%s\n", sub);

	sub = strstr(buf, "ayo");
	printf("%s\n", sub);
	
	return 0;
}
