#ifndef SORTING_UTILITIES_H
#define SORTING_UTILITIES_H

typedef struct {
    int unq_flag;
    int rev_flag;
    int num_flag;
    int ig_case_flag;
    int ig_blanks_flag;
} FlagStruct;

FlagStruct processFlags(char*[], int);
int errorInt(void);
void errorVoid(void);
int isFlag(char*);
int my_isUpper(const char);
int my_lineIsUpper(const char*);
char* my_toLower(char*);
int compare(const char*, const char*, char*);
void insertionSort(int, char*[], char*);
void insertionSortOrig(int, char*[]);
int my_isdigit(char);
int isNumeric(const char*);
long parseLong(const char*);
int compareStringsAsNumbers(const char*, const char*);
void insertionSortWithNumeric(int, char*[]);
void getFlags(int, char*[], int*, char*[]);
void printLines(int, char*[]);
void freeLines(int, char*[]);
void ignoreBlanks(int, char*[]);
void unique(int*, char*[]);
void ignoreCase(int, char*[]);
void numeric(int, char*[]);
void swap(char*[], char*[]);
void reverse(int, char*[]);

#endif // SORTING_UTILITIES_H
