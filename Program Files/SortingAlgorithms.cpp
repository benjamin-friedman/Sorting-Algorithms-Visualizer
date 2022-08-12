/*
  Author: Benjamin G. Friedman
  File: SortingAlgorithms.cpp
  Description:
      - The implementation file for the sorting algorithms. Also includes various helper functions.
        The linked list interface is necessary for bucket sort.
*/


#include "SortingAlgorithms.h"
#include <stdlib.h>
#include <unistd.h>
#include <vector>
#include <algorithm>
#include <iostream>

extern const size_t totalNumbers;	// 250
const int totalBuckets = 25;
const int bucketInterval = 100;

typedef struct node {
    int data;
    struct node* next;
} Node;


/* Actual merge sort */
void mergeSort(int *a, int *L, int *R, int l, int r);

/* Helper Functions */
void swap(int *n1, int *n2);				    // most algorithms
int indexOfMin(int *a, int size, int starting_index);	    // selection sort
void fixDown(int *a, int size, int index);		    // heap sort
void removeTheMax(int *a, int size);			    // heap sort
void merge(int *a, int *L, int *R, int l, int m, int r);    // merge sort
Node* insertionSort(Node* list);			    // bucket sort
int getBucketIndex(int value);
int getMax(int* a, int size);				    // radix sort
void countSort(int* a, int size, int exp);		


/* Sorting Algorithm Function Definitions */
void bubbleSort(int *a, int size) {
    for (int i = 0; i < size - 1; ++i) {
	for (int j = 0; j < size - 1 - i; ++j) {
	    if (a[j] > a[j + 1]) {
		swap(&a[j], &a[j + 1]);
		usleep(1500);
	    }
	}
    }
}



void selectionSort(int *a, int size) {
    for (int i = 0; i < size - 1; ++i) {
	swap(&a[i], &a[indexOfMin(a, size, i)]);
	usleep(100000);
    }
}



void insertionSort(int *a, int size) {
    int item_index;
    for (int i = 1; i < size; ++i) {
	item_index = i;
	for (int j = i - 1; j >= 0 && a[item_index] < a[j]; --j) {
	    swap(&a[item_index], &a[j]);
	    item_index = j;
	    usleep(1750);
	}
    }
}



void shellSort(int *a, int size) {
    int temp, h = 2;

    while (h < size / 3)
	h *= 2;
    h--;

    while (h > 0) {
	for (int i = h; i < size; ++i) {
	    temp = a[i];
	    int j;
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
    for (int i = size / 2 - 1; i >= 0; --i) {
	fixDown(a, size, i);
	usleep(70000);
    }

    int originalSize = size;
    for (int i = 0; i < originalSize - 1; ++i) {
	removeTheMax(a, size);
	--size;
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



void countingSort(int* a, int size) {
    int max = a[0];
    for (int i = 1; i < size; ++i) {
	if (a[i] > max)
	    max = a[i];
    }
    int* count = new int[max + 1];
    int* output = new int[totalNumbers];

    for (int i = 0; i <= max; ++i)
	count[i] = 0;

    for (int i = 0; i < size; ++i)
	count[a[i]]++;

    for (int i = 1; i <= max; ++i)
	count[i] += count[i - 1];

    for (int i = size - 1; i >= 0; --i) {
	output[count[a[i]] - 1] = a[i];
	count[a[i]]--;
    }

    for (int i = 0; i < size; ++i) {
	usleep(100000);
	a[i] = output[i];
    }

    delete[] count;
    delete[] output;
}



void bucketSort(int* a, int size) {
    Node** buckets = new Node*[totalBuckets];

    for (int i = 0; i < totalBuckets; ++i)
	buckets[i] = nullptr;

    for (int i = 0; i < size; ++i) {
	int pos = getBucketIndex(a[i]);
	Node* current = new Node;
	current->data = a[i];
	current->next = buckets[pos];
	buckets[pos] = current;
    }

    for (int i = 0; i < totalBuckets; ++i)
	buckets[i] = insertionSort(buckets[i]);

    for (int j = 0, i = 0; i < totalBuckets; ++i) {
	Node* node = buckets[i];
	while (node != nullptr) {
	    a[j++] = node->data;
	    usleep(100000);
	    node = node->next;
	}
    }

    for (int i = 0; i < totalBuckets; ++i) {
	Node* current = buckets[i];
	while (current != nullptr) {
	    Node* next = current->next;
	    delete current;
	    current = next;
	}
    }

    delete[] buckets;
}



void radixSort(int* a, int size) {
    int max = getMax(a, size);
    for (int exp = 1; max / exp > 0; exp *= 10) {
	usleep(20000);
	countSort(a, size, exp);
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
    for (int i = starting_index + 1; i < size; ++i) {
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
  
    for (i = 0; i < n1; ++i)
        L[i] = a[l + i];
    for (j = 0; j < n2; ++j)
        R[j] = a[m + 1 + j];
  
    i = 0;
    j = 0;
    k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            a[k] = L[i];
            ++i;
        }
        else {
            a[k] = R[j];
            ++j;
        }
	usleep(5000);
        ++k;
    }
  
    while (i < n1) {
        a[k] = L[i];
        ++i;
        ++k;
	usleep(5000);
    }
  
    while (j < n2) {
        a[k] = R[j];
        ++j;
        ++k;
	usleep(5000);
    }
}



int getMax(int* a, int size) {
    int max = a[0];
    for (int i = 1; i < size; ++i)
        if (a[i] > max)
            max = a[i];
    return max;
}



Node* insertionSort(Node* list) {
    if (list == nullptr || list->next == nullptr)
	return list;
    
    Node* nodeList = list;
    Node* k = list->next;
    nodeList->next = nullptr;
  
    while (k != nullptr) {
        Node *ptr = nullptr;
        if (nodeList->data > k->data) {
            Node* tmp = k;
            k = k->next;
            tmp->next = nodeList;
            nodeList = tmp;
            continue;
        }

        for (ptr = nodeList; ptr->next != nullptr; ptr = ptr->next) {
            if (ptr->next->data > k->data)
                break;
        }

        if (ptr->next != nullptr) {
            Node *tmp = k;
            k = k->next;
            tmp->next = ptr->next;
            ptr->next = tmp;
            continue;
        }
        else {
            ptr->next = k;
            k = k->next;
            ptr->next->next = 0;
            continue;
        }
    }
    
    return nodeList;
}



int getBucketIndex(int value) {
    return value / bucketInterval;
}



void countSort(int* a, int size, int exp) {
    int* output = new int[size];
    int count[10] = { 0 };
 
    for (int i = 0; i < size; ++i) {
        count[(a[i] / exp) % 10]++;
    }
    for (int i = 1; i < 10; ++i) {
        count[i] += count[i - 1];
    }
    for (int i = size - 1; i >= 0; --i) {
        output[count[(a[i] / exp) % 10] - 1] = a[i];
        count[(a[i] / exp) % 10]--;
    }
    for (int i = 0; i < size; ++i) {
        a[i] = output[i];
	usleep(35000);
    }

    delete[] output;
}
