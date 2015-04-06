/*
 * Source file for writing errors.
 *
 * Author: Jake Wilson
 * Date:   March 26, 2015
 */

#include <stdio.h>
#include <string.h>

#include "../include/error.h"
#include "../include/gen_ops.h"


/*
 * Writes the appropriate error message to stdout, given the error code
 * @param line
 *              the line number of the error
 */
void write_error(int line) {
    char error[ERROR_LEN] = {0};

    switch (sic_error.code) {
        case NEGATIVE_OPERAND:
            strncpy(error, "Negative operand", ERROR_LEN);
            break;

        case EMPTY_ARG:
            strncpy(error, "Operand must be provided", ERROR_LEN);
            break;

        case DUPLICATE_SYMBOL:
            strncpy(error, "Duplicate symbol", ERROR_LEN);
            break;

        case ODD_BYTES:
            strncpy(error, "Odd number of bytes", ERROR_LEN);
            break;

        case INVALID_LIT_CHAR:
            strncpy(error, "Literal character must be X or C", ERROR_LEN);
            break;

        case INVALID_QUOTES:
            strncpy(error, "Literal must be enclosed in single quotes", ERROR_LEN);
            break;

        case UNDEFINED_INS:
            strncpy(error, "Undefined instruction", ERROR_LEN);
            break;

        case NO_ERROR:
        default: // don't write error if there isn't one
            return;
    }

    error_thrown = TRUE;
    printf("ERROR (pass %d): %s on line %d.\n", error_pass, error, line);
    set_error(NO_ERROR);
}


/*
 * Sets the line number and the code of sic_error
 * @param code
 *              the error code
 */
void set_error(int code) {
    sic_error.code = code;
}
