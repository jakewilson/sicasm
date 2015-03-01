/*
 * main.c
 * Main file for Project 1.
 *
 * Author: Jake Wilson
 * Date:   January 12, 2015
 */

#include "hash_table.h"
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("ERROR: Must supply an argument.\n");
        return BAD_ARGS;
    }

    HashTable *table = new_hashtable();
    FILE *fp = fopen(argv[1], "r");

    if (fp == NULL) {
        printf("ERROR: Could not open file: %s.\n", argv[1]);
        return BAD_FILE;
    }

    read_file(table, fp);
    return 0;
}

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
            if (strlen(val) == 0) {
                Node *n = lookup(table, key);
                if (n != NULL) {
                    printf("Found %s at location %d with value %d.\n", key, hash(key), n->value);
                } else {
                    printf("ERROR %s not found.\n", key);
                }
            } else {
                add_to_table(table, key, atoi(val));
            }
        }
    } 
}

