/*
 * hash_table.h
 * General header file for the hash table.
 *
 * Author: Jake Wilson
 * Date:   January 12, 2015
 */

#define TABLE_SIZE 150
#define KEY_SIZE   10

typedef struct Node {
    struct Node *n;
    char *key;
    int value;
    int format; // optional format field (for use by OPTAB only)
} Node;

typedef Node * HashTable;

HashTable *new_hashtable();
Node *new_node();
void insert(HashTable *table, const char *key, int value, int format);
void insert_sym(HashTable *table, const char *key, int value);
int hash(const char *key);
Node *find(HashTable *table, const char *key);
void print(HashTable *table);
