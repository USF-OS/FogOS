#include "kernel/types.h"
#include "user/user.h"
#include "kernel/stat.h"
#include "kernel/fcntl.h"

#define POLY32LE 0xEDB88320

int
main(int argc, char* argv[])
{
	uint32 checksum;
	struct stat metadata;

	char* file_name = argv[1];
	int fd = open(file_name, O_RDONLY);
	fstat(fd, &metadata);

	// Check that the name provided is a valid file name
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

	// Perform the 32-bit CRC
	checksum = crc(fd, metadata.size);
	

	printf("%d %d %s\n", checksum, metadata.size, file_name);

	return 0;
}
