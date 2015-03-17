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

    free(sym_tab);
    free(op_tab);

    return 0;
}

/*
 * Constructs the op table so it doesn't need to be read
 * in from a file every time a program is assembled
 *
 * @param op_tab
 *              the table to fill with opcodes
 */
void construct_op_table(HashTable *op_tab) {
    insert(op_tab, "+LDB", 68, 4);
    insert(op_tab, "MULR", 0X98, 2);
    insert(op_tab, "+SSK", 0XEC, 4);
    insert(op_tab, "WD", 0XDC, 3);
    insert(op_tab, "*STX", 0X10, 3);
    insert(op_tab, "*OR", 0X44, 3);
    insert(op_tab, "AND", 0X40, 3);
    insert(op_tab, "*LDA", 0X00, 3);
    insert(op_tab, "+JGT", 0X34, 4);
    insert(op_tab, "+STL", 0X14, 4);
    insert(op_tab, "*WD", 0XDC, 3);
    insert(op_tab, "+STI", 0XD4, 4);
    insert(op_tab, "LPS", 0XD0, 3);
    insert(op_tab, "+LDT", 0X74, 4);
    insert(op_tab, "*LDCH", 0X50, 3);
    insert(op_tab, "*LDL", 0X08, 3);
    insert(op_tab, "TIXR", 0XB8, 2);
    insert(op_tab, "SUBF", 0X5C, 3);
    insert(op_tab, "*JSUB", 0X48, 3);
    insert(op_tab, "LDX", 0X04, 3);
    insert(op_tab, "+MULF", 0X60, 4);
    insert(op_tab, "+J", 0X3C, 4);
    insert(op_tab, "SVC", 0XB0, 2);
    insert(op_tab, "STT", 0X84, 3);
    insert(op_tab, "+COMP", 0X28, 4);
    insert(op_tab, "TIX", 0X2C, 3);
    insert(op_tab, "FLOAT", 0XC0, 1);
    insert(op_tab, "LDT", 0X74, 3);
    insert(op_tab, "STA", 0X0C, 3);
    insert(op_tab, "*TD", 0XE0, 3);
    insert(op_tab, "SHIFTR", 0XA8, 2);
    insert(op_tab, "STB", 0X78, 3);
    insert(op_tab, "SIO", 0XF0, 1);
    insert(op_tab, "LDA", 0X00, 3);
    insert(op_tab, "HIO", 0XF4, 1);
    insert(op_tab, "+STS", 0X7C, 4);
    insert(op_tab, "DIVF", 0X64, 3);
    insert(op_tab, "*TIX", 0X2C, 3);
    insert(op_tab, "+JSUB", 0X48, 4);
    insert(op_tab, "LDCH", 0X50, 3);
    insert(op_tab, "+COMPF", 0X88, 4);
    insert(op_tab, "JEQ", 0X30, 3);
    insert(op_tab, "*DIV", 0X24, 3);
    insert(op_tab, "+STT", 0X84, 4);
    insert(op_tab, "+SUBF", 0X5C, 4);
    insert(op_tab, "*AND", 0X40, 3);
    insert(op_tab, "+OR", 0X44, 4);
    insert(op_tab, "SSK", 0XEC, 3);
    insert(op_tab, "+JLT", 0X38, 4);
    insert(op_tab, "*RD", 0XD8, 3);
    insert(op_tab, "LDS", 0X6C, 3);
    insert(op_tab, "*MUL", 0X20, 3);
    insert(op_tab, "+LDS", 0X6C, 4);
    insert(op_tab, "+DIV", 0X24, 4);
    insert(op_tab, "J", 0X3C, 3);
    insert(op_tab, "+MUL", 0X20, 4);
    insert(op_tab, "*COMP", 0X28, 3);
    insert(op_tab, "+STX", 0X10, 4);
    insert(op_tab, "*J", 0X3C, 3);
    insert(op_tab, "+LDA", 0X00, 4);
    insert(op_tab, "+SUB", 0X1C, 4);
    insert(op_tab, "+STB", 0X78, 4);
    insert(op_tab, "*JLT", 0X38, 3);
    insert(op_tab, "SUB", 0X1C, 3);
    insert(op_tab, "+ADDF", 0X58, 4);
    insert(op_tab, "RD", 0XD8, 3);
    insert(op_tab, "*JEQ", 0X30, 3);
    insert(op_tab, "LDB", 0X68, 3);
    insert(op_tab, "RSUB", 0X4C, 3);
    insert(op_tab, "MULF", 0X60, 3);
    insert(op_tab, "JSUB", 0X48, 3);
    insert(op_tab, "SUBR", 0X94, 2);
    insert(op_tab, "DIVR", 0X9C, 2);
    insert(op_tab, "LDL", 0X08, 3);
    insert(op_tab, "+JEQ", 0X30, 4);
    insert(op_tab, "+STCH", 0X54, 4);
    insert(op_tab, "*STL", 0X14, 3);
    insert(op_tab, "+STA", 0X0C, 4);
    insert(op_tab, "STSW", 0XE8, 3);
    insert(op_tab, "COMPF", 0X88, 3);
    insert(op_tab, "+DIVF", 0X64, 4);
    insert(op_tab, "+STF", 0X80, 4);
    insert(op_tab, "TIO", 0XF8, 1);
    insert(op_tab, "*ADD", 0X18, 3);
    insert(op_tab, "*STSW", 0XE8, 3);
    insert(op_tab, "+STSW", 0XE8, 4);
    insert(op_tab, "+LPS", 0XD0, 4);
    insert(op_tab, "JLT", 0X38, 3);
    insert(op_tab, "*JGT", 0X34, 3);
    insert(op_tab, "MUL", 0X20, 3);
    insert(op_tab, "+LDL", 0X08, 4);
    insert(op_tab, "OR", 0X44, 3);
    insert(op_tab, "COMP", 0X28, 3);
    insert(op_tab, "TD", 0XE0, 3);
    insert(op_tab, "STS", 0X7C, 3);
    insert(op_tab, "*STCH", 0X54, 3);
    insert(op_tab, "LDF", 0X70, 3);
    insert(op_tab, "ADD", 0X18, 3);
    insert(op_tab, "FIX", 0XC4, 1);
    insert(op_tab, "*RSUB", 0X4C, 3);
    insert(op_tab, "NORM", 0XC8, 1);
    insert(op_tab, "STF", 0X80, 3);
    insert(op_tab, "*LDX", 0X04, 3);
    insert(op_tab, "CLEAR", 0XB4, 2);
    insert(op_tab, "+RSUB", 0X4C, 4);
    insert(op_tab, "ADDF", 0X58, 3);
    insert(op_tab, "+WD", 0XDC, 4);
    insert(op_tab, "+LDCH", 0X50, 4);
    insert(op_tab, "+LDF", 0X70, 4);
    insert(op_tab, "+LDX", 0X04, 4);
    insert(op_tab, "STCH", 0X54, 3);
    insert(op_tab, "+ADD", 0X18, 4);
    insert(op_tab, "+AND", 0X40, 4);
    insert(op_tab, "*SUB", 0X1C, 3);
    insert(op_tab, "STX", 0X10, 3);
    insert(op_tab, "RMO", 0XAC, 2);
    insert(op_tab, "COMPR", 0XA0, 2);
    insert(op_tab, "SHIFTL", 0XA4, 2);
    insert(op_tab, "STL", 0X14, 3);
    insert(op_tab, "+TD", 0XE0, 4);
    insert(op_tab, "ADDR", 0X90, 2);
    insert(op_tab, "STI", 0XD4, 3);
    insert(op_tab, "+TIX", 0X2C, 4);
    insert(op_tab, "*STA", 0X0C, 3);
    insert(op_tab, "JGT", 0X34, 3);
    insert(op_tab, "DIV", 0X24, 3);
    insert(op_tab, "+RD", 0XD8, 4);
}

