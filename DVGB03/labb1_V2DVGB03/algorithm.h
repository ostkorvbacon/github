#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <stdbool.h> // bool

// bubble_sort sorts an array arr of length n
void bubble_sort(int *arr, int n);

// insertion_sort sorts an array arr of length n
void insertion_sort(int *arr, int n);

// quick_sort sorts an array arr of length n
void quick_sort(int *arr, int n);

// Sub funktion of quick_sort, sorts array with iteration
void QuickSort(int *arr,int low,int high);

// Partitions the array to make it faster to sort
int partition(int *arr, int low, int high);

// linear_search checks whether a value v is in an array arr of length n
bool linear_search(const int *arr, int n, int v);

// binary_search checks whether a value v is in a sorted arrray arr of length n
bool binary_search(const int *arr, int n, int v);

#endif
