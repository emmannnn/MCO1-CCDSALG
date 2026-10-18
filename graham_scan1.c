/* graham_scan1.c - Graham's scan using the "slow" sort (insertion sort) */
#include <stdio.h>
#include <time.h>
#include "stack.h"
#include "sort.h"
#include "graham_scan.h"

int grahamScan1(Point points[], int n, Point hull[])
{
    static Stack s;     /* static so this big struct is not placed on the call stack */
    int i;
    int count;          /* number of elements currently in the stack */
    int anchorIndex;
    int m;
    Point p, t;
    clock_t start, end;
    double elapsed;

    start = clock();

    create(&s);
    count = 0;

    if (n > 0) {
        /* Step 1: find the anchor (lowest y, then lowest x) */
        anchorIndex = findAnchor(points, n);

        /* Step 2: sort by polar angle around the anchor. The anchor ends up at index 0. */
        setAnchor(points, n, points[anchorIndex]);
        insertionSort(points, n);

        /* Step 3: scan the sorted points */
        push(&s, points[0]);
        count = 1;

        for (i = 1; i < n; i++) {
            p = points[i];
            t = top(&s);

            /* skip duplicate points */
            if (p.x != t.x || p.y != t.y) {

                /* pop while the last two points and p do not make a left turn.
                   A cross product within EPSILON of zero counts as collinear. */
                while (count >= 2 && crossProduct(nextToTop(&s), top(&s), p) <= EPSILON) {
                    pop(&s);
                    count--;
                }

                push(&s, p);
                count++;
            }
        }
    }

    /* Step 4: move the stack contents to hull[] so that the anchor is first */
    m = count;
    for (i = m - 1; i >= 0; i--) {
        hull[i] = pop(&s);
    }

    end = clock();
    elapsed = (double)(end - start) * 1000.0 / CLOCKS_PER_SEC;
    printf("Elapsed time (slow version, insertion sort): %f ms\n", elapsed);

    return m;
}
