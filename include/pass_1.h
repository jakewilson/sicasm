/*
 * pass_1.h
 * Header file for all Pass 1 related functions and macros.
 *
 * Author: Jake Wilson
 * Date: March 8, 2015
 */

void add_to_sym_tab(HashTable *sym_tab, char *symbol, int loc_ctr);
void increment_loc_ctr(HashTable *op_tab, int *loc_ctr, char **tokens);
int get_bytes(char *str);
int increment_loc(int *loc_ctr, HashTable *op_tab, char *op);
char **tokenize(char *line);
void pass_1(FILE *pgm, HashTable *sym_tab, HashTable *op_tab);
void free_tokens(char **tokens);
