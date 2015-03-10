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

#include "../include/file_io.h"

/*
 * Populates a Hash Table given a file pointer to a
 * file filled with data. It adds lines with both keys
 * and values, and looks up lines with only keys.
 * @param table:
 *                  the Hash Table to fill
 * @param fp:
 *                  the pointer to the file to read
 */
void read_file(HashTable *table, FILE *fp) {
    char c = '\0', key[10], val[12];
    int keyIdx = 0, valIdx = 0;
    while ((c = fgetc(fp)) != EOF) {
        if (is_letter(c)) {
            key[keyIdx++] = c;
        } else if (is_digit(c)) {
            val[valIdx++] = c;
        } else if (is_newline(c) || is_cr(c)) {
            // add key and val to the table
            // and clear the buffers
            key[keyIdx] = '\0';
            val[valIdx] = '\0';
            keyIdx = valIdx = 0;
            // add to the table only if a key and a value are entered
            if (strlen(val) != 0) { 
                printf("inserting %s...\n", key);
                insert(table, key, atoi(val));
            }
        }
    } 
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

