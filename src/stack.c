/*
 * Source file for stack functions.
 *
 * Author: Jake Wilson
 * Date: March 21, 2015
 */

#include <stdlib.h>

#include "../include/stack.h"


/*
 * Returns whether the stack is empty or not
 * @param s
 *              the stack in question
 * @return
 *              TRUE if the stack is empty, FALSE if not
 */
int empty(Stack *s) {
    return s->top == NULL;
}
