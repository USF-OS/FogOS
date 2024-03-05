#include "kernel/types.h"
#include "user/user.h"
#include "kernel/fcntl.h"
#include "user/sha1.h"
#include <stdint.h>

int main(void) {
    int fd;
    char *filename = "input.txt"; // Change to your file's name or pass it as an argument
    char fileContent[1024]; // Buffer for file content
    uint8_t digest[SHA1_HASH_SIZE];
    char hash_str[41];

    // Open the file
    fd = open(filename, O_RDONLY);
    if (fd < 0) {
        printf("Failed to open file\n");
        exit(1);
    }

    // Read from the file
    int bytesRead = read(fd, fileContent, sizeof(fileContent) - 1); // Leave space for null terminator
    if (bytesRead < 0) {
        printf("Failed to read file\n");
        close(fd);
        exit(1);
    }
    fileContent[bytesRead] = '\0'; // Null terminate the string

    // Close the file
    close(fd);

    // Call the SHA-1 hashing function on the file content
    sha1sum(digest, (const uint8_t*)fileContent, strlen(fileContent));

    // Convert the resulting SHA-1 hash into a hexadecimal string
    sha1tostring(hash_str, digest);

    // Print the file content and its SHA-1 hash
    printf("File content: %s\n", fileContent);
    printf("SHA-1 Hash: %s\n", hash_str);

    exit(0);
}
