/*
 * file_io.h
 * Header file for sicasm file operations.
 *
 * Author: Jake Wilson
 * Date: March 9, 2015
 */

#define BAD_ARGS 1
#define BAD_FILE 2

#include "hash_table.h"

void read_file(HashTable *table, FILE *fp);
int is_letter(char c);
int is_pound(char c);
int is_at_sign(char c);
int is_digit(char c);
int is_newline(char c);
int is_cr(char c);
