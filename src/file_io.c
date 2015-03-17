/*
 * file_io.c
 * Source file for sicasm file operations.
 *
 * Author: Jake Wilson
 * Date: March 9, 2015
 */

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#include "../include/file_io.h"

/*
 * Trims a string of all leading and trailing white space. This returns a pointer
 * to the substring of the original (passed in) string, so it is important
 * to NOT overrwrite the original string with the return value, and only
 * to deallocate the original, not the returned string.
 *
 * @param str
 *              the string to string
 * @return
 *              the trimmed string as a substring of str
 */
char *trim(char *str) {
    while (isspace(*str)) str++;

    // the string is all spaces
    if (*str == 0)
        return str;

    char *end = &str[strlen(str) - 1];
    while (end > str && isspace(*end)) end--;

    *(end + 1) = '\0';

    return str;
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

