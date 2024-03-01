#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/spinlock.h"
#include "kernel/sleeplock.h"
#include "kernel/fs.h"
#include "kernel/file.h"
#include "user/user.h"
#include "kernel/fcntl.h"

#define MAX_CODES 256
#define BUFFER_SIZE 1024
#define NULL ((void *) 0)

typedef struct {
    char ch;
    char code[256];
} HuffmanCode;

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

void decodeHuffmanString(int fd, HuffmanCode codes[], int codeCount, char *outputFileName) {
    char *bitBuffer=malloc(BUFFER_SIZE);
    char *decodedString=malloc(BUFFER_SIZE);
    int bitSize = readLine(fd, bitBuffer, sizeof(bitBuffer));
    if (bitSize > 0) {
        int decodedIndex = 0;
        for (char *token = bitBuffer; *token != '\0';) {
            char code[256] = {0};
            int codeIndex = 0;
            while (*token != ' ' && *token != '\0') {
                code[codeIndex++] = *token++;
            }
            if (*token == ' ') token++;
                        for (int i = 0; i < codeCount; i++) {
                            if (strcmp(code, codes[i].code) == 0) {
                                decodedString[decodedIndex++] = codes[i].ch;
                                break;
                            }
                        }
                    }
                    decodedString[decodedIndex] = '\0';
                    int outFile = open(outputFileName, O_WRONLY | O_CREATE | O_TRUNC);
                    if (outFile == -1) {
                        return;
                    }
                    write(outFile, decodedString, strlen(decodedString));
                    close(outFile);
                }
            }


int main(int argc, char *argv[])
{
	if(argc<2)return 1;
	int fd = open(argv[1], O_RDONLY);
	    if (fd == -1) {
	        return 1;
	    }
	    HuffmanCode codes[MAX_CODES];
	    int codeCount = 0;
	    char *lineBuffer=malloc(BUFFER_SIZE);
	    int lineSize;
	    int emptyLineCount = 0;
	    while ((lineSize = readLine(fd, lineBuffer, sizeof(lineBuffer))) != -1) {
	        if (lineSize == 0) {
	            emptyLineCount++;
	            if (emptyLineCount == 2) break;
	            else continue;
	        }
	        emptyLineCount = 0;
	        char *colonPtr = strchr(lineBuffer, ':');
	        if (colonPtr != NULL) {
	            *colonPtr = '\0';
	            codes[codeCount].ch = lineBuffer[0];
	            strcpy(codes[codeCount].code, colonPtr + 1);
	            codeCount++;
	        }
	    }
	   decodeHuffmanString(fd, codes, codeCount, argv[2]);
	    close(fd);
	for (int i = 0; i < codeCount; i++) {
        printf("Character: %c, Code: %s\n", codes[i].ch, codes[i].code);
    }
	    return 0;
}
