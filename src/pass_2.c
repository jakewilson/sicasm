/*
 * Source file for pass 2 of SIC/XE.
 *
 * Author: Jake Wilson
 * Date: March 27, 2015
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../include/sicasm.h"

/*
 * Performs pass 2 of the assembler.
 * @param pgm
 *              the source program to assemble
 * @param sym_tab
 *              the symbol table
 * @param op_tab
 *              the operand table
 * @param lst
 *              pointer to the .lst file
 * @param obj
 *              pointer to the .obj file
 *
 */
void pass_2(HashTable *sym_tab, HashTable *op_tab, FILE *lst, FILE *obj) {
    error_pass = PASS_2;
    int line_num = 1;

    while (is_comment_line(file[line_num].line) || is_blank_line(file[line_num].line))
        //print_line(line_num, -1, file[line_num++].line);
        line_num++;

    char **tokens = tokenize(file[line_num++].line);
    int begin = -1;
    convert_to_pos_int(tokens[ARG], &begin, 16);
    free(tokens);

    for (; line_num < file_size; line_num++) {
        if (!is_comment_line(file[line_num].line) && !is_blank_line(file[line_num].line)) {
            tokens = tokenize(file[line_num].line);
            Node *ins_node = find(op_tab, tokens[OPCODE]);
            if (ins_node != NULL) {
                printf("%X\n", ins_node->value);
            }

        } // end if comment() or blank()
    }
}
