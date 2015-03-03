/*
 * sicasm.h
 * Header for main assembler functions, like file i/o.
 *
 * Author: Jake Wilson
 * Date: March 3, 2015
 */
void read_file(HashTable *table, FILE *fp);
int is_letter(char c);
int is_pound(char c);
int is_at_sign(char c);
int is_digit(char c);
int is_newline(char c);
int is_cr(char c);
