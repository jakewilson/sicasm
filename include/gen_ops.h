/*
 * gen_ops.h
 * Header file for sicasm general operations.
 *
 * Author: Jake Wilson
 * Date: March 9, 2015
 */

#define BAD_ARGS 1
#define BAD_FILE 2

#define TRUE  1
#define FALSE 0

/* The segments of a sicasm line */
#define LABEL   0
#define OPCODE  1
#define ARG     2
#define COMMENT 3

/* The maximum length of each sicasm line segment */
#define LABEL_LEN    8
#define OPCODE_LEN   8
#define ARG_LEN     11
#define COMMENT_LEN 39

#define SEGMENT_LENGTHS LABEL_LEN,\
                        OPCODE_LEN,\
                        ARG_LEN,\
                        COMMENT_LEN

/* The starting points of each segment on a line */
#define LABEL_START    0
#define OPCODE_START   9
#define ARG_START     18
#define COMMENT_START 31

#define SEGMENT_STARTING_POSITIONS LABEL_START,\
                                   OPCODE_START,\
                                   ARG_START,\
                                   COMMENT_START

#define NUM_SEGMENTS 4

#define LINE_MAX_SIZE 80

#define WORD_LEN 3

int is_literal(char *str);
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
char **tokenize(char *line);
void free_tokens(char **tokens);
