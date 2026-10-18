/* graham_scan2.c - Graham's scan using the "fast" sort (merge sort) */
#include <stdio.h>
#include <time.h>
#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif
#include <math.h>
#include <float.h>
#include "stack.h"
#include "sort.h"
#include "graham_scan.h"

static double getTimeMilliseconds(void)
{
#ifdef _WIN32
    LARGE_INTEGER counter;
    LARGE_INTEGER frequency;

    if (QueryPerformanceFrequency(&frequency) &&
        QueryPerformanceCounter(&counter)) {
        return ((double)counter.QuadPart * 1000.0) /
               (double)frequency.QuadPart;
    }
    return (double)GetTickCount64();
#else
    struct timespec ts;

    if (timespec_get(&ts, TIME_UTC) == TIME_UTC) {
        return ((double)ts.tv_sec * 1000.0) +
               ((double)ts.tv_nsec / 1000000.0);
    }
    return ((double)clock() * 1000.0) / (double)CLOCKS_PER_SEC;
#endif
}

#define TURN_EPS (512.0L * DBL_EPSILON) /* scale-aware tolerance for double rounding noise */

/*
 * Returns 1 only for a counterclockwise turn that is larger than estimated
 * floating-point rounding noise. The vectors are normalized before the
 * cross product, avoiding the old fixed 1e-10 angular cutoff and reducing
 * overflow/underflow risk. This preserves genuine small turns much better.
 */
static int isLeftTurn(Point a, Point b, Point c)
{
    long double abx = (long double)b.x - (long double)a.x;
    long double aby = (long double)b.y - (long double)a.y;
    long double acx = (long double)c.x - (long double)a.x;
    long double acy = (long double)c.y - (long double)a.y;
    long double abScale = fmaxl(fabsl(abx), fabsl(aby));
    long double acScale = fmaxl(fabsl(acx), fabsl(acy));
    long double u1x, u1y, u2x, u2y;
    long double cross, lengths;

    /* Repeated points cannot form a strict turn. */
    if (abScale == 0.0L || acScale == 0.0L)
        return 0;

    u1x = abx / abScale;
    u1y = aby / abScale;
    u2x = acx / acScale;
    u2y = acy / acScale;

    cross = u1x * u2y - u1y * u2x;
    lengths = sqrtl(u1x * u1x + u1y * u1y) *
              sqrtl(u2x * u2x + u2y * u2y);

    return cross > TURN_EPS * lengths;
}

int grahamScan2(Point points[], int n, Point hull[])
{
    static Stack s;     /* static so this big struct is not placed on the call stack */
    int i;
    int count;          /* number of elements currently in the stack */
    int anchorIndex;
    int m;
    Point p, t;
    double start, end, elapsed;

    start = getTimeMilliseconds();

    create(&s);
    count = 0;

    if (n > 0) {
        /* Step 1: find the anchor (lowest y, then lowest x) */
        anchorIndex = findAnchor(points, n);

        /* Step 2: compute polar angles, then sort. The anchor ends up at index 0. */
        computePolarAngles(points, n, points[anchorIndex]);
        mergeSort(points, 0, n - 1);

        /* Step 3: scan the sorted points */
        push(&s, points[0]);
        count = 1;

        for (i = 1; i < n; i++) {
            p = points[i];
            t = top(&s);

            /* skip duplicate points */
            if (p.x != t.x || p.y != t.y) {

                /* pop while the last two points and p do not make a left turn */
                while (count >= 2 && !isLeftTurn(nextToTop(&s), top(&s), p)) {
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

    end = getTimeMilliseconds();
    elapsed = end - start;
    printf("Elapsed time (fast version, merge sort): %f ms\n", elapsed);

    return m;
}
