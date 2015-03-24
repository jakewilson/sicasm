/*
 * sicasm.h
 * Header for main assembler functions, like file i/o.
 *
 * Author: Jake Wilson
 * Date: March 3, 2015
 */

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

#include "hash_table.h"
#include "stack.h"
#include "gen_ops.h"
#include "pass_1.h"

