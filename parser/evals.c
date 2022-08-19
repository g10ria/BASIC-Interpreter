#include "../headers/evals.h"

/**
 * Evaluates an expression
 * 
 * @param e the expression
 * @return the value of the expression
 */
int evaluateExp(struct expression *e, struct entry* map)
{
    if (e->op == '\0') // no operand, it's just a raw value
    {
        char *var = get(e->exp2, map);

        // raw value, not a variable
        if (var == NULL)
            return atoi(e->exp2);

        return atoi(var);
    }
    else
    {
        int exp2 = atoi(e->exp2);
        int exp1 = evaluateExp(e->exp1, map);

        switch (e->op)
        {
        case ('+'):
            return exp1 + exp2;
        case ('*'):
            return exp1 * exp2;
        case ('-'):
            return exp1 - exp2;
        case ('/'):
            return exp1 / exp2;
        default:
            printf("error! invalid math operator");
            exit(1);
        }
    }
}

/**
 * Helper function, converts a number to a string
 * 
 * @param num the number
 * @return the number as a string
 */
char *numToString(int num)
{
    int places = 0;

    int n = num;
    while (n != 0)
    {
        places++;
        n /= 10;
    }

    char *res = malloc(places * sizeof(char));
    for (int i = places - 1; i >= 0; i--)
    {
        res[i] = num % 10 + '0';
        num /= 10;
    }

    return res;
}

/**
 * Evaluates a program given an array of statements
 * 
 * @param statements array of statements
 * @param numStatements # of statements in the program
 * @param lineToIndex array of line to index (see convert function in interpreter.c)
 */
void eval(struct statement *statements, int numStatements, int *lineToIndex)
{
    char initialValue = '\0';
    struct entry* map = initializeHashmap(&initialValue); // for storing variables

    struct statement *s = statements; // current statement
    int pause = 0;

    for (int i = 0; i < numStatements; i++)
    {

        if (pause == 0)
            s = statements + i;
        else
            pause = 0;

        switch (s->type)
        {

        case ('R'): // REM
            break;

        case ('L'):; //LET
            int value = evaluateExp(s->arg2.exp, map);
            put(s->arg1.str, numToString(value), map);
            break;

        case ('P'):; // PRINT
            int result = evaluateExp(s->arg1.exp, map);
            printf("%d\n", result);
            break;

        case ('N'):;        // (I)NPUT
            char inp[1024]; // arbitrary value
            scanf("%[^\n]%*c", inp);
            int answer = atoi(inp);
            put(s->arg1.str, numToString(answer), map);
            break;

        case ('G'):; // GOTO
            int line = s->arg1.num;
            int index = lineToIndex[line - 1];
            i = index - 1;
            s = statements + index - 1;
            break;

        case ('I'):;
            int left = evaluateExp(s->arg1.exp, map);
            int right = evaluateExp(s->arg3.exp, map);
            char op = *(s->arg2.str);

            int cond = 0;
            switch (op)
            {
            case ('='):
                cond = left == right;
                break;
            case ('<'):
                cond = left < right;
                break;
            case ('>'):
                cond = left > right;
                break;
            default:
                printf("error! invalid boolean operator");
            }

            if (cond)
            {
                s = s->arg4.sta;
                i--;
                pause = 1;
            }

            break;

        case ('E'): // END
            i = numStatements;
            break;
        }
    }

    free(map);
}