/*
 * include.h
 * General header file for Project 1.
 *
 * Author: Jake Wilson
 * Date:   January 12, 2015
 */

#include <stdio.h>

#define TABLE_SIZE 52
#define KEY_SIZE   10

#define BAD_ARGS 1
#define BAD_FILE 2

#define TRUE  1
#define FALSE 0

typedef struct Node {
    struct Node *n;
    char *key;
    int value;
} Node;

typedef Node * HashTable;

HashTable *new_hashtable();
Node *new_node();
void read_file(HashTable *table, FILE *fp);
int is_letter(char c);
int is_digit(char c);
int is_newline(char c);
int is_cr(char c);
void add_to_table(HashTable *table, const char *key, int value);
int hash(const char *key);
Node *lookup(HashTable *table, const char *key);
