/*
 * Source file for writing errors.
 *
 * Author: Jake Wilson
 * Date:   March 26, 2015
 */

#include <stdio.h>

#include "../include/error.h"

void write_error() {
    switch (sic_error.code) {
        case NEGATIVE_OPERAND:
            printf("Negative operand on line %d.", sic_error.line);
            break;
    }
}
