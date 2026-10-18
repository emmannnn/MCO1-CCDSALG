/* stack.c - implementation of the array-based stack */
#include <stdio.h>
#include "stack.h"

/* CREATE(S): makes the stack empty */
void create(Stack *s)
{
    s->topIndex = -1;
}

/* ISFULL(S): returns 1 if no more elements can be pushed */
int isFull(Stack *s)
{
    if (s->topIndex == MAX_SIZE - 1)
        return 1;
    return 0;
}

/* ISEMPTY(S): returns 1 if the stack has no elements */
int isEmpty(Stack *s)
{
    if (s->topIndex == -1)
        return 1;
    return 0;
}

/* PUSH(S, elem): puts elem on top of the stack */
void push(Stack *s, Point elem)
{
    if (isFull(s)) {
        printf("Error: stack is full.\n");
        return;
    }

    s->topIndex = s->topIndex + 1;
    s->data[s->topIndex] = elem;
}

/* POP(S): removes the top element and returns it */
Point pop(Stack *s)
{
    Point elem;

    elem.x = 0.0;
    elem.y = 0.0;
    elem.dist = 0.0;

    if (isEmpty(s)) {
        printf("Error: stack is empty.\n");
        return elem;
    }

    elem = s->data[s->topIndex];
    s->topIndex = s->topIndex - 1;
    return elem;
}

/* TOP(S): returns the top element without removing it */
Point top(Stack *s)
{
    Point elem;

    elem.x = 0.0;
    elem.y = 0.0;
    elem.dist = 0.0;

    if (isEmpty(s)) {
        printf("Error: stack is empty.\n");
        return elem;
    }

    return s->data[s->topIndex];
}

/* NEXT-TO-TOP(S): returns the element just below the top element */
Point nextToTop(Stack *s)
{
    Point elem;

    elem.x = 0.0;
    elem.y = 0.0;
    elem.dist = 0.0;

    if (s->topIndex < 1) {
        printf("Error: stack has fewer than 2 elements.\n");
        return elem;
    }

    return s->data[s->topIndex - 1];
}
