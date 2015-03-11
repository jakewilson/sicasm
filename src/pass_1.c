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
    int lengths[4] = {LABEL_LEN, OPCODE_LEN, ARG_LEN, COMMENT_LEN};

    // allocate space for each individual string
    int i;
    for (i = 0; i < NUM_SEGMENTS; i++) {
        // add one to the length to add the \0
        tokens[i] = (char *)(malloc((lengths[i] + 1) * sizeof(char)));
    }

    strncpy(tokens[LABEL], &line[0], LABEL_LEN);
    tokens[LABEL][LABEL_LEN] = '\0';

    strncpy(tokens[OPCODE], &line[9], OPCODE_LEN);
    tokens[OPCODE][OPCODE_LEN] = '\0';

    strncpy(tokens[ARG], &line[18], ARG_LEN);
    tokens[ARG][ARG_LEN] = '\0';

    strncpy(tokens[COMMENT], &line[31], COMMENT_LEN);
    tokens[COMMENT][COMMENT_LEN] = '\0';

    return tokens;
}
