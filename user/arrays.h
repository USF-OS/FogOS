#ifndef ARRAYS_H
#define ARRAYS_H

// Array printing function
void print_array(int* arr, int size);

// Insertion sort for integer arrays
void sort_int_array(int* arr, int size);

// Deletes value at specified index (only for arrays with dynamic memory allocation)
void delete_at_index(int** arr, int index, int *size);

// Adds a specified value at a specified index (only for arrays with dynamic memory allocation)
void add_at_index(int** arr, int value, int index, int *size);

// Returns the index of the value to search or -1
int binary_search(int* arr, int target, int size);

// Returns the union of two arrays
int* array_union(int* arr1, int* arr2, int size1, int size2, int *new_size);

// Returns the intersection of two arrays
int* array_intersection(int* arr1, int* arr2, int size1, int size2, int *new_size);


#endif
