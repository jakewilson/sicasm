/*
 * Main file for sicasm.
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

    FILE *fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("ERROR: Could not open file: %s.\n", argv[1]);
        return BAD_FILE;
    }

    HashTable *sym_tab = new_hashtable();
    HashTable *op_tab = new_hashtable();

    construct_op_table(op_tab);

    // fill the symbol table
    pass_1(fp, sym_tab, op_tab);

    printf("\nSymbol Table\n-----------\n");
    print(sym_tab);

    fclose(fp);

    free(sym_tab);
    free(op_tab);

    return 0;
}

