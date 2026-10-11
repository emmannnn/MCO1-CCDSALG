/* sort.c - insertion sort, merge sort, and polar angle helper functions */
#include <math.h>
#include "sort.h"

/* Temporary array used by merge sort when merging two halves */
static Point temp[MAX_SIZE];

/*
 * Returns the index of the anchor point.
 * The anchor is the point with the lowest y coordinate.
 * If there is a tie, the point with the lower x coordinate is chosen.
 */
int findAnchor(Point points[], int n)
{
    int i;
    int anchorIndex = 0;

    for (i = 1; i < n; i++) {
        if (points[i].y < points[anchorIndex].y) {
            anchorIndex = i;
        }
        else if (points[i].y == points[anchorIndex].y &&
                 points[i].x < points[anchorIndex].x) {
            anchorIndex = i;
        }
    }

    return anchorIndex;
}

/*
 * Computes the polar angle and the squared distance of every point
 * with respect to the anchor.
 *
 * Since the anchor is the lowest point, all angles are from 0 to pi.
 * The anchor itself gets angle 0 and distance 0, so after sorting
 * it will always end up at index 0.
 */
void computePolarAngles(Point points[], int n, Point anchor)
{
    int i;
    double dx, dy;

    for (i = 0; i < n; i++) {
        dx = points[i].x - anchor.x;
        dy = points[i].y - anchor.y;

        points[i].angle = atan2(dy, dx);
        points[i].dist = dx * dx + dy * dy;   /* no need for sqrt when only comparing */
    }
}

/*
 * Returns 1 if point a should come before point b in the sorted order.
 * Smaller polar angle goes first.
 * If the angles are equal, the point closer to the anchor goes first.
 */
int comesBefore(Point a, Point b)
{
    if (a.angle < b.angle)
        return 1;
    if (a.angle > b.angle)
        return 0;

    if (a.dist < b.dist)
        return 1;
    return 0;
}

/* ---------- SLOW: insertion sort ---------- */
void insertionSort(Point points[], int n)
{
    int i, j;
    Point key;

    for (i = 1; i < n; i++) {
        key = points[i];
        j = i - 1;

        /* shift the bigger elements one position to the right */
        while (j >= 0 && comesBefore(key, points[j])) {
            points[j + 1] = points[j];
            j--;
        }

        points[j + 1] = key;
    }
}

/* ---------- FAST: merge sort ---------- */

/* Merges the sorted halves points[left..mid] and points[mid+1..right] */
void merge(Point points[], int left, int mid, int right)
{
    int i = left;       /* index for the left half */
    int j = mid + 1;    /* index for the right half */
    int k = left;       /* index for the temp array */

    while (i <= mid && j <= right) {
        if (comesBefore(points[j], points[i])) {
            temp[k] = points[j];
            j++;
        }
        else {
            temp[k] = points[i];
            i++;
        }
        k++;
    }

    /* copy whatever is left in the left half */
    while (i <= mid) {
        temp[k] = points[i];
        i++;
        k++;
    }

    /* copy whatever is left in the right half */
    while (j <= right) {
        temp[k] = points[j];
        j++;
        k++;
    }

    /* copy the merged result back to the original array */
    for (k = left; k <= right; k++) {
        points[k] = temp[k];
    }
}

void mergeSort(Point points[], int left, int right)
{
    int mid;

    if (left < right) {
        mid = (left + right) / 2;

        mergeSort(points, left, mid);
        mergeSort(points, mid + 1, right);
        merge(points, left, mid, right);
    }
}
