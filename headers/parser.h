#ifndef parser_h

#define parser_h

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include "./types.h"

struct expression* parseExpression(char*, int);
struct statement* parseStatement(void);
struct statement* parse(struct token*, int);

#endif