#include "../headers/scanner.h"

/**
 * Helper for comparing two strings
 * 
 * @param one the first string
 * @param two the second string
 * @return 1 if the two are equal, 0 otherwise
 * 
 * Edit: I didn't know that strcmp existed when I wrote this,
 * but I'm too lazy to remove it now :)
 */
int equals(char *one, char *two)
{
    int ind = 0;

    while (one[ind] != '\0' && two[ind] != '\0')
    {
        if (one[ind] != two[ind])
            return 0;
        ind++;
    }

    return one[ind] == '\0' && two[ind] == '\0' ? 1 : 0;
}

/**
 * Deduces the type of a string and returns a token with the appropriate type
 * 
 * @param inp input string
 * @return a token with the string and the correct type
 */
struct token *scanString(char *inp)
{
    struct token *t = malloc(sizeof(struct token));
    t->val = inp;

    int inpInd = 0;
    char c = inp[0];

    if (isdigit(c) == 0)
    { // keyword, varname, or operand

        if (c == '+' || c == '-' || c == '*' || c == '/')
            t->type = 'o'; // operand
        else if (equals(inp, "REM") |
                 equals(inp, "LET") |
                 equals(inp, "PRINT") |
                 equals(inp, "INPUT") |
                 equals(inp, "GOTO") |
                 equals(inp, "IF") |
                 equals(inp, "END") == 1)
            t->type = 'k'; // keyword
        else
            t->type = 'v'; // variable
    }
    else
        t->type = 'n'; // number

    return t;
}

/**
 * Given all the lines in the program, returns an array of tokens
 * 
 * @param lines array of the lines in the program
 * @param numLines total # of lines
 * @param firstLine line number of the first line the program
 * @param next the "next" array that the interpreter maintains (see design doc)
 */
struct token *scan(char **lines, int numLines, int firstLine, int *next)
{
    struct token *tokens = malloc(numLines * AVG_TOKENS_PER_LINE * sizeof(struct token));

    int nextLine = firstLine;

    int numTokens = 0;

    char *line;
    // iterate over every line
    while (nextLine != -1)
    {
        line = lines[nextLine];

        // splitting the line up by spaces
        int currInd = 0;
        while (line[currInd] != '\0')
        {
            if (line[currInd] == ' ')
                currInd++;
            else
            {
                int spaceInd = currInd;
                while (line[spaceInd] != ' ' && line[spaceInd] != '\0')
                    spaceInd++;

                // currInd = start of the word
                // spaceInd = blank space at end of the word
                char *nextStr = malloc(spaceInd - currInd + 1); // size + 1
                memcpy(nextStr, line + currInd, spaceInd - currInd);
                nextStr[spaceInd - currInd] = '\0';

                tokens[numTokens] = *scanString(nextStr);
                numTokens++;

                currInd = spaceInd;
            }
        } // splitting up the line by spaces
        nextLine = next[nextLine];
    }

    return tokens;
}