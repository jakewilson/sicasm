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

    file = calloc(100, sizeof *file);

    // fill the symbol table
    pass_1(fp, sym_tab, op_tab);

    if (error_thrown == FALSE) {
        int lst_path_size = strlen(argv[1]) + strlen(LST_EXT) + 1;
        int obj_path_size = strlen(argv[1]) + strlen(OBJ_EXT) + 1;

        char *lst_path = calloc(lst_path_size, sizeof *lst_path);
        char *obj_path = calloc(obj_path_size, sizeof *obj_path);

        snprintf(lst_path, lst_path_size, "%s%s", argv[1], LST_EXT);
        snprintf(obj_path, obj_path_size, "%s%s", argv[1], OBJ_EXT);

        FILE *lst = fopen(lst_path, "w+");
        FILE *obj = fopen(obj_path, "w+");

        pass_2(sym_tab, op_tab, lst, obj);
    }

    fclose(fp);

    free(sym_tab);
    free(op_tab);

    return 0;
}

void add_line(int line_num, int loc, char *line) {
    file[line_num].loc = loc;
    file[line_num].line = calloc(LINE_MAX_SIZE, sizeof *(file[line_num].line));
    strcpy(file[line_num].line, line);
}
