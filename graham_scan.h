/* graham_scan.h - prototypes of the two versions of Graham's scan */
#ifndef GRAHAM_SCAN_H
#define GRAHAM_SCAN_H

#include "stack.h"

/*
 * Both functions compute the convex hull of points[0..n-1].
 * The hull points are stored in hull[] in counterclockwise order,
 * starting with the anchor. The return value is m, the number of hull points.
 */
int grahamScan1(Point points[], int n, Point hull[]);   /* slow version */
int grahamScan2(Point points[], int n, Point hull[]);   /* fast version */

#endif
