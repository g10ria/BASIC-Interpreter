#ifndef evals_h

#define evals_h

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include "./types.h"

#include "../cson/headers/hashmapLite.h"

int evaluateExp(struct expression*, struct entry* map);

void eval(struct statement*, int, int*);

#endif