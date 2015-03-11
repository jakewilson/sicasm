/*
 * sicasm.h
 * Header for main assembler functions, like file i/o.
 *
 * Author: Jake Wilson
 * Date: March 3, 2015
 */

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

#define NUM_SEGMENTS 4

#include "file_io.h"
#include "pass_1.h"
