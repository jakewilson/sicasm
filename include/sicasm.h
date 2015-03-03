/*
 * sicasm.h
 * Header for main assembler functions, like file i/o.
 *
 * Author: Jake Wilson
 * Date: 3/3/15
 */
void read_file(HashTable *table, FILE *fp);
int is_letter(char c);
int is_digit(char c);
int is_newline(char c);
int is_cr(char c);
