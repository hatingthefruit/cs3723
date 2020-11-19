// gcc -Wall ebq929-assign5.c -o /tmp/eval
// /tmp/eval "2 + 3 * 6" "8/4" "3=4" "BOB + 5"
// prints:    20          2     0     Error

#include <stdio.h>
#include <string.h>

// Not really very good to have a special number for errors
#define ERR 102413

static double orFn(double x, double y)
{
    return (x != 0 || y != 0 ? 1 : 0);
}

static double andFn(double x, double y)
{
    return (x != 0 && y != 0 ? 1 : 0);
}

static double ltFn(double x, double y)
{
    return (x < y ? 1 : 0);
}

static double eqFn(double x, double y)
{
    return (x == y ? 1 : 0);
}

static double gtFn(double x, double y)
{
    return (x > y ? 1 : 0);
}

static double multFn(double x, double y)
{
    return x * y;
}

static double divFn(double x, double y)
{
    return x / y;
}

static double addFn(double x, double y)
{
    return x + y;
}

static double subFn(double x, double y)
{
    return x - y;
}

typedef struct OPER {
    char oper;
    int precedence;
    double (*func)(double x, double y);
} oper_t;

static oper_t operators[] = {{'|', 1, orFn},  {'&', 2, andFn}, {'<', 3, ltFn},   {'=', 3, eqFn}, {'>', 3, gtFn},
                             {'+', 4, addFn}, {'-', 4, subFn}, {'*', 5, multFn}, {'/', 5, divFn}};
static int numOpers = sizeof(operators) / sizeof(oper_t); // numOpers is 9

// Careful, this is recursive
static double eval(char *expr, int sc, int ec)
{
    int level;
    int i;
    int op;

    // Trim spaces (don't worry about errors here)
    while (expr[sc] == ' ')
        sc++;
    while (expr[ec - 1] == ' ')
        ec--;

    // If just one character, must be a number
    if (sc == ec - 1) {
        char ch = expr[sc];
        // TBD -- if ch is '0' to '9', convert it to a number and return it
        if (ch >= '0' && ch <= '9') {
            return ch - '0';
        }

        return ERR;
    }

    // Must be of the form: left oper right
    for (level = 1; level <= 5; level++) {
        for (op = 0; op < numOpers; op++) {
            // TBD -- if the operator[op] has the right precedence AND
            // TBD -- if we can find operator[op].oper in the substring RIGHT to LEFT
            // TBD -- then recursively call eval() with left then right of the operator[op].oper
            // TBD -- and then if left or right returned ERR, return ERR
            // TBD -- otherwise return operators[op].func(left, right)

            // Look for the operator in the string, from right to left
            for (i = ec; i > sc; i--) {
                // If the operator was found, then recursively evaluate the left side and right side
                if (expr[i - 1] == operators[op].oper) {
                    int left = eval(expr, sc, i - 1);
                    int right = eval(expr, i, ec);

                    // Return ERR if either side returns and ERR
                    if (left == ERR || right == ERR) {
                        return ERR;
                    }
                    else {
                        // Otherwise, evaluate the function for the operator
                        return operators[op].func(left, right);
                    }
                }
            }
        }
    }
    return ERR;
}

static void check(char *expr, double expected)
{
    double result = eval(expr, 0, strlen(expr));
    if (result == expected) {
        printf("Value of %s is %g as expected\n\n", expr, result);
    }
    else {
        printf("Value of %s is %g instead of expected %g\n\n", expr, result, expected);
    }
}

int main(int argc, char *argv[])
{
    int i;

    // Recommend getting these to work one at a time
    check(" 4 ", 4);
    check("9+8", 17);
    check(" 3 + 4 * 5 ", 23);
    check(" 9 - 2 - 1", 6);
    check("3=4 | 5<6 & 7<8", 1);

    for (i = 1; i < argc; i++) {
        char *expr = argv[i];
        double result = eval(expr, 0, strlen(expr));
        if (result == ERR) {
            printf("Value of %s is an Error\n\n", expr);
        }
        else {
            printf("Value of %s is %g\n\n", expr, result);
        }
    }
}
