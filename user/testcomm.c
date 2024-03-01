#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"

//testing comm with two sorted files and no flags
void comm_noflags() {
	char *cmd[] = { "/comm", "text1.txt", "text2.txt", 0 };
	exec(cmd[0], cmd);
}

//comm with -1 flag (1st column omitted)
void comm_flag1() {
	char *cmd[] = { "/comm", "-1", "text1.txt", "text2.txt", 0 };
	exec(cmd[0], cmd);
}

//comm with -2 flag (2nd column omitted)
void comm_flag2() {
	char *cmd[] = { "/comm", "-2", "text1.txt", "text2.txt", 0 };
	exec(cmd[0], cmd);
}

//comm with -3 flag (3rd column omitted)
void comm_flag3() {
	char *cmd[] = { "/comm", "-3", "text1.txt", "text2.txt", 0 };
	exec(cmd[0], cmd);
}

//testing no args
void comm_noargs() {
	char *cmd[] = { "/comm", 0 };
	exec(cmd[0], cmd);
}

//test non-existent files
void invalid_files() {
	char *cmd[] = { "/comm", "hello.txt", "world.txt", 0 };
	exec(cmd[0], cmd);
}

int main(void) {
	//run 1 test at a time 
	
	comm_noflags();

	//comm_flag1();

	//comm_flag2();

	//comm_flag3();

	//comm_noargs();

	//invalid_files();
	
	return 0;
}
