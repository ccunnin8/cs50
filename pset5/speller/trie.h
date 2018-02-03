/**
 * includes the struct for each try node
 * and methods to create a trie from a dictionary text file
 * and methods to lookup a word
 */
#ifndef TRIE_H
#define TRIE_H


 #include <stdio.h>
#include <stdlib.h>

 #define OFFSET 97
 #define ALPHABET_SIZE 27
 #define LENGTH 45

//STRUCT
 typedef struct _node
 {
     struct _node *children[ALPHABET_SIZE];
     char word[LENGTH + 1];
 }
 node;


 //prototypes
 int convert_to_index(char c);
 bool has_word(node *n, char *w);
 int link_two_nodes(int index, node *n1);
 void set_word(node *n, char *w);
 node* create_node(void);

#endif
