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
    error_pass = PASS_1;
    char *line = calloc(LINE_MAX_SIZE, sizeof *line);
    int line_num = 1;

    // eat up all initial blank and/or comment lines
    while (is_comment_line(line = fgets(line, LINE_MAX_SIZE, pgm)) || is_blank_line(line))
        print_line(line_num++, -1, line);

    char **tokens = tokenize(line);
    int loc_ctr = 0;


    if (strcasecmp(tokens[OPCODE], "START") == 0) {
        int loc;
        if (convert_to_pos_int(tokens[ARG], &loc, 16)) {
            loc_ctr = loc;
        } else {
            set_error(NEGATIVE_OPERAND);
        }

        add_to_sym_tab(sym_tab, tokens[LABEL], loc_ctr);
        print_line(line_num++, loc_ctr, line);
        write_error(line_num - 1);
    }

    free_tokens(tokens);

    Stack *literal_stack = new_stack(); // keep track of all literals with a stack

    // parse the file line by line
    while ((line = fgets(line, LINE_MAX_SIZE, pgm)) != NULL) {
        if (!is_comment_line(line) && !is_blank_line(line)) {
            tokens = tokenize(line);

            if (is_empty(tokens[ARG]))
                set_error(EMPTY_ARG);

            add_to_sym_tab(sym_tab, tokens[LABEL], loc_ctr);

            if (is_literal(tokens[ARG]))
                push(literal_stack, tokens[ARG]);

            print_line(line_num++, loc_ctr, line);

            increment_loc_ctr(op_tab, &loc_ctr, tokens, sym_tab, literal_stack, &line_num);
            write_error(line_num - 1);

            free_tokens(tokens);
        } else { // if it is a blank or comment line
            print_line(line_num++, -1, line);
        }
    } // end while()

}


/*
 * Removes all literals from the stack and adds them to the symbol table
 * @param lit_stack
 *              the literal stack
 * @param sym_tab
 *              the symbol table
 * @param loc_ctr
 *              the location counter
 */
void add_literals(Stack *lit_stack, HashTable *sym_tab, int *loc_ctr, int *line_num) {
    while (!empty(lit_stack)) {
        char *lit = pop(lit_stack);
        // we do a find here because we don't want to generate an error if a
        // duplicate literal is found
        if (find(sym_tab, lit) == NULL) {
            int bytes = get_bytes(&lit[1]);
            add_to_sym_tab(sym_tab, lit, *loc_ctr);

            // print the literal
            char lit_line[LINE_MAX_SIZE];

            sprintf(lit_line, "%s BYTE %s\n", lit, &lit[1]);

            print_line((*line_num)++, *loc_ctr, lit_line);
            write_error((*line_num) - 1);

            *loc_ctr += bytes;
        }
        free(lit);
    }
}


/*
 * Prints a line to the specified stream
 * If the loc_ctr is less than 0, it is ommitted
 *
 * @param line_num
 *              the line number
 * @param loc_ctr
 *              the location counter
 * @param line
 *              the line to print
 */
void print_line(int line_num, int loc_ctr, char *line) {
    if (loc_ctr >= 0) {
        printf("%03d- %05X%5s%s", line_num, loc_ctr, "", line);
    } else {
        printf("%03d- %5s%5s%s", line_num, "", "", line);
    }
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
 * @param sym_tab
 *              the symbol table
 * @param lit_stack
 *              the literal stack
 * @param line_num
 *              the line number
 */
void increment_loc_ctr(HashTable *op_tab, int *loc_ctr, char **tokens, HashTable *sym_tab, Stack *lit_stack, int *line_num) {
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
            set_error(NEGATIVE_OPERAND);
        }

    } else if (strcmp(tokens[OPCODE], "BYTE") == 0) {
        *loc_ctr += get_bytes(tokens[ARG]);
    } else if (strcmp(tokens[OPCODE], "RESB") == 0) {
        int words = -1;

        if (convert_to_pos_int(tokens[ARG], &words, 10)) {
            *loc_ctr += words;
        } else {
            set_error(NEGATIVE_OPERAND);
        }
        
    } else if (strcmp(tokens[OPCODE], "BASE") == 0) {

    } else if (strcmp(tokens[OPCODE], "NOBASE") == 0) {

    } else if (strcmp(tokens[OPCODE], "LTORG") == 0) {
        add_literals(lit_stack, sym_tab, loc_ctr, line_num);
    } else if (strcmp(tokens[OPCODE], "END") == 0) {
        add_literals(lit_stack, sym_tab, loc_ctr, line_num);
    } else {
        set_error(UNDEFINED_INS);
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
            set_error(DUPLICATE_SYMBOL);
        }
    }
}

/*
 * Gets the number of bytes of a byte literal string, for example:
 *   X'FEBA' -> 2 bytes
 *   C'EOF'  -> 3 bytes
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
                set_error(ODD_BYTES);
            }

        } else if (*str == 'C'){
            str += 2; // skip two characters (the C and the ')
            int num_chars = 0;
    
            while (*str++ !='\'') num_chars++;
            
            num_bytes = num_chars;
        } else {
            set_error(INVALID_LIT_CHAR);
        }

    } else {
        set_error(INVALID_QUOTES);
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


