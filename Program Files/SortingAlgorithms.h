/*
  Author: Benjamin G. Friedman
  Date: 11/08/2021
  File: SortingAlgorithms.h
  Description:
      - Header file for the sorting algorithms.
*/


#ifndef SORTING_ALGORITHMS_H
#define SORTING_ALGORITHMS_H

/* Sorting Algorithms */
void bubbleSort(int* a, int size);
void selectionSort(int* a, int size);
void insertionSort(int* a, int size);
void shellSort(int* a, int size);
void quickSort(int* a, int size);
void heapSort(int* a, int size);
void mergeSort(int* a, int size);
void countingSort(int* a, int size);
void bucketSort(int* a, int size);
void radixSort(int* a, int size);

#endif
