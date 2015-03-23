/*
 * Header file for stack functions.
 *
 * Author: Jake Wilson
 * Date: March 21, 2015
 */

#define STACK_SIZE 10

typedef struct Stack {
    char **stack;
    int top;
    int size;
} Stack;

Stack *new_stack();
char *pop(Stack *s);
void push(Stack *s, char *str);
int empty(Stack *s);
