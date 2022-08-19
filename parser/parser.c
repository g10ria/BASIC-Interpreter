#include "../headers/parser.h"

struct token *t; // current token

/**
 * Parses an arithmetic expression according to this grammar:
 * expr -> expr next
 * next -> + num | - num
 * num is just a number
 */
struct expression *parseExpression(char *inp, int length)
{
    // printf("parsing expression %s\n", inp);

    struct expression *e = malloc(sizeof(struct expression));

    int opIndex = length - 1;

    // it is a digit
    while (isdigit(inp[opIndex]) != 0 && opIndex > 0)
        opIndex--;

    if (opIndex == 0)
    {
        e->exp2 = &(inp[opIndex]);
        e->op = '\0';

        return e;
    }
    else
    {
        e->exp2 = &(inp[opIndex + 1]);
        e->op = inp[opIndex];
        struct expression *e2 = parseExpression(inp, opIndex);
        e->exp1 = e2;

        return e;
    }
}

/**
 * Parses a statement according to its type
 * (Deduces type from the first 1-2 characters in the line of code)
 * 
 * @return a pointer to the parsed statement
 */
struct statement *parseStatement()
{
    struct statement *s = malloc(sizeof(struct statement));
    s->type = (t->val)[0];
    if (s->type == 'I' && (t->val)[1] == 'N')
        s->type = 'N'; // INPUT (not IF)

    t++;

    union argument arg1;
    union argument arg2;
    union argument arg3;
    union argument arg4;

    // rem, let, print, nput, goto, if, end
    switch (s->type)
    {
    case ('R'): // REM
        while(t->type=='v' || t->type=='n')
            t++;
        arg1.str = "";
        break;

    case ('L'): // LET
        arg1.str = t->val;
        t += 2; // skip the '='

        int len = 0;
        while (t->val[len] != '\0')
            len++;
        arg2.exp = parseExpression(t->val, len);
        t++;
        break;

    case ('P'):; // PRINT

        int len2 = 0;
        while (t->val[len2] != '\0')
            len2++;
        arg1.exp = parseExpression(t->val, len2);

        t++;
        break;

    case ('N'): //  (I)NPUT
        arg1.str = t->val;
        t++;
        break;

    case ('G'):                  // GOTO
        arg1.num = atoi(t->val);
        t++;
        break;

    case ('I'):; // IF

        int len4 = 0;
        while (t->val[len4] != '\0')
            len4++;
        arg1.exp = parseExpression(t->val, len4);
        t++;
        arg2.str = t->val;
        t++;

        int len5 = 0;
        while (t->val[len5] != '\0')
            len5++;
        arg3.exp = parseExpression(t->val, len5);
        t++;

        arg4.sta = parseStatement();

        break;

    case ('E'):
        break;
    }

    s->arg1 = arg1;
    s->arg2 = arg2;
    s->arg3 = arg3;
    s->arg4 = arg4;

    return s;
}

/**
 * Parses a program given its array of tokens
 * 
 * @param tokens the array of tokens
 * @param numStatements the total # of statements (lines of code)
 * 
 * @return an array of statements
 */
struct statement *parse(struct token *tokens, int numStatements)
{
    t = tokens;

    struct statement *s = malloc(numStatements * sizeof(struct statement));
    int currStatement = 0;

    // parse a program
    while (currStatement < numStatements)
    {
        s[currStatement] = *parseStatement();
        currStatement++;
    }

    return s;
}