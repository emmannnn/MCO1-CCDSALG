/* sort.h - sorting algorithms and helper functions for polar angle sorting */
#ifndef SORT_H
#define SORT_H

#include "stack.h"

/* Helper functions */
double crossProduct(Point a, Point b, Point c);
int    findAnchor(Point points[], int n);
void   setAnchor(Point points[], int n, Point anchor);
int    comesBefore(Point a, Point b);

/* "Slow" sorting algorithm, O(n^2) */
void insertionSort(Point points[], int n);

/* "Fast" sorting algorithm, O(n log n) */
void mergeSort(Point points[], int left, int right);

#endif
