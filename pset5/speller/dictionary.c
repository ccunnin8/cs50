

// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "trie.h"
#include "dictionary.h"

node* global;
int total = 0;

//keep track of words
int counter = 0;
// Returns true if word is in dictionary else false
bool check(const char *wordt)
{
    //Make another pointer that points to the word
    char checkword[LENGTH + 1];

    strcpy(checkword,wordt);

    // Copy a pointer to the beginning of the trie
    node *ptr = global;

    //Keep track of which character
    int count = 0;

    //loop over the characters 1 by 1 until we hit the end (\0)
    while(checkword[count] != '\0')
    {

        //convert the character to the array index of the lowercase
        checkword[count] = tolower(checkword[count]);

        int index = convert_to_index(checkword[count]);

        //if there is a pointer to another node at the index of the first try point to the next try
        if (ptr->children[index] != NULL)
            ptr = ptr->children[index];

        //if there's not a pointer there it's definitely not a word!
        else
            return false;
        count++;
    }
    //if we got out of the loop that means that we followed the trie all the way down and each letter was there
    //but is there word actually there?
    if (strcmp(ptr->word,checkword) == 0)
        return true;
    else
        return false;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    //initialize constant global which is the ROOT trie to the size of 1 node
    global = malloc(sizeof(node));
    //make a copy of global and call it pt
    if (!global)
    {
        printf("ERROR");
        return false;
    }
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        global->children[i] = NULL;
    }
    strcpy(global->word,"");
    node *ptr = global;
    //open the dictionary w/ error check
    FILE *dict = fopen(dictionary,"r");
    if (!dict)
    {
        fprintf(stderr,"The dictionary you specified could not be located!");
        return false;
    }
    //initialize word
    char w[LENGTH + 1];
    //scan through each line
    while(fscanf(dict,"%s",w) != EOF)
    {
       //iterate over each letter of the word
       int count = 0;
       total++;
       while (w[count] != '\0')
       {
           int index = convert_to_index(w[count]);
           //if there is no pointer at that index
           if (ptr->children[index] == NULL)
           {
               //create a new node
               link_two_nodes(index,ptr);
           }
           ptr = ptr->children[index];
           count++;
       }
       //dereference ptr to have word;
       strcpy(ptr->word,w);
       //point ptr back to global;
       ptr = global;
    }
    fclose(dict);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return global != NULL ? total : 0;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    node *ptr = global;
    if (unload_recursive(ptr) == 0)
        return true;
    else
        return false;
}

int unload_recursive(node *n)
{
    for (int i = 0; i < ALPHABET_SIZE; i++)
    {
        if (n->children[i] != NULL)
        {
            unload_recursive(n->children[i]);
        }
    }
    free(n);
    return 0;
}

