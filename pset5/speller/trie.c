/**
 * includes the struct for each try node
 * and methods to create a trie from a dictionary text file
 * and methods to lookup a word
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include "trie.h"

 //return the correct number to link to according to the ASCII character
 int convert_to_index(char c)
 {
     if (c != '\0' && c != '\'')
      return (int)c - OFFSET;
     else if (c == '\'')
      return ALPHABET_SIZE - 1;
     else
      return ALPHABET_SIZE - 1;
 }

 //checks to see if the word is at the end of the node
 bool has_word(node *n, char *w)
 {
     return (strcmp(n->word,w) == 0);
 }

 //connect two nodes together
 //return 0 for success, 1 for error
 int link_two_nodes(int index, node *n)
 {
     node *new_node = create_node();
     if (!new_node)
     {
         printf("an error occured");
         return -1;
     }
     n->children[index] = new_node;
     return 0;
 }

 //set the word of the final node in a key to the dictionary word
 void set_word(node *n, char *w)
 {
     strcpy(n->word,w);
 }

//create a node (without a word set)
node *create_node(void)
{
    node *n = malloc(sizeof(node));
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
     n->children[i] = NULL;
    }
    strcpy(n->word,"");
    return n;
}
