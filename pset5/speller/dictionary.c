// Implements a dictionary's functionality

#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 197371;

// Hash table
node *table[N];

// Number of words read in from dictionary
int numwords = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    for (node *n = table[hash(word)]; n != NULL; n = n->next)
    {
        if (strcasecmp(n->word, word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    //Hash function due to http://www.cse.yorku.ca/~oz/hash.html
    unsigned long val = 5381;

    for (int i = 0, n = strlen(word); i < n; i++)
    {
        val = ((val << 5) + val) + tolower(word[i]);
    }

    return (unsigned int) val % N;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    FILE *dicfile = fopen(dictionary, "r");
    if (!dicfile)
    {
        printf("Could not open dictionary file.");
        return false;
    }

    char word[LENGTH + 1];
    int index;

    while (fscanf(dicfile, "%s", word) != EOF)
    {
        node *n = malloc(sizeof(node));
        strcpy(n->word, word);
        index = hash(word);
        if (table[index] == NULL)
        {
            n->next = NULL;
            table[index] = n;
        }
        else
        {
            n->next = table[index]->next;
            table[index]->next = n;
        }
        numwords++;
    }

    fclose(dicfile);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return numwords;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    int numfreed = 0;
    node *n = NULL, *tmp = NULL;
    for (int i = 0; i < N; i++)
    {
        n = table[i];
        while (n != NULL)
        {
            tmp = n;
            n = n->next;
            free(tmp);
            numfreed++;
        }
    }
    return numfreed == numwords;
}