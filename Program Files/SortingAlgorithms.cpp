#include "SortingAlgorithms.h"
#include <stdlib.h>
#include <unistd.h>

/**** Sorting Algorithm Function Definitions *****/
void bubbleSort(int *a, int size) {
    int i, j;
    for (i = 0; i < size - 1; i++) {
	for (j = 0; j < size - 1 - i; j++) {
	    if (a[j] > a[j + 1]) {
		swap(&a[j], &a[j + 1]);
		usleep(1500);
	    }
	}
    }
}



void selectionSort(int *a, int size) {
    for (int i = 0; i < size - 1; i++) {
	swap(&a[i], &a[indexOfMin(a, size, i)]);
	usleep(100000);
    }
}



void insertionSort(int *a, int size) {
    int i, j, item_index;
    for (i = 1; i < size; i++) {
	item_index = i;
	for (j = i - 1; j >= 0 && a[item_index] < a[j]; j--) {
	    swap(&a[item_index], &a[j]);
	    item_index = j;
	    usleep(1750);
	}
    }
}



void shellSort(int *a, int size) {
    int i, j, temp, h = 2;

    while (h < size / 3)
	h *= 2;
    h--;

    while (h > 0) {
	for (i = h; i < size; i++) {
	    temp = a[i];
	    for (j = i - h; j >= 0 && temp < a[j]; j -= h) {
		a[j + h] = a[j];
		usleep(20000);
	    }

	    a[j + h] = temp;
	}

	h /= 2;
    }
}



void quickSort(int *a, int size) {
    if (size > 1) {
	int index_of_left, index_of_right;
	swap(&a[0], &a[rand() % size]);
	usleep(40000);
	index_of_left = 0;
	index_of_right = size - 1;

	while (index_of_left != index_of_right) {
	    while (index_of_right > index_of_left && a[index_of_right] > a[0])
		index_of_right--;
	    while (index_of_left < index_of_right && a[index_of_left] <= a[0])
		index_of_left++;
	    if (index_of_left != index_of_right) {
		swap(&a[index_of_left], &a[index_of_right]);
		usleep(40000);
	    }
	}

	swap(&a[0], &a[index_of_left]);
	usleep(40000);

	if (index_of_left > 1) {
	    quickSort(a, index_of_left);
	}

	if (index_of_left < size - 2) {
	    quickSort(&a[index_of_left + 1], size - index_of_left - 1);
	}
	
    }
}



void heapSort(int *a, int size) {
    int i;
    for (i = size / 2 - 1; i >= 0; i--) {
	fixDown(a, size, i);
	usleep(70000);
    }

    int originalSize = size;
    for (i = 0; i < originalSize - 1; i++) {
	removeTheMax(a, size);
	size--;
	usleep(70000);
    }
}



void mergeSortWrapper(int* a, int size) {
    int *L = new int[size];
    int *R = new int[size];
    
    mergeSort(a, L, R, 0, size - 1);
    
    delete[] L;
    delete[] R;
}

void mergeSort(int *a, int *L, int *R, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
 	
	usleep(50000); 
        mergeSort(a, L, R, l, m);
        mergeSort(a, L, R, m + 1, r); 
        merge(a, L, R, l, m, r);
    }
}



/***** Helper Function Definitions *****/
void swap(int *n1, int *n2) {
    int temp = *n1;
    *n1 = *n2;
    *n2 = temp;
}



int indexOfMin(int *a, int size, int starting_index) {
    int index_of_min = starting_index;
    for (int i = starting_index + 1; i < size; i++) {
	if (a[i] < a[index_of_min])
	    index_of_min = i;
    }
    return index_of_min;
}



void fixDown(int *a, int size, int index) {
    int index_of_left_child = index * 2 + 1;
    int index_of_right_child = index * 2 + 2;
    int index_of_largest_child = -1;
    int temp;

    if (index_of_right_child < size) {
	index_of_largest_child = a[index_of_left_child] > a[index_of_right_child] ?
	index_of_left_child : index_of_right_child;
    }
    else if (index_of_left_child < size)
	index_of_largest_child = index_of_left_child;

    if (index_of_largest_child != -1 && a[index] < a[index_of_largest_child]) {
	temp = a[index];
	a[index] = a[index_of_largest_child];
	a[index_of_largest_child] = temp;
	fixDown(a, size, index_of_largest_child);
    }
}



void removeTheMax(int *a, int size) {
    swap(&a[0], &a[size - 1]);
    fixDown(a, size - 1, 0);
}



void merge(int *a, int *L, int *R, int l, int m, int r) {
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;
  
    for (i = 0; i < n1; i++)
        L[i] = a[l + i];
    for (j = 0; j < n2; j++)
        R[j] = a[m + 1 + j];
  
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            a[k] = L[i];
            i++;
        }
        else {
            a[k] = R[j];
            j++;
        }
	usleep(5000);
        k++;
    }
  
    while (i < n1) {
        a[k] = L[i];
        i++;
        k++;
	usleep(5000);
    }
  
    while (j < n2) {
        a[k] = R[j];
        j++;
        k++;
	usleep(5000);
    }
}
