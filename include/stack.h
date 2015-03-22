/*
 * Header file for stack functions.
 *
 * Author: Jake Wilson
 * Date: March 21, 2015
 */

typedef struct Stack {
    char *top;
    char **stack;
    int size;
} Stack;

char *pop(Stack *s);
void push(Stack *s, char *str);
int empty(Stack *s);
