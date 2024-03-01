#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fcntl.h"

/*
*Prints the unique lines from two sorted files and common lines from both into 3 columns.
*1st column contains lines unique to the first file
*2nd column contains lines unique to the second file
*3rd column conatins lines common to both
*Run /testcomm for tests (stored in testcomm.c) and to run comm: /comm [optional flag] file1 file2
*/
void comm(const char *path1, const char *path2, int flag) {
	char *line1 = ((void *) 0);
	char *line2 = ((void *) 0);
	uint len1 = 0;
	uint len2 = 0;
	int file1 = open(path1, O_RDONLY);
	int file2 = open(path2, O_RDONLY);

	if (file1 == -1 || file2 == -1) {
		fprintf(2, "Error opening file.\n");
	}
	
	int r1 = getline(&line1, &len1, file1); 
	int r2 = getline(&line2, &len2, file2); 

	while (1) {
		if (r1 <= 0 || r2 <= 0) {
			break;
		}
		int cmp = strcmp(line1, line2);
		
		//line is unique to file 1
		if (cmp < 0) {				
			if (flag != 1) {
				printf("%s", line1);
			}
			r1 = getline(&line1, &len1, file1);
		//line is unique to file 2
		} else if (cmp > 0) {	
			if (flag != 2) {
				printf("\t%s", line2);
			}
			r2 = getline(&line2, &len2, file2);
		//line common to both files
		} else {					
			if (flag != 3) {		
				printf("\t\t%s", line1);
			}
			r1 = getline(&line1, &len1, file1);
			r2 = getline(&line2, &len2, file2);
		}
	}
	//print remaining lines if any
	while (r1 != 0 && flag != 1) {
		printf("%s", line1);
		r1 = getline(&line1, &len1, file1);
	}
	while (r2 != 0 && flag != 2) {
		printf("\t%s", line1);
		r2 = getline(&line2, &len2, file2);
	}
	free(line1);
	free(line2);
}

int main(int argc, char* argv[]) {
	if (argc <= 2) {
		printf("Usage: comm [-1 | -2 | -3] file1 file2\n");
		return 1;
	}
	//check for flags
	//-1: 1st column omitted (lines unique to file 1).
	//-2: 2nd column ommited (lines unique to file 2).
	//-3: 3rd column ommitted (lines common to both files).
	int flag = 0;
	char *flag_str = argv[1];

	if (*flag_str == '-') {
		flag_str++;
		if (*flag_str == '1') {
			flag = 1;
		} else if (*flag_str == '2') {
			flag = 2;
		} else if (*flag_str == '3') {
			flag = 3;
		} else {
			printf("invalid flags\n");
		}
		comm(argv[2], argv[3], flag);		
	} else {
		comm(argv[1], argv[2], 0);
	}
	return 0;
}
