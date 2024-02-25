#include "kernel/types.h"
#include "user/user.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"

int
main(int argc, char* argv[])
{
	uint32 checksum;
	struct stat metadata;

	// Gets the file name from argv, opens the file, and retrieves the metadata
	char* file_name = argv[1];
	int fd = open(file_name, O_RDONLY);
	fstat(fd, &metadata);

	// Checks that the name provided is a valid file name
	if (metadata.type == 1)
	{
		printf("cksum: %s: Is a directory\n", file_name);
		return -1;
	}
	else if (metadata.type == 3)
	{
		printf("cksum: %s: Is a device\n", file_name);
		return -1;
	}

	// Calculates the 32-bit CRC checksum
	checksum = crc(fd, metadata.size);
	
	// Prints the checksum, the file size, and the file name to the console
	printf("%d %d %s\n", checksum, metadata.size, file_name);

	return 0;
}
