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
 * Performs the first pass of sicasm on a file
 *
 * @param pgm
 *              the file pointer to read 
 * @param sym_tab
 *              the symbol table to be filled upon completion of pass 1
 * @param op_tab
 *              a hash table already filled with valid SIC/XE operations
 */
void pass_1(FILE *pgm, HashTable *sym_tab, HashTable *op_tab) {
    char *line = calloc(LINE_MAX_SIZE, sizeof *line);
    // eat up all initial blank and/or comment lines
    while (is_comment_line(line = fgets(line, LINE_MAX_SIZE, pgm)) || is_blank_line(line));
    char **tokens = tokenize(line);
    int loc_ctr = 0;
    if (strcasecmp(tokens[OPCODE], "START") == 0) {
        // TODO check if operand is a valid integer
        //      if so, assign the value to loc_ctr
    }
    //printf("%s%s%s%s\n", tokens[LABEL], tokens[OPCODE], tokens[ARG], tokens[COMMENT]);
    free_tokens(tokens);
}

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

    int lengths[NUM_SEGMENTS] = {SEGMENT_LENGTHS};
    int start_positions[NUM_SEGMENTS] = {SEGMENT_STARTING_POSITIONS};

    // allocate space for each individual string and assign each a value
    int i;
    for (i = 0; i < NUM_SEGMENTS; i++) {
        // add one to the length to make room for the '\0'
        tokens[i] = (char *)(malloc((lengths[i] + 1) * sizeof(char)));

        // copy each substring of the line into the appropriate token
        strncpy(tokens[i], &line[start_positions[i]], lengths[i]);
        tokens[i][lengths[i]] = '\0';
    }

    return tokens;
}

/*
 * Frees a two dimensional array of strings of size NUM_SEGMENTS
 * @param tokens
 *              the tokens array to free
 */
void free_tokens(char **tokens) {
    int i;
    for (i = 0; i < NUM_SEGMENTS; i++)
        free(tokens[i]);
    free(tokens);
}
