#ifndef scanner_h

#define scanner_h

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include "./types.h"

#define AVG_TOKENS_PER_LINE 6 // arbitrary number, used for malloc

int equals(char*, char*);
struct token* scanString(char* inp);
struct token* scan(char**, int, int, int*);

#endif