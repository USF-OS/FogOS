#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define MAX_LINE_LENGTH 512

// Function to extract a range of characters.
void cutc(int fd, int start, int end) {
    char line[MAX_LINE_LENGTH];
    int n;

    // Read from the file descriptor until there's nothing left to read.
    while ((n = read(fd, line, sizeof(line))) > 0) {
 
        // Check the range
        if (end >= n) {
            fprintf(2, "cut: specified range exceeds the line length\n");
            exit(1);
        }

        // Iterate through each character in the buffer.
        for (int i = 0; i < n; i++) {
            // Check if the current character is within the specified range.
            if (i >= start && i <= end) {
                // Write the character to standard output.
                write(1, &line[i], 1);
            }
        }
        // Write a newline character after processing each buffer.
        write(1, "\n", 1);
    }
    // Check for read error.
    if (n < 0) {
        fprintf(2, "cut: read error\n");
        exit(1);
    }
}

// Function to extract fields separated by a delimiter.
void cutf(int fd, char delimiter, int field) {
    char line[MAX_LINE_LENGTH];
    int n, currentField = 0, i = 0;

    // Read from the file descriptor until there's nothing left to read.
    while ((n = read(fd, line, sizeof(line))) > 0) {
        // Iterate through each character in the buffer.
        for (i = 0; i < n; i++) {
            // Check if the current character is the delimiter.
            if (line[i] == delimiter) {
                // Increment field count upon finding the delimiter.
                currentField++;
                // Break if we have read the required field.
                if (currentField > field) {
                    break;
                }
            } else if (currentField == field) {
                // Write the character to standard output if it's in the required field.
                write(1, &line[i], 1);
            }
        }
        // Write a newline character after processing each buffer.
        write(1, "\n", 1);
    }
    // Check for read error.
    if (n < 0) {
        fprintf(2, "cut: read error\n");
        exit(1);
    }
}

int main(int argc, char *argv[]) {
    int fd;

    // Check for the correct number of arguments.
    if (argc <= 1) {
        fprintf(2, "Usage: cut -c range [file] or cut -f field -d delim [file]\n");
        exit(1);
    }

    // Handling the -c flag for character ranges.
    if (strcmp(argv[1], "-c") == 0) {
        // Ensure proper usage with the correct number of arguments.
        if (argc < 4) {
            fprintf(2, "cut: -c option requires two arguments(Example: cut -c 1 3)\n");
	        exit(1);
        }
         
        int start = atoi(argv[2]); // Convert start position from string to int.
        int end = atoi(argv[3]);   // Convert end position from string to int.
        
        // Validate the range
        if (start <= 0 || end <= 0 || start > end) {
            fprintf(2, "cut: invalid range specified\n");
            exit(1);
        }
        // Adjusting the start and end to 0-based index
        start--;
        end--;

        fd = (argc == 5) ? open(argv[4], 0) : 0; // Open file if provided.

        cutc(fd, start, end); // Call the function to cut characters.
        if (fd != 0) close(fd); // Close the file descriptor if it was opened.
    } 
    
    // Handling the -f flag for fields.
    else if (strcmp(argv[1], "-f") == 0 && strcmp(argv[3], "-d") == 0) {
        // Ensure proper usage with the correct number of arguments.
        if (argc < 5) {
            fprintf(2, "cut: incorrect usage of -f and -d\n");
            exit(1);
        }
        
        int field = atoi(argv[2]) - 1;  // Convert field number from string to int.
        char delimiter = argv[4][0];    // Get the delimiter character.
	    fd = (argc == 6) ? open(argv[5], 0) : 0; // Open file if provided.
        cutf(fd, delimiter, field); // Call the function to cut fields.
        
        if (fd != 0) close(fd); // Close the file descriptor if it was opened.
    } else {
        // Print error message if arguments do not match expected patterns.
        fprintf(2, "cut: invalid arguments\n");
        exit(1);
    }

    exit(0);
}
