/* stack.h - Point type and array-based stack used by Graham's scan */
#ifndef STACK_H
#define STACK_H

#define MAX_SIZE 32768   /* 2^15, the maximum problem size */

/* A 2D point. The angle and dist fields are filled in before sorting. */
typedef struct {
    double x;
    double y;
    double angle;   /* polar angle from the anchor, in radians */
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
