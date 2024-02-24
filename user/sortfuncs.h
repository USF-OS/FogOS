#ifndef SORTING_UTILITIES_H
#define SORTING_UTILITIES_H

#define MAX_LINES 1000

typedef struct {
    int unq_flag;
    int rev_flag;
    int num_flag;
    int ig_case_flag;
    int ig_blanks_flag;
} FlagStruct;

FlagStruct processFlags(char *flags[], int num_flags);

int errorInt(void);
void errorVoid(void);
int isFlag(char* flag);
int my_isUpper(const char c);
int my_lineIsUpper(const char* line);
char* my_toLower(char* line);
int compare(const char* s1, const char* s2, char* flag);
void insertionSort(int num_lines, char *lines[], char* flag);
void insertionSortOrig(int num_lines, char *lines[]);
int my_isdigit(char c);
int isNumeric(const char *str);
long parseLong(const char *str);
int compareStringsAsNumbers(const char* a, const char* b);
void insertionSortWithNumeric(int num_lines, char **lines);
void printLines(int num_lines, char *lines[]);
void freeLines(int num_lines, char *lines[]);
void ignoreBlanks(int num_lines, char *lines[]);
void unique(int *num_lines, char *lines[]);
void ignoreCase(int num_lines, char *lines[]);
void numeric(int num_lines, char *lines[]);
void swap(char** a, char** b);
void reverse(int num_lines, char *lines[]);
int reverseCheck(char** flags, int flagCount);

#endif // SORTING_UTILITIES_H
