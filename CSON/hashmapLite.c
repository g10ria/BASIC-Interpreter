/**
 * Simple hashmap in C. Only includes adding and fetching by key,
 * does not include removing key-value pairs.
 * 
 * Provide keys and values as strings. Pick a hash function
 * from ./hashfunctions.c and pick a map size in the variable size.
 */

#include "./headers/hashmapLite.h"
#include "./headers/hashfunctions.h"

int size = 256; // size of 1 level of hashmap

int (*hash)(char *key, int size) = &sum;

// pseudo-linked list
struct entry {
    char *key;          // unhashed key as a string
    char *val;          // type as a raw string
    struct entry *next; // next in the list
};

/**
 * Allocates space for the map and initializes null values
 */
struct entry* initializeHashmap(char* initialValue)
{
    struct entry *map; // entry array

    map = malloc(size * sizeof(struct entry));

    for (int i = 0; i < size; i++)
    {
        map[i].key = initialValue;
        map[i].next = NULL;
    }

    return map;
}

/**
 * Adds an entry to the map. Three cases: the address is unoccupied in the
 * array, the address is occupied and the key exists, and the address
 * is occupied but the key does not exist.
 * 
 * @param ent pointer to the entry to add
 */
void addEntry(struct entry *ent, struct entry* map)
{
    int address = hash(ent->key, size);
    struct entry *current = map + address;

    // empty list, add key-value pair directly
    if (*(current->key) == 0)
        map[address] = *ent;
    else
    {
        // get to the tail of the list or the first matching key
        while (current->next != NULL && strcmp(ent->key, current->key) != 0)
            current = current->next;

        // key exists, just replace the value
        if (strcmp(ent->key, current->key) == 0)
            current->val = ent->val;
        else
            current->next = ent; // otherwise concat it to the list
    }

    return;
}
/**
 * Gets a value from the hashmap given a key
 * 
 * @param key the key
 */
char *get(char *key, struct entry* map)
{
    int address = hash(key, size);
    struct entry *current = map + address;

    int strComparison = strcmp(key, current->key);

    while (current->next != NULL && strComparison != 0)
    {
        current = current->next;
        strComparison = strcmp(key, current->key);

    }

    return strComparison == 0 ? current->val : NULL;
}

/**
 * Puts a new value into the map given a key and a value
 * 
 * @param key the key
 * @param value the value
 */
void put(char *key, char *value, struct entry* map)
{
    struct entry e;

    e.key = key;
    e.val = value;
    e.next = NULL;

    addEntry(&e, map);

    get(e.key, map);

    return;
}