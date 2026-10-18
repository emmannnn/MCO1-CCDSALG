/* stack.h - Point type and array-based stack used by Graham's scan */
#ifndef STACK_H
#define STACK_H

#define MAX_SIZE 32768   /* 2^15, the maximum problem size */
#define EPSILON  1e-9    /* tolerance for floating-point rounding errors */

/* A 2D point. The dist field is filled in before sorting. */
typedef struct {
    double x;
    double y;
    double dist;    /* squared distance from the anchor */
} Point;

/* Stack implemented with an array */
typedef struct {
    Point data[MAX_SIZE];
    int topIndex;   /* index of the top element, -1 if the stack is empty */
} Stack;

void  create(Stack *s);
void  push(Stack *s, Point elem);
Point pop(Stack *s);
Point top(Stack *s);
Point nextToTop(Stack *s);
int   isFull(Stack *s);
int   isEmpty(Stack *s);

#endif
