/*
 * gen_ops.c
 * Source file for sicasm general operations.
 *
 * Author: Jake Wilson
 * Date: March 9, 2015
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "../include/gen_ops.h"

/*
 * Determines whether a string is a literal or not (starts with '=')
 * @return
 *              TRUE if str is a literal, FALSE if not
 */
int is_literal(char *str) {
    if (!is_empty(str))
        return (str[0] == '=');

    return FALSE;
}

/*
 * Same as convert_to_int, but returns false if the converted number
 * is negative.

 * @param str
 *              the string to convert
 * @param num
 *              the pointer to store the conversion at
 * @param base
 *              the number base that string is in
 * @return
 *              TRUE if the conversion was successful AND num is positive, FALSE if neither
 */
int convert_to_pos_int(char *str, int *num, int base) {
    return convert_to_int(str, num, base) && *(num) >= 0;
}

/*
 * Converts str to an int, and stores the value in num if the conversion
 * was successful.
 * 
 * @param str
 *              the string to convert
 * @param num
 *              the pointer to store the conversion at
 * @param base
 *              the number base that string is in
 * @return
 *              TRUE if the conversion was successful, FALSE if not
 */
int convert_to_int(char *str, int *num, int base) {
    char *endptr;
    *num = (int)strtol(str, &endptr, base);

    return !(endptr == str);
}

/*
 * Returns whether the string is empty (equals the empty string)
 * 
 * @param str
 *              the string to check
 * @return
 *              whether the str is the empty string ("")
 */
int is_empty(char *str) {
    return (strcmp(str, "") == 0);
}

/*
 * Trims a string and returns a newly allocated pointer to
 * the trimmed string.
 * NOTE: It is the callers responsibility to free the returned string.

 * @param str
 *              the string to string
 * @return
 *              the newly trimmed string
 */
char *trim(char *str) {
    char *ret = (char *)calloc((strlen(str) + 1), sizeof *ret);

    while (isspace(*str)) str++;

    // the string is not all spaces
    if (*str != 0) {
        char *end = &str[strlen(str) - 1];
        while (end > str && isspace(*end)) end--;
    
        *(end + 1) = '\0';
    }
    strncpy(ret, str, strlen(str) + 1); // add one for the \0

    return ret;
}

/*
 * Returns whether the line is a comment line (starts with a '.')
 * @return
 *              whether the line is a comment line
 */
int is_comment_line(char *line) {
    if (strlen(line) > 0) {
        return (line[0] == '.');
    }
    return TRUE;
}

/*
 * Returns whether the line is a blank line (first char is a '\n')
 * @return
 *              whether the line is a blank line
 */
int is_blank_line(char *line) {
    if (strlen(line) > 0) {
        return (line[0] == '\n');
    }
    return TRUE;
}

/*
 * Determines if a character is a letter, case-insensitive
 * @param c:
 *          the character to evaluate
 * @return:
 *          a non-zero integer if the character is a letter, zero if not
 */
int is_letter(char c) {
    return (c >= 97 && c <= 122) || (c >= 65 && c <= 90);
}

/*
 * Determines if a character is a digit
 * @param c:
 *          the character to evaluate
 * @return:
 *          a non-zero integer if the character is a digit, zero if not
 */
int is_digit(char c) {
    return (c >= 48 && c <= 57);
}

/*
 * Determines if a character is a newline
 * @param c:
 *          the character to evaluate
 * @return:
 *          a non-zero integer if the character is a newline, zero if not
 */
int is_newline(char c) {
    return (c == 10);
}

/*
 * Determines if a character is a carriage return
 * @param c:
 *          the character to evaluate
 * @return:
 *          a non-zero integer if the character is a carriage return, zero if not
 */
int is_cr(char c) {
    return (c == 13);
}

/*
 * Determines if a character is a pound sign ('#')
 * @param c:
 *          the character to evaluate
 * @return:
 *          a non-zero integer if the character is a pound sign, zero if not
 */
int is_pound(char c) {
    return (c == 35);
}

/*
 * Determines if a character is an at sign ('@')
 * @param c:
 *          the character to evaluate
 * @return:
 *          a non-zero integer if the character is an at sign, zero if not
 */
int is_at_sign(char c) {
    return (c == 64);
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


