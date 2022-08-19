#ifndef types_h

#define types_h

struct expression
{
    struct expression *exp1;
    char* exp2;
    char op;
};

union argument {
    char *str;
    int num;
    struct expression *exp;
    struct statement *sta;
};

// pseudo-polymorphism
struct statement
{
    char type; // denotes the "subclass"

    union argument arg1;
    union argument arg2;
    union argument arg3;
    union argument arg4;
};

struct token
{
    char type;
    /**
     * k for keyword
     * v for varname
     * n for number
     * o for operand
     */
    char *val;
};

#endif