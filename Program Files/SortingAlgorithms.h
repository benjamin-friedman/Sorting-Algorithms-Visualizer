#ifndef SORTING_ALGORITHMS_H
#define SORTING_ALGORITHMS_H

/* Sorting Algorithms */
void bubbleSort(int *a, int size);
void selectionSort(int *a, int size);
void insertionSort(int *a, int size);
void shellSort(int *a, int size);
void quickSort(int *a, int size);
void heapSort(int *a, int size);
void mergeSortWrapper(int* a, int size);
void mergeSort(int *a, int *L, int *R, int l, int r);

/* Helper Functions */
void swap(int *n1, int *n2);				    // most algorithms
int indexOfMin(int *a, int size, int starting_index);	    // selection sort
void fixDown(int *a, int size, int index);		    // heap sort
void removeTheMax(int *a, int size);			    // heap sort
void merge(int *a, int *L, int *R, int l, int m, int r);    // merge sort

#endif
