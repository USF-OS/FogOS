#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

#define MAX_LINE_LENGTH 512

void cutc(int fd, int start, int end) {
    char line[MAX_LINE_LENGTH];
    int n;

    while ((n = read(fd, line, sizeof(line))) > 0) {
        for (int i = 0; i < n; i++) {
            if (i >= start && i <= end) {
                write(1, &line[i], 1);
            }
        }
        write(1, "\n", 1);
    }
    if (n < 0) {
        fprintf(2, "cut: read error\n");
        exit(1);
    }
}

void cutf(int fd, char delimiter, int field) {
    char line[MAX_LINE_LENGTH];
    int n, currentField = 0, i = 0;

    while ((n = read(fd, line, sizeof(line))) > 0) {
        for (i = 0; i < n; i++) {
            if (line[i] == delimiter) {
                currentField++;
                if (currentField > field) {
                    break;
                }
            } else if (currentField == field) {
                write(1, &line[i], 1);
            }
        }
        write(1, "\n", 1);
    }
    if (n < 0) {
        fprintf(2, "cut: read error\n");
        exit(1);
    }
}

int main(int argc, char *argv[]) {
    int fd;

    if (argc <= 1) {
        fprintf(2, "Usage: cut -c range [file] or cut -f field -d delim [file]\n");
        exit(1);
    }

    if (strcmp(argv[1], "-c") == 0) {
        if (argc < 4) {
            fprintf(2, "cut: incorrect usage of -c\n");
            exit(1);
        }
        int start = atoi(argv[2]) - 1;
        int end = atoi(argv[3]) - 1;
        fd = (argc == 5) ? open(argv[4], 0) : 0;

        cutc(fd, start, end);
        if (fd != 0) close(fd);
    } else if (strcmp(argv[1], "-f") == 0 && strcmp(argv[2], "-d") == 0) {
        if (argc < 5) {
            fprintf(2, "cut: incorrect usage of -f and -d\n");
            exit(1);
        }
        int field = atoi(argv[3]) - 1;
        char delimiter = argv[4][0];
        fd = (argc == 6) ? open(argv[5], 0) : 0;

        cutf(fd, delimiter, field);
        if (fd != 0) close(fd);
    } else {
        fprintf(2, "cut: invalid arguments\n");
        exit(1);
    }
    
    exit(0);
}
