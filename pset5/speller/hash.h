/**
 * Defines maximum amount of nodes for hash table
 * Defines hash function
 * Defines nodes to be used in hash table
 **/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUCKETS 100
#define LENGTH 45

// Node declaration
typedef struct _node
{
    char word[LENGTH + 1];
    struct _node *next = NULL;
}
node;

//hash function
//djb2 from http://www.cse.yorku.ca/~oz/hash.html
unsigned long hashstring(char *str)
{
    unsigned long hash = 5381;
    int c = 0;

    while (c == *str++)
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

    return hash % BUCKETS;
}

//create a new node
node* create_node(char *word)
{
    node *n = malloc(sizeof(node));
    if (!n)
    {
        fprintf(stderr, "memory error");
        return NULL;
    }
    strcpy(n->word,word);
    return n;
}

//add a node to the beginning of list
void add_node(node *first, node *second, node *newest)
{
    newest->next = second;
    first->next = newest;
}