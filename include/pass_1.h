/*
 * pass_1.h
 * Header file for all Pass 1 related functions and macros.
 *
 * Author: Jake Wilson
 * Date: March 8, 2015
 */

void add_literals(Stack *lit_stack, HashTable *sym_tab, int *loc_ctr, int *line_num);
void print_line(int line_num, int loc_ctr, char *line);
void add_to_sym_tab(HashTable *sym_tab, char *symbol, int loc_ctr);
void increment_loc_ctr(HashTable *op_tab, int *loc_ctr, char **tokens, HashTable *sym_tab, Stack *lit_stack, int *line_num);
int get_bytes(char *str);
int increment_loc(int *loc_ctr, HashTable *op_tab, char *op);
void pass_1(FILE *pgm, HashTable *sym_tab, HashTable *op_tab);
