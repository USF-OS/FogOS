#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "user/user.h"

/*
* Usage: move /source_file /directory_destination
* Takes in a source_file and moves it to the directory_destination.
* Uses link and unlink to create a reference file pointing to the data
* of the source file, moving the reference file into the directory, 
* and unlinking the original file.
*/

int
main(int argc, char *argv[])
{
	int source;
	
	if (argc <= 1){
		fprintf(2, "Usage: /move file_source dir_destination...\n");
		exit(1);
	} 

	if ((source = open(argv[1], O_RDONLY)) == 0) {
		fprintf(2, "move: Unable to open source file %s\n", argv[1]);
		exit(1);
	}

	char *destination = malloc(strlen(argv[1]) + strlen(argv[2]) + 2);
	strcpy(destination, argv[2]);
	destination[strlen(argv[2])] = '/';
	strcpy(destination + strlen(argv[2]) + 1, argv[1]);
	if (link(argv[1], destination) < 0) {
		fprintf(2, "move: link failed %s\n", destination);
		exit(1);
	}
	unlink(argv[1]);
	free(destination);
	exit(0);
}
