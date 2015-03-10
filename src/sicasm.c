/*
 * main.c
 * Main file for Project 1.
 *
 * Author: Jake Wilson
 * Date:   January 12, 2015
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "../include/sicasm.h"

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

