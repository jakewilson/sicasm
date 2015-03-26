/*
 * Source file for writing errors.
 *
 * Author: Jake Wilson
 * Date:   March 26, 2015
 */

#include <stdio.h>

#include "../include/error.h"


/*
 * Writes the appropriate error message to stdout, given the error code
 */
void write_error() {
    switch (sic_error.code) {
        case NEGATIVE_OPERAND:
            printf("Negative operand on line %d.", sic_error.line);
            break;
    }
}


/*
 * Sets the line number and the code of sic_error
 * @param line
 *              the line number of the error
 * @param code
 *              the error code
 */
void set_error(int line, int code) {
    sic_error.line = line;
    sic_error.code = code;
}
