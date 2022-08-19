#ifndef hashmapLite_h

#define hashmapLite_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "./hashfunctions.h"

struct entry;

struct entry* initializeHashmap(char* initialValue);

void addEntry(struct entry *ent, struct entry *map);

char *get(char *key, struct entry *map);

void put(char *key, char *value, struct entry *map);

#endif