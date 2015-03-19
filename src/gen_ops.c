/*
 * file_io.c
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
    return 1;
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
    return 1;
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

