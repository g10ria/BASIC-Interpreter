#ifndef interpreter_h

#define interpreter_h

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include "./types.h"

#define MAX_LINES 512 // todo: dynamic sizing?
#define MAX_LINE_LENGTH 256

#include "./parser.h"
#include "./scanner.h"
#include "./evals.h"

void initialize(void);
void addLine(char*);

#endif