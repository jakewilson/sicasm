/*
 * Source file for stack functions.
 *
 * Author: Jake Wilson
 * Date: March 21, 2015
 */

#include <stdlib.h>
#include <string.h>

#include "../include/stack.h"


/*
 * Returns whether the stack is empty or not
 * @param s
 *              the stack in question
 * @return
 *              TRUE if the stack is empty, FALSE if not
 */
int empty(Stack *s) {
    return (s->top == -1);
}

/*
 * Pops a string from the stack
 * @param s
 *              the stack to pop from
 */
char *pop(Stack *s) {
    if (!empty(s))
        return s->stack[s->top--];
    
    return NULL;
}


/*
 * Pushes a string onto the stack
 * @param s
 *              the stack to push to
 * @param str
 *              the string to push
 */
void push(Stack *s, char *str) {
    if (s->top < s->size)
        s->stack[++(s->top)] = str;
}

Stack *new_stack() {
    Stack *s = memset(malloc(sizeof *s), '\0', sizeof *s);
    s->top = -1;
    s->stack = calloc(STACK_SIZE, sizeof *(s->stack));
    s->size = STACK_SIZE;
    return s;
}