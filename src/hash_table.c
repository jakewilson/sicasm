/*
 * hash_table.c
 * All hash table functions.
 *
 * Author: Jake Wilson
 * Date:   January 19, 2015
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../include/hash_table.h"

/*
 * Attempts to find a key in the hash table.
 * @param table:
 *          the Hash Table to look up the key in
 * @param key:
 *          the key to find
 */
Node *find(HashTable *table, const char *key) {
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
 * Prints a hash table, without printing the format
 * @param table
 *              the table to print
 */
void print(HashTable *table) {
    int i;
    for (i = 0; i < TABLE_SIZE; i++)
        if (table[i] != NULL)
            printf("%d: %s %X\n", i, table[i]->key, table[i]->value);
}

/*
 * Adds a key, value and a format to a Hash Table. If a collision occurs,
 * it is added to the end of the linked list at the index of collision.
 * @param table:
 *          the Hash Table to modify
 * @param key:
 *          the key of the node
 * @param value:
 *          the value of the node
 * @param format
 *          the format of the node (for use by OPTAB only)
 */
void insert(HashTable *table, const char *key, int value, int format) {
    int idx = hash(key);
    if (find(table, key) == NULL) { // make sure the key is not already in the hash table
        if (table[idx] == NULL) {
            table[idx] = new_node();
            strcpy(table[idx]->key, key);
            table[idx]->value = value;
            table[idx]->format = format;
        } else {
            Node *n = new_node();
            strcpy(n->key, key);
            n->value = value;
            n->format = format;
            n->n = table[idx];
            table[idx] = n;
        }
    }
}

/*
 * Adds a key, value and a format of -1 to a Hash Table. If a collision occurs,
 * it is added to the end of the linked list at the index of collision.
 * @param table:
 *          the Hash Table to modify
 * @param key:
 *          the key of the node
 * @param value:
 *          the value of the node
 */
void insert_sym(HashTable *table, const char *key, int value) {
    insert(table, key, value, -1);
}

        
/*
 * Hashes the passed in key by taking the modulus of the sum
 * of every letter in the key with TABLE_SIZE.
 * @param key:
 *              the key to hash
 * @return:
 *              the hash
 */
int hash(const char *key) {
    int i, hash = 0;
    for (i = 0; i < (int)strlen(key); i++)
        hash += key[i];
    return hash % TABLE_SIZE;
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
 * @return 
 *          a newly initialized Hash Table
 */
HashTable *new_hashtable() {
    return calloc(TABLE_SIZE, sizeof(Node));
}

