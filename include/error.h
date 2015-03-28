/*
 * Header file for error codes for SIC/XE.
 *
 * Author: Jake Wilson
 * Date:   March 26, 2015
 */

typedef struct Error {
    int line;
    int code;
} Error;

Error sic_error;
int error_found;

/* Error codes */
#define NO_ERROR         0
#define NEGATIVE_OPERAND 1
#define EMPTY_ARG        2
#define DUPLICATE_SYMBOL 3
#define ODD_BYTES        4
#define INVALID_LIT_CHAR 5
#define INVALID_QUOTES   6

void write_error(int line);
void set_error(int code);
