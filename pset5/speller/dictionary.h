
// Declares a dictionary's functionality

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include <stdbool.h>
#include "trie.h"
// Maximum length for a word
// (e.g., pneumonoultramicroscopicsilicovolcanoconiosis)
#define LENGTH 45

// Prototypes
bool check(const char *wordt);
bool load(const char *dictionary);
unsigned int size(void);
bool unload(void);
int unload_recursive(node *n);

#endif // DICTIONARY_H
