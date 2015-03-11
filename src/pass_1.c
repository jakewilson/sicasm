/*
 * pass_1.c
 * File for the functions of Pass 1 of the assembler.
 *
 * Author: Jake Wilson
 * Date: March 8, 2015
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/sicasm.h"

/*
 * Tokenizes a line into four segments, any of which may be empty:
 *  - the LABEL segment
 *  - the OPCODE segment (this will contain a + if provided)
 *  - the ARG segment (this will contain a #,@, or = if provided)
 *  - the COMMENT segment
 *
 * NOTES:
 *       - It is the callers responsibility to free the returned array, since it is
 *         dynamically allocated on the heap.
 * 
 *       - It is the callers responsibility to ensure the line is not a comment line
 *         before calling this function.
 *
 * @param line
 *              the line to tokenize
 * @return
 *              an array of 4 strings, each containing a segment of the line
 */
char **tokenize(char *line) {
    // allocate space for the array of strings
    char **tokens = (char **)(malloc(NUM_SEGMENTS * sizeof(char *)));

    // the lengths of each segment
    int lengths[NUM_SEGMENTS] = {SEGMENT_LENGTHS};

    int start_positions[NUM_SEGMENTS] = {SEGMENT_STARTING_POSITIONS};

    // allocate space for each individual string
    int i;
    for (i = 0; i < NUM_SEGMENTS; i++) {
        // add one to the length to add the \0
        tokens[i] = (char *)(malloc((lengths[i] + 1) * sizeof(char)));
        // copy each substring of the line into the appropriate token
        strncpy(tokens[i], &line[start_positions[i]], lengths[i]);
        tokens[i][lengths[i]] = '\0';
    }

    return tokens;
}
