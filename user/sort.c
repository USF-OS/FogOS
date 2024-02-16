#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
	const int num_args = argc;
	char *arg_vec[] = argv;
	
	sort(num_args, arg_vec);

	return 0;
}
