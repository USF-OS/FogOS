#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "arrays.h"
#include <stddef.h>


void sort_int_array(int* arr, int size) {
	for (int i = 1; i < size; i++) {
    	int curr = arr[i];
   		int j = i - 1;
    	while (j >= 0 && arr[j] > curr) {
      		arr[j + 1] = arr[j];
      		j = j - 1;
   		}
    	arr[j + 1] = curr;
	}
}

int binary_search(int* arr, int target, int size) {
	int low = 0;
	int high = size - 1;
	
	while (low <= high) {
		int mid = ((high - low) / 2) + low;
		int currentValue = arr[mid];
		if (currentValue == target) {
			return mid;
		} if (currentValue < target) {
			low = mid + 1;
		} else {
			high = mid - 1;
		}
	}
	return -1;
}

void print_array(int* arr, int size) {
	for (int i = 0; i < size; i++) {
    	printf("%d ", arr[i]);
	}
	printf("\n");
}

void delete_at_index(int** arr, int index, int *size) {
    if (index < 0 || index >= *size) {
        printf("Invalid index\n");
        return;
    }

    int* new_arr = (int*)malloc((*size - 1) * sizeof(int));
    if (new_arr == NULL) {
    	printf("malloc() could not be called\n");
        return;
    }

	// copy the first part until the index to delete, then skip in and copy the rest
    memcpy(new_arr, *arr, index * sizeof(int));
    memcpy(new_arr + index, *arr + index + 1, (*size - index - 1) * sizeof(int));

    free(*arr);
	*size = *size - 1;
    *arr = new_arr;
}

void add_at_index(int** arr, int value, int index, int *size) {
    if (index < 0 || index > *size) {
        printf("Invalid index.\n");
        return;
    }

    int* new_arr = (int*)malloc((*size + 1) * sizeof(int));
    if (new_arr == NULL) {
        printf("malloc() could not be called\n");
        return;
    }

	// copy the first part until the index, add value, then copy the second part
    memcpy(new_arr, *arr, index * sizeof(int));
    new_arr[index] = value;
    memcpy(new_arr + index + 1, *arr + index, (*size - index) * sizeof(int));
    
    free(*arr);
    *size = *size + 1;
    *arr = new_arr;
}

int* array_intersection(int* arr1, int* arr2, int size1, int size2, int *new_size) {
	sort_int_array(arr1, size1);
	sort_int_array(arr2, size2);

	
	int min = size1 < size2 ? size1: size2;
	int* intersection = (int*)malloc(sizeof(int) * min);
	if (intersection == NULL) {
		printf("malloc could not be called\n");
		return NULL;
	}

	int i = 0; 
	int j = 0; 
	int k = 0;

	while (i < size1 && j < size2) {
		if (arr1[i] == arr2[j]) {
	    	intersection[k++] = arr1[i]; 
	        i++;
	        j++;
	    } else if (arr1[i] < arr2[j]) {
	        i++;
	    } else {
	        j++;
	    }
	}
	
	*new_size = k;
	return intersection;	 
}

int* array_union(int* arr1, int* arr2, int size1, int size2, int *new_size) {
	sort_int_array(arr1, size1);
	sort_int_array(arr2, size2);

	int max = size1 > size2 ? size1: size2;
	int* union_arr = (int*)malloc(sizeof(int) * max);
	if (union_arr == NULL) {
		printf("malloc could not be called\n");
		return NULL;
	}

	int i = 0; 
	int j = 0;
	int k = 0;

	// add all arr1 values
	while (i < size1) {
		union_arr[k++] = arr1[i++];
	}
	
	// Found this algorithm online - adds unique arrr2 values
	for (j = 0; j < size2; j++) {
		int found = 0;
	    for (int l = 0; l < k; l++) {
	    	if (union_arr[l] == arr2[j]) {
	        	found = 1;
	            break;
	        }
	    }
	    if (!found) {
	 	   union_arr[k++] = arr2[j];
	    }
	}
	
	*new_size = k;	    
	return union_arr;	 
}



