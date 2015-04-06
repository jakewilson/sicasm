/*
 * sicasm.h
 * Header for main assembler functions, like file i/o.
 *
 * Author: Jake Wilson
 * Date: March 3, 2015
 */

#define PASS_1 1
#define PASS_2 2

#define LST_EXT ".lst"
#define OBJ_EXT ".obj"

#include "error.h"
#include "hash_table.h"
#include "stack.h"
#include "gen_ops.h"
#include "pass_1.h"
#include "pass_2.h"
