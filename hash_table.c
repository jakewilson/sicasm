/*
 * p1.c
 * Contains all functions (besides main) used in Project 1.
 *
 * Author: Jake Wilson
 * Date:   January 19, 2015
 */

#include "hash_table.h"
#include <stdlib.h>
#include <string.h>

/*
 * Attempts to find a key in the hash table.
 * @param table:
 *          the Hash Table to look up the key in
 * @param key:
 *          the key to find
 */
Node *lookup(HashTable *table, const char *key) {
    int idx = hash(key);
    Node *n = table[idx];
    while (n != NULL) {
        if (strcmp(n->key, key) == 0) {
             return n;
         }
        n = n->n;
    }
    return NULL;
}

/*
 * Adds a key and a value to a Hash Table. If a collision occurs,
 * it is added to the end of the linked list at the index of collision.
 * @param table:
 *          the Hash Table to modify
 * @param key:
 *          the key of the node
 * @param value:
 *          the value of the node
 */
void add_to_table(HashTable *table, const char *key, int value) {
    int idx = hash(key);
    if (lookup(table, key) != NULL) { // make sure the key isn't already in the table
        printf("ERROR %s already exists at location %d.\n", key, idx);
    } else {
        if (table[idx] == NULL) {
            table[idx] = new_node();
            strcpy(table[idx]->key, key);
            table[idx]->value = value;
        } else {
            printf("%s collided with %s at index %d.\n", key, table[idx]->key, idx);
            Node *n = new_node();
            strcpy(n->key, key);
            n->value = value;
            n->n = table[idx];
            table[idx] = n;
        }
        printf("Stored %s %d at location %d.\n", key, value, idx);
    }
}

        
/*
 * Hashes the passed in key by taking the modulus of 
 * the key's first letter with TABLE_SIZE.
 * @param key:
 *              the key to hash
 * @return:
 *              the hash
 */
int hash(const char *key) {
    return key[0] % TABLE_SIZE;
}

/*
 * Allocates and initializes a new Node
 * @return:
 *              a newly initialized Node
 */
Node *new_node() {
    Node *n = memset(malloc(sizeof(Node)), 0, sizeof(Node));
    n->key = calloc(10, sizeof(n->key));
    return n;
}

/*
 * Allocates and initializes a new Hash Table
 * @return a newly initialized Hash Table
 */
HashTable *new_hashtable() {
    return calloc(TABLE_SIZE, sizeof(Node));
}

/*
 * Determines if a character is a letter, case-insensitive
 * @param c:
 *          the character to evaluate
 * @return:
 *          a non-zero integer if the character is a letter, zero if not
 */
int is_letter(char c) {
    return (c >= 97 && c <= 122) || (c >= 65 && c <= 90);
}

/*
 * Determines if a character is a digit
 * @param c:
 *          the character to evaluate
 * @return:
 *          a non-zero integer if the character is a digit, zero if not
 */
int is_digit(char c) {
    return (c >= 48 && c <= 57);
}

/*
 * Determines if a character is a newline
 * @param c:
 *          the character to evaluate
 * @return:
 *          a non-zero integer if the character is a newline, zero if not
 */
int is_newline(char c) {
    return (c == 10);
}

/*
 * Determines if a character is a carriage return
 * @param c:
 *          the character to evaluate
 * @return:
 *          a non-zero integer if the character is a carriage return, zero if not
 */
int is_cr(char c) {
    return (c == 13);
}
