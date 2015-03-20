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
 *              a pointer to the source file to assemble
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
        int loc;
        if (convert_to_pos_int(tokens[ARG], &loc, 16)) {
            // TODO make sure this isn't positive
            loc_ctr = loc;
        } else {
            // TODO write error: operand must be a positive number
        }

        add_to_sym_tab(sym_tab, tokens[LABEL], loc_ctr);
        // TODO write print_line()
    }

    free_tokens(tokens);

    // parse the file line by line
    while ((line = fgets(line, LINE_MAX_SIZE, pgm)) != NULL) {
        if (!is_comment_line(line) && !is_blank_line(line)) {
            tokens = tokenize(line);

            add_to_sym_tab(sym_tab, tokens[LABEL], loc_ctr);
            printf("%05X%5s%s", loc_ctr, "", line);

            increment_loc_ctr(op_tab, &loc_ctr, tokens);

            free_tokens(tokens);
        } // end !is_comment_line()
    } // end while()

}


/*
 * Looks up the specified opcode and increments loc_ctr by the format of opcode.
 * If the opcode is not found, the opcode is checked to see if it's an assembler directive.
 * If so, appropriate actions are taken and loc_ctr is incremented by the appropriate amount.
 * TODO all errors are written when appropriate
 *
 * @param op_tab
 *              the op table
 * @param loc_ctr
 *              the location counter
 * @param tokens
 *              the line tokens
 */
void increment_loc_ctr(HashTable *op_tab, int *loc_ctr, char **tokens) {
    Node *opcode = find(op_tab, tokens[OPCODE]);
    if (opcode != NULL) {
        *loc_ctr += opcode->format;
    } else if (strcmp(tokens[OPCODE], "WORD") == 0) {
        *loc_ctr += WORD_LEN;
    } else if (strcmp(tokens[OPCODE], "RESW") == 0) {
        int words = -1;

        if (convert_to_pos_int(tokens[ARG], &words, 10)) {
            *loc_ctr += (WORD_LEN * words);
        } else {
            // TODO write error: operand must be a positive number
        }

    } else if (strcmp(tokens[OPCODE], "BYTE") == 0) {
        *loc_ctr += get_bytes(tokens[ARG]);
    }

}


/*
 * Adds symbol to the symbol table if it isn't already there
 * If it is, the appropriate error will be written TODO
 *
 * @param sym_tab
 *              the symbol table
 * @param symbol
 *              the symbol to insert
 * @param loc_ctr
 *              the loc_ctr to insert for symbol
 */
void add_to_sym_tab(HashTable *sym_tab, char *symbol, int loc_ctr) {
    if (!is_empty(symbol)) {
        if (find(sym_tab, symbol) == NULL) { // and the label does not already exist
            insert_sym(sym_tab, symbol, loc_ctr);
        } else {
            // TODO write error: duplicate symbol
        }
    }
}

/*
 * Gets the number of bytes of a byte literal string, for example:
 * X'FEBA' -> 2 bytes
 * C'EOF'  -> 3 bytes
 * This function will also write the appropriate error to an error file TODO
 *
 * @param str
 *              the string to check 
 * @return
 *              the number of bytes of string, 0 if invalid
 */
int get_bytes(char *str) {
    int num_bytes = 0;

    if (str[1] == '\'' && str[strlen(str) - 1] == '\'') {
        if (*str == 'X') {
            // ensure amount of characters in between the quotes is even
            str += 2; // skip two characters (the X and the ')
            int num_chars = 0;
    
            while (*str++ !='\'') num_chars++;
    
            if (num_chars % 2 == 0) {
                num_bytes = (num_chars / 2);
            } else {
                // TODO write error: Odd number of X bytes found in operand field
            }

        } else if (*str == 'C'){
            str += 2; // skip two characters (the X and the ')
            int num_chars = 0;
    
            while (*str++ !='\'') num_chars++;
            
            num_bytes = num_chars;
        } else {
            // TODO write error: expected 'X' or 'C' before open quote
        }

    } else {
        // TODO write error: no quotes found in operand field
    }

    return num_bytes;
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
        char untrimmed[LINE_MAX_SIZE] = {0};

        // copy each substring of the line into the appropriate token
        strncpy(untrimmed, &line[start_positions[i]], lengths[i]);

        tokens[i] = trim(untrimmed);
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


