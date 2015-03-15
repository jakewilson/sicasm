/*
 * pass_1.h
 * Header file for all Pass 1 related functions and macros.
 *
 * Author: Jake Wilson
 * Date: March 8, 2015
 */

char **tokenize(char *line);
void pass_1(FILE *pgm, HashTable *sym_tab, HashTable *op_tab);
