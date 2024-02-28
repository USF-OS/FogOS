#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"
#include "user/user.h"

char buf[2048];

/*
* Usage: copy /source_file /destination_file
* Opens the source_file for reading, copies over content 
* to a string buffer which is then written to the destination file.
*/

int
main(int argc, char *argv[])
{
	int source, destination, n;
	
	if (argc <= 1){
		fprintf(2, "Usage: /copy file_source file_destination\n");
		exit(1);
	} 

	if ((source = open(argv[1], O_RDONLY)) == 0) {
		fprintf(2, "copy: unable to open source file: %s", argv[1]);
		exit(1);
	}

	if ((destination = open(argv[2], O_WRONLY)) == 0) {
		fprintf(2, "copy: unable to open destination file: %s", argv[2]);
		exit(1);
	}

	while((n = read(source, buf, sizeof(buf))) > 0) {
		if (write(destination, buf, n) != n) {
			fprintf(2, "copy: unable to copy to destination file: %s from source file %s", argv[2], argv[1]);
			exit(1);
		}
	}
	if(n < 0) {
		printf("Unable to read source file");
		exit(1);
	}

	close(source);
	close(destination);
	exit(0);
}
