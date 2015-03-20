/*
 * gen_ops.h
 * Header file for sicasm general operations.
 *
 * Author: Jake Wilson
 * Date: March 9, 2015
 */

#define BAD_ARGS 1
#define BAD_FILE 2

#include "hash_table.h"

int convert_to_pos_int(char *str, int *num, int base);
int convert_to_int(char *str, int *num, int base);
char *trim(char *str);
int is_empty(char *str);
int is_comment_line(char *line);
int is_blank_line(char *line);
int is_letter(char c);
int is_pound(char c);
int is_at_sign(char c);
int is_digit(char c);
int is_newline(char c);
int is_cr(char c);
