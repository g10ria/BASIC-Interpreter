#include "./headers/interpreter.h"

char **lines;       // array of the lines
int numLines = 0;   // number of lines in the program
int *next;          // stores the next line of every line
int firstLine = -1; // line number of the first line

int *nextConverted; // "next" indices converted to line indices (see convert function)

/**
 * Allocates needed space and initializes the necessary values for the program
 */
void initialize()
{
    next = malloc(MAX_LINES * sizeof(int));
    nextConverted = malloc(MAX_LINES * sizeof(int));
    for (int i = 0; i < MAX_LINES; i++)
        next[i] = -1;

    lines = malloc(MAX_LINES * sizeof(char *));
    for (int i = 0; i < MAX_LINES; i++)
        lines[i] = "";
}

/**
 * Adds a new line to the program
 * Strips the line number from the string before adding it
 * 
 * @param input the line as a string
 */
void addLine(char *input)
{
    int line = atoi(input);

    int spaceInd = 0;
    while (input[spaceInd] != ' ')
        spaceInd++;
    input = input + spaceInd + 1;

    if (firstLine == -1 || line < firstLine)
        firstLine = line;

    if (lines[line][0] == '\0')
        numLines++;

    lines[line] = input;

    /**
     * Updates the nextLines array (goes "down" the array
     * and updates "next values")
     */
    int nextValue = next[line];
    int currNextValue = nextValue;
    int currNextValueIndex = line - 1;

    while (currNextValue == next[line] && currNextValueIndex >= 0)
    {
        next[currNextValueIndex] = line;

        currNextValueIndex--;
        currNextValue = next[currNextValueIndex];
    }

    return;
}

/**
 * Converts the "next" array to an "index" array
 * For example, if there are two lines 10 and 20 in the program,
 * the "next" array will have indices 0-9 equal to 10 and indices
 * 10-19 equal to 20. This will just convert indices 0-9 to 0 and
 * indices 10-19 to 1, etc. It's used for the GOTO function.
 * (New values are stored in a new array, the "next" array is untouched)
 */
void convertLinesToIndex()
{
    int current = 0;
    int previousNext = next[0];

    for (int i = 0; i < MAX_LINES; i++)
    {

        if (next[i] != previousNext)
        {
            current++;
            previousNext = next[i];
        }
        // printf("%d goes to %d\n", i, current);
        nextConverted[i] = current;

        if (i < MAX_LINES - 1 && next[i + 1] == -1)
            break;
    }

    return;
}

/**
 * Actually runs the program for the "RUN" command
 */
void runProgram()
{
    struct token *tokens = scan(lines, numLines, firstLine, next);
    struct statement *statements = parse(tokens, numLines);
    convertLinesToIndex();
    eval(statements, numLines, nextConverted);

    return;
}

/**
 * Lists each line of the program for the "LIST" command
 */
void listProgram()
{
    int nextLine = firstLine;

    while (nextLine != -1)
    {
        printf("%d %s\n", nextLine, lines[nextLine]);
        nextLine = next[nextLine];
    }

    return;
}

/**
 *  Clears the program and removes all lines for the "CLEAR" command
 */
void clearProgram()
{
    for (int i = 0; i < MAX_LINES; i++)
    {
        next[i] = -1;
        lines[i] = "";
    }
    numLines = 0;
    firstLine = -1;

    return;
}

/**
 * Prints a help message for the "HELP" command
 */
void printHelp()
{
    printf("AVAILABLE COMMANDS:\n\n");
    printf("\tImmediate:\n\n");

    printf("\tHELP\n");
    printf("\t\tPrints this help message.\n");
    printf("\tRUN\n");
    printf("\t\tRuns the current program.\n");
    printf("\tLIST\n");
    printf("\t\tLists the current lines in the program.\n");
    printf("\tCLEAR\n");
    printf("\t\tClears all lines in the current program.\n");
    printf("\tQUIT\n");
    printf("\t\tQuits the interpreter.\n");

    printf("\n\n");

    printf("\tBASIC:\n\n");
    printf("\t<LINE> LET <VARIABLE> = <VALUE>\n");
    printf("\t\tExample: 10 LET X = 10\n");

    printf("\t<LINE> PRINT <VARIABLE>\n");
    printf("\t\tExample: 15 PRINT X\n");

    printf("\t<LINE> IF <CONDITION> <COMMAND>\n");
    printf("\t\tExample: 20 IF X = 10 PRINT X\n");

    printf("\t<LINE> REM <COMMENT>\n");
    printf("\t\tExample: 35 REM THIS IS A COMMENT\n");

    printf("\t<LINE> INPUT <VARIABLE>\n");
    printf("\t\tExample: 40 INPUT X\n");

    printf("\t<LINE> GOTO <LINE>\n");
    printf("\t\tExample: 45 GOTO 55\n");

    printf("\t END\n");
    printf("\t\tExample: 55 END\n");

    printf("\n\n");

    return;
}

/**
 * For the "QUIT" command
 */
void quit()
{
    free(lines);
    free(next);
    free(nextConverted);

    exit(0);
}

/**
 * Helper function to retrieve the length of a string
 * 
 * @param str the input string
 * @return the length of the string
 */
int strLen(char *str)
{
    int len = 0;
    while (str[len] != '\0')
        len++;
    return len + 1;
}

/**
 * Main method to run the interpreter
 * Lacking in error handling :P
 */ 
int main()
{
    initialize();

    printf("Welcome to your simplified BASIC interpreter.\n\n\
    \tMAX PROGRAM LENGTH: %d lines\n\
    \tMAX LINE LENGTH: %d characters\n\
    \tUse CTRL-C to quit the interpreter.\n\n",
           MAX_LINES, MAX_LINE_LENGTH);

    char *l = malloc(MAX_LINE_LENGTH * sizeof(char));

    while (1 == 1)
    {
        scanf("%[^\n]%*c", l);

        if (*l == '\0')
            continue; // skip empty lines

        if (strcmp(l, "RUN") == 0)
            runProgram();
        else if (strcmp(l, "LIST") == 0)
            listProgram();
        else if (strcmp(l, "CLEAR") == 0)
            clearProgram();
        else if (strcmp(l, "HELP") == 0)
            printHelp();
        else if (strcmp(l, "QUIT") == 0)
            quit();
        else
        {
            // make a copy of the string
            int length = strLen(l);
            char *l2 = malloc(length * sizeof(char));
            for (int i = 0; i < length; i++)
                l2[i] = l[i];

            addLine(l2);
        }
    }

    free(lines);
    free(next);
    free(nextConverted);

    return 0;
}