#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/spinlock.h"
#include "kernel/sleeplock.h"
#include "kernel/fs.h"
#include "kernel/file.h"
#include "user/user.h"
#include "kernel/fcntl.h"

#define NULL ((void *) 0)
#define MAX_CODES 256
#define BUFFER_SIZE 1024

char chars[MAX_CODES]; // Array to store characters.
char *codes[MAX_CODES]; // Array of pointers to store codes.

int readLine(int fd, char *buffer, int maxSize) {
    int numRead = 0;
    int totalRead = 0;
    char ch;
    while (totalRead < maxSize - 1) {
        numRead = read(fd, &ch, 1);
        if (numRead == 1) {
            if (ch == '\n') break;
            *buffer++ = ch;
            totalRead++;
        } else if (numRead == 0) {
            if (totalRead == 0) return -1;
            else break;
        } else {
            return -1;
        }
    }
    *buffer = '\0';
    return totalRead;
}

void decodeHuffmanString(int fd, char chars[], char *codes[], int codeCount, char *outputFileName) {
    char *bitBuffer = malloc(BUFFER_SIZE);
    char *decodedString = malloc(BUFFER_SIZE);
    int bitSize = readLine(fd, bitBuffer, BUFFER_SIZE); // Use BUFFER_SIZE directly for consistency.
    if (bitSize > 0) {
        int decodedIndex = 0;
        for (char *token = bitBuffer; *token != '\0';) {
            char *code = malloc(256); // Allocate dynamically for each code.
            int codeIndex = 0;
            while (*token != ' ' && *token != '\0') {
                code[codeIndex++] = *token++;
            }
            code[codeIndex] = '\0'; // Ensure the code is null-terminated.
            if (*token == ' ') token++; // Skip space between codes.
            for (int i = 0; i < codeCount; i++) {
                if (strcmp(code, codes[i]) == 0) {
                    decodedString[decodedIndex++] = chars[i];
                    break; // Found the matching code, break the loop.
                }
            }
            free(code); // Free the allocated memory for the code after use.
        }
        decodedString[decodedIndex] = '\0'; // Null-terminate the decoded string.

        // Proceed with writing the decoded string to the file.
        int outFile = open(outputFileName, O_WRONLY | O_CREATE | O_TRUNC);
        if (outFile != -1) {
            write(outFile, decodedString, strlen(decodedString));
            close(outFile);
        }
    }
    free(bitBuffer); // Free allocated memory.
    free(decodedString);
}

int main(int argc, char *argv[]) {
    if (argc < 3) return 1;
    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        return 1;
    }
    int codeCount = 0;
    char *lineBuffer = malloc(BUFFER_SIZE);
    int lineSize;
    int emptyLineCount = 0;
    while ((lineSize = readLine(fd, lineBuffer, BUFFER_SIZE)) != -1) {
        if (lineSize == 0) {
            emptyLineCount++;
            if (emptyLineCount == 2) break;
            else continue;
        }
        emptyLineCount = 0;
        char *colonPtr = strchr(lineBuffer, ':');
        if (colonPtr != NULL) {
            *colonPtr = '\0';
            if (strcmp(lineBuffer, "~") == 0) {
                chars[codeCount] = '\n';
            } else {
                chars[codeCount] = lineBuffer[0];
            }
            codes[codeCount] = malloc(strlen(colonPtr + 1) + 1); // Allocate memory for code.
            strcpy(codes[codeCount], colonPtr + 1);
            codeCount++;
        }
    }
    decodeHuffmanString(fd, chars, codes, codeCount, argv[2]);
    close(fd);
    for (int i = 0; i < codeCount; i++) {
        free(codes[i]); // Free the allocated memory for each code.
    }
    free(lineBuffer);
    return 0;
}
