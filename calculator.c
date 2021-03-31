#define _GNU_SOURCE
#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include "log.h" //For some additional logarithm functions

#define ARRAY_SIZE 9
#define GOLDEN_RT ((1 + sqrt(5)) * 0.5) //Golden Ratio
#define APERY_CONST 1.202056903159 //Apery's Constant
#define M_SQRT_3 (sqrt(3)) //Theodorus' Constant (Square root of 3)
#define G 0.915965594177219 //Catalan's Constant

//Used to solve equation
double solveEquation(char* input);

//Get some numbers
long double convertFloat(char* input, long double total);
unsigned int numberOfOperations(char* input);

//String char checking
int validNext(char c);
int validateOperation(char c);
int validateRoot(char c);

//Factorial functions
int nCr(long double num1, long double num2);
int nPr(long double num1, long double num2);

//Change strings
char* removeChar(char* input, int index, int c);
char* assignrootOperations(char* rootOperations, int numNum, char* copy, int i, char state);
char* setUp(char* copy);

//Root functions
float squareRoot(float number);
float fifthRoot(float number);

int main(void)
{
    char* getEquation = NULL;
    float result = 0.0;

    system("clear");
    printf("Enter a bunch of equations below: \n");

    while (1)
    {
        getEquation = get_string("");
        result = solveEquation(getEquation);

        //Erase equation typed by user
        printf("\033[A\033[2K", stdout);
        rewind(stdout);

        printf("%s = %f\n", getEquation, result);
        printf("Note that this result did not take BEDMAS into account.\n\n");
    }
}

double solveEquation(char* input)
{
    static double ans = 0.0;
    unsigned int times = 0, location = 0;
    short copyIndexStart = 0, multNeg = 1, x = 0, root = 0, numNum = 1;
    float divide = 10.0, lastCheck = 0.0;
    long double last = 0.0, total = 0.0;
    char state = '\0', whichNum = '0', lastNum = '0';
    char* copy = (char*) malloc(strlen(input) * sizeof(char));
    char* rootOperations = NULL;

    //Copy input to copy
    strcpy(copy, input);

    //Check for negative first number or stuff like subtracting negative numbers and adding negative numbers
    setUp(copy);

    //Used to check for square root, cube roo, quartic root, and quintic root
    for (int i = 0; i < strlen(copy); i++)
    {
        if (!isascii(copy[i]))
            return NAN;
        if (isalpha(copy[i]))
        {
            char* arr = (char*) malloc(sizeof(char) * ARRAY_SIZE);
            copyIndexStart = i;
            strncat(arr, &copy[copyIndexStart], ARRAY_SIZE);
            if (copy[i] == 'm' || copy[i] == 'e' || copy[i] == 'E')
                continue;

            else if (copy[i] == 's')
            {
                if (strncmp(arr, "sqrt(", 5) == 0)
                {
                    copy[copyIndexStart] = '#';
                    removeChar(copy, copyIndexStart, 5);
                    root++;
                    i += 4;
                }
                else if (strncmp(arr, "square(", 7) == 0)
                {
                    copy[copyIndexStart] = '<';
                    removeChar(copy, copyIndexStart, 7);
                    root++;
                    i += 6;
                }
                else if (strncmp(arr, "sixthrt(", 8) == 0)
                {
                    copy[copyIndexStart] = '!';
                    removeChar(copy, copyIndexStart, 8);
                    root++;
                    i += 7;
                }
                else if (strncmp(arr, "sin(", 4) == 0)
                {
                    copy[copyIndexStart] = ':';
                    removeChar(copy, copyIndexStart, 4);
                    root++;
                    i += 3;
                }
                else if (strncmp(arr, "sinh(", 5) == 0)
                {
                    copy[copyIndexStart] = 34;
                    removeChar(copy, copyIndexStart, 5);
                    root++;
                    i += 4;
                }
                else
                    return NAN;
            }
            else if (copy[i] == 'a')
            {
                if (strncmp(arr, "arcsin(", 7) == 0)
                {
                    copy[copyIndexStart] = '>';
                    removeChar(copy, copyIndexStart, 7);
                    root++;
                }
                else if (strncmp(arr, "arccos(", 7) == 0)
                {
                    copy[copyIndexStart] = '?';
                    removeChar(copy, copyIndexStart, 7);
                    root++;
                }
                else if (strncmp(arr, "arctan(", 7) == 0)
                {
                    copy[copyIndexStart] = '|';
                    removeChar(copy, copyIndexStart, 7);
                    root++;
                }
                else if (strncmp(arr, "arcsinh(", 8) == 0)
                {
                    copy[copyIndexStart] = '{';
                    removeChar(copy, copyIndexStart, 8);
                    root++;
                }
                else if (strncmp(arr, "arccosh(", 8) == 0)
                {
                    copy[copyIndexStart] = '}';
                    removeChar(copy, copyIndexStart, 8);
                    root++;
                }
                else if (strncmp(arr, "arctanh(", 8) == 0)
                {
                    copy[copyIndexStart] = '(';
                    removeChar(copy, copyIndexStart, 8);
                    root++;
                }
                else if (strncmp(arr, "ans", 3) == 0)
                {
                    total = ans;
                    removeChar(copy, copyIndexStart, 3);
                    i -= 5;
                }
                else if (strncmp(arr, "abs(", 4) == 0)
                {
                    copy[copyIndexStart] = 'w';
                    removeChar(copy, copyIndexStart, 4);
                    i -= 4;
                }
                else
                    return NAN;
                i += 7;
            }
            else if (copy[i] == 'c')
            {
                if (strncmp(arr, "cbrt(", 5) == 0)
                {
                    copy[copyIndexStart] = '@';
                    removeChar(copy, copyIndexStart, 5);
                    root++;
                }
                else if (strncmp(arr, "cube(", 5) == 0)
                {
                    copy[copyIndexStart] = '&';
                    removeChar(copy, copyIndexStart, 5);
                    root++;
                }
                else if (strncmp(arr, "cos(", 4) == 0)
                {
                    copy[copyIndexStart] = ';';
                    removeChar(copy, copyIndexStart, 4);
                    root++;
                    i--;
                }
                else if (strncmp(arr, "cosh(", 5) == 0)
                {
                    copy[copyIndexStart] = 39;
                    removeChar(copy, copyIndexStart, 5);
                    root++;
                }
                else if (strncmp(arr, "ceil(", 5) == 0)
                {
                    copy[copyIndexStart] = 'c';
                    removeChar(copy, copyIndexStart, 5);
                    root++;
                }
                else
                    return NAN;
                i += 4;
            }
            else if (copy[i] == 'q')
            {
                if (strncmp(arr, "quartrt(", 8) == 0)
                {
                    copy[copyIndexStart] = '$';
                    removeChar(copy, copyIndexStart, 8);
                    root++;
                }
                else if (strncmp(arr, "quintrt(", 8) == 0)
                {
                    copy[copyIndexStart] = '~';
                    removeChar(copy, copyIndexStart, 8);
                    root++;
                }
                else
                    return NAN;
                i += 7;
            }
            else if (copy[i] == 't')
            {
                if (strncmp(arr, "tan(", 4) == 0)
                {
                    copy[copyIndexStart] = 92;
                    removeChar(copy, copyIndexStart, 4);
                    root++;
                }
                else if (strncmp(arr, "tanh(", 5) == 0)
                {
                    copy[copyIndexStart] = '\f';
                    removeChar(copy, copyIndexStart, 5);
                    root++;
                    i++;
                }
                else
                    return NAN;
                i += 2;
            }
            else if (copy[i] == 'f')
            {
                if (strncmp(arr, "floor(", 6) == 0)
                {
                    copy[copyIndexStart] = 'f';
                    removeChar(copy, copyIndexStart, 6);
                    root++;
                    i += 5;
                }
                else
                    return NAN;
            }
            else if (copy[i] == 'l')
            {
                //ln
                if (strncmp(arr, "ln(", 3) == 0)
                {
                    copy[copyIndexStart] = 'l';
                    removeChar(copy, copyIndexStart, 3);
                    root++;
                    i += 2;
                }
                else if (strncmp(arr, "logone(", 7) == 0)
                {
                    copy[copyIndexStart] = 'v';
                    removeChar(copy, copyIndexStart, 7);
                    root++;
                    i += 6;
                }
                //log base 2
                else if (strncmp(arr, "logtwo(", 7) == 0)
                {
                    copy[copyIndexStart] = 'n';
                    removeChar(copy, copyIndexStart, 7);
                    root++;
                    i += 6;
                }
                //log base 3
                else if (strncmp(arr, "logthree(", 9) == 0)
                {
                    copy[copyIndexStart] = 'o';
                    removeChar(copy, copyIndexStart, 9);
                    root++;
                    i += 8;
                }
                //log base 4
                else if (strncmp(arr, "logfour(", 8) == 0)
                {
                    copy[copyIndexStart] = 'p';
                    removeChar(copy, copyIndexStart, 8);
                    root++;
                    i += 7;
                }
                //log base 5
                else if (strncmp(arr, "logfive(", 8) == 0)
                {
                    copy[copyIndexStart] = 'q';
                    removeChar(copy, copyIndexStart, 8);
                    root++;
                    i += 7;
                }
                //log base 6
                else if (strncmp(arr, "logsix(", 7) == 0)
                {
                    copy[copyIndexStart] = 'r';
                    removeChar(copy, copyIndexStart, 7);
                    root++;
                    i += 6;
                }
                //log base 7
                else if (strncmp(arr, "logseven(", 9) == 0)
                {
                    copy[copyIndexStart] = 's';
                    removeChar(copy, copyIndexStart, 9);
                    root++;
                    i += 8;
                }
                //log base 8
                else if (strncmp(arr, "logeight(", 9) == 0)
                {
                    copy[copyIndexStart] = 't';
                    removeChar(copy, copyIndexStart, 9);
                    root++;
                    i += 8;
                }
                //log base 9
                else if (strncmp(arr, "lognine(", 8) == 0)
                {
                    copy[copyIndexStart] = 'u';
                    removeChar(copy, copyIndexStart, 8);
                    root++;
                    i += 7;
                }
                //log base 10
                else if (strncmp(arr, "log(", 4) == 0)
                {
                    copy[copyIndexStart] = 'k';
                    removeChar(copy, copyIndexStart, 4);
                    root++;
                    i += 3;
                }
                else
                    return NAN;
            }
            else if (copy[i] == 'P')
            {
                if (strncmp(arr, "PI", 2) == 0)
                {
                    copy[i + 1] = ' ';
                    i++;
                }
                else
                    return NAN;
            }
            else if (copy[i] == 'G')
            {
                if (strncmp(arr, "GOLDEN_RT", 9) == 0)
                {
                    removeChar(copy, copyIndexStart, 9);
                    i += 8;
                }
                else
                    return NAN;
            }
            else if (copy[i] == 'A')
            {
                if (strncmp(arr, "APERY_CNS", 9) == 0)
                {
                    removeChar(copy, copyIndexStart, 9);
                    i += 8;
                }
                else
                    return NAN;
            }
            else if (copy[i] == 'S')
            {
                if (strncmp(arr, "SQRT_2", 6) == 0)
                    removeChar(copy, copyIndexStart, 6);

                else if (strncmp(arr, "SQRT_3", 6) == 0)
                {
                    copy[i] = 'M';
                    removeChar(copy, copyIndexStart, 6);
                }
                else
                    return NAN;
                i += 5;
            }
            else if (copy[i] == 'C')
            {
                if (strncmp(arr, "CATALAN_C", 9) == 0)
                {
                    copy[i] = 'K';
                    removeChar(copy, copyIndexStart, 9);
                    i += 8;
                }
            }
            else if (copy[i] == 'n')
            {
                if (strncmp(arr, "nCr", 3) == 0)
                {
                    copy[i] = 'C';
                    removeChar(copy, copyIndexStart, 3);
                }
                else if (strncmp(arr, "nPr", 3) == 0)
                {
                    copy[i] = 'P';
                    removeChar(copy, copyIndexStart, 3);
                }
                else
                    return NAN;
                i += 2;
            }
            else
                return NAN;
        }
    }

    total = convertFloat(copy, total);

    if (total == NAN)
        return NAN;

    times = numberOfOperations(copy);

    x = times;

    if (times == 0)
        times++;

    //If there was a negative sign in front of the first number, it is negative, so multiply it by -1.
    total *= multNeg;
    lastNum = '0';
    numNum = 0;
    multNeg = 1;

    rootOperations = (char*) malloc(root * sizeof(char));
    for (int j = 0; j < times; j++)
    {
        for (int i = location; i < strlen(copy) + 1; i++)
        {
            //If there's a space at copy[i], save an iteration
            if (copy[i] == ' ')
                continue;
            if (whichNum == '1' && !isdigit(copy[i]) && copy[i] != '.' && copy[i] != '!')
            {
                //rootOperations and additional operations
                for (int a = 0; a < strlen(rootOperations); a++)
                {
                    //sqrt
                    if (rootOperations[a] == '0')
                        total = squareRoot(total);
                    else if (rootOperations[a] == '1')
                        last = squareRoot(last);

                    //cbrt
                    else if (rootOperations[a] == '2')
                        total = cbrt(total);
                    else if (rootOperations[a] == '3')
                        last = cbrt(last);

                    //quartic root
                    else if (rootOperations[a] == '4')
                        total = squareRoot(squareRoot(total));
                    else if (rootOperations[a] == '5')
                        last = squareRoot(squareRoot(last));

                    //quintic root
                    else if (rootOperations[a] == '6')
                        total = fifthRoot(total);
                    else if (rootOperations[a] == '7')
                        last = fifthRoot(last);

                    //sixth root
                    else if (rootOperations[a] == ';')
                        total = cbrt(squareRoot(total));
                    else if (rootOperations[a] == ':')
                        last = cbrt(squareRoot(last));

                    //square
                    else if (rootOperations[a] == '8')
                        total *= total;
                    else if (rootOperations[a] == '9')
                        last *= last;

                    //cube
                    else if (rootOperations[a] == '[')
                        total = pow(total, 3);
                    else if (rootOperations[a] == ']')
                        last = pow(last, 3);

                    //sin
                    else if (rootOperations[a] == '{')
                        total = sin(total);
                    else if (rootOperations[a] == '}')
                        last = sin(last);

                    //cos
                    else if (rootOperations[a] == '~')
                        total = cos(total);
                    else if (rootOperations[a] == '`')
                        last = cos(last);

                    //tan
                    else if (rootOperations[a] == '=')
                        total = tan(total);
                    else if (rootOperations[a] == '_')
                        last = tan(last);

                    //arcsin
                    else if (rootOperations[a] == '(')
                        total = asin(total);
                    else if (rootOperations[a] == ')')
                        last = asin(last);

                    //arccos
                    else if (rootOperations[a] == ',')
                        total = acos(total);
                    else if (rootOperations[a] == '.')
                        last = acos(last);

                    //arctan
                    else if (rootOperations[a] == '<')
                        total = atan(total);
                    else if (rootOperations[a] == '>')
                        last = atan(last);

                    //sinh
                    else if (rootOperations[a] == ' ')
                        total = sinh(total);
                    else if (rootOperations[a] == 'a')
                        last = sinh(last);

                    //cosh
                    else if (rootOperations[a] == 'b')
                        total = cosh(total);
                    else if (rootOperations[a] == 'c')
                        last = cosh(last);

                    //tanh
                    else if (rootOperations[a] == 'd')
                        total = tanh(total);
                    else if (rootOperations[a] == 'e')
                        last = tanh(last);

                    //arcsinh
                    else if (rootOperations[a] == '+')
                        total = asinh(total);
                    else if (rootOperations[a] == '-')
                        last = asinh(last);

                    //arccosh
                    else if (rootOperations[a] == '*')
                        total = acosh(total);
                    else if (rootOperations[a] == '/')
                        last = acosh(last);

                    //arctanh
                    else if (rootOperations[a] == '@')
                        total = atanh(total);
                    else if (rootOperations[a] == '#')
                        last = atanh(last);

                    //ceil
                    else if (rootOperations[a] == 'f')
                        total = (int) total + 1;
                    else if (rootOperations[a] == 'g')
                        last = (int) last + 1;

                    //floor
                    else if (rootOperations[a] == 'h')
                        total = (int) total;
                    else if (rootOperations[a] == 'i')
                        last = (int) last;

                    //ln
                    else if (rootOperations[a] == 'j')
                        total = ln(total);
                    else if (rootOperations[a] == 'k')
                        last = ln(last);

                    //log base 10
                    else if (rootOperations[a] == 'l')
                        total = log10(total);
                    else if (rootOperations[a] == 'm')
                        last = log10(last);

                    //log base 2
                    else if (rootOperations[a] == 'n')
                        total = log2(total);
                    else if (rootOperations[a] == 'o')
                        last = log2(last);

                    //log base 3
                    else if (rootOperations[a] == 'p')
                        total = log3(total);
                    else if (rootOperations[a] == 'q')
                        last = log3(last);

                    //log base 4
                    else if (rootOperations[a] == 'r')
                        total = log4(total);
                    else if (rootOperations[a] == 's')
                        last = log4(last);

                    //log base 5
                    else if (rootOperations[a] == 't')
                        total = log5(total);
                    else if (rootOperations[a] == 'u')
                        last = log5(last);

                    //log base 6
                    else if (rootOperations[a] == 'v')
                        total = log6(total);
                    else if (rootOperations[a] == 'w')
                        last = log6(last);

                    //log base 7
                    else if (rootOperations[a] == 'x')
                        total = log7(total);
                    else if (rootOperations[a] == 'y')
                        last = log7(last);

                    //log base 8
                    else if (rootOperations[a] == 'z')
                        total = log8(total);
                    else if (rootOperations[a] == 'A')
                        last = log8(last);

                    //log base 9
                    else if (rootOperations[a] == 'B')
                        total = log9(total);
                    else if (rootOperations[a] == 'C')
                        last = log9(last);

                    //log base 1
                    else if (rootOperations[a] == 'D')
                        total = log1(total);
                    else if (rootOperations[a] == 'E')
                        last = log1(last);

                    //factorial
                    else if (rootOperations[a] == 'F')
                    {
                        if (total < 0)
                            return NAN;
                        total = tgamma(total + 1);
                    }
                    else if (rootOperations[a] == 'G')
                    {
                        if (last < 0)
                            return NAN;
                        last = tgamma(last + 1);
                    }

                    //absolute value
                    else if (rootOperations[a] == 'H')
                        total = fabsl(total);
                    else if (rootOperations[a] == 'I')
                        last = fabsl(last);
                }
                last *= multNeg;
                //operation
                switch (state)
                {
                    case '+':
                        total += last;
                        break;
                    case '-':
                        total -= last;
                        break;
                    case '*':
                        total *= last;
                        break;
                    case '/':
                        total /= last;
                        break;
                    case '^':
                        total = pow(total, last);
                        break;
                    case '%':
                        total = fmod(total, last);
                        break;
                }
                if (state == 'e')
                {
                    if ((int) last != last)
                        return NAN;
                    else
                    {
                        if (last > 9)
                            return -1;
                        else
                            total *= pow(10, last);
                    }
                }
                else if (state == 'C')
                {
                    if ((int) last != last || (int) total != total)
                        return NAN;
                    else
                    {
                        if (total < last);
                        else
                            total = tgamma(total + 1) / (tgamma(last + 1) * tgamma(total - last + 1));
                    }
                }
                else if (state == 'P')
                {
                    if ((int) last != last || (int) total != total)
                        return NAN;
                    else
                    {
                        if (total < last);
                        else
                            total = tgamma(total + 1) / tgamma(total - last + 1);
                    }
                }
                 location = i;
                break;
            }

            if (x == 0)
                whichNum = '1';

            if (isdigit(copy[i]))
                numNum = 1;
            else
                rootOperations = assignrootOperations(rootOperations, numNum, copy, i, state);

            if (copy[i] == 'm' && state != '\0')
                multNeg = -1;

            if (state != '\0')
            {
                //Converts last number to float
                if (isdigit(copy[i]))
                {
                    if (lastCheck != 0.0)
                        return NAN;

                    whichNum = '1';

                    if (lastNum == '1')
                    {
                        last += (copy[i] - '0') / divide;
                        divide *= 10;
                        continue;
                    }

                    last += copy[i] - '0';
                    if (isdigit(copy[i + 1]))
                        last *= 10;
                }
                else if (copy[i] == 'P')
                {
                    if (total != 0.0)
                        last *= M_PI;

                    last = M_PI;
                    lastCheck = last;
                    whichNum = '1';
                }
                else if (copy[i] == 'E')
                {
                    if (total != 0.0)
                        last *= M_E;

                    last = M_E;
                    lastCheck = M_E;
                    whichNum = '1';
                }
                else if (copy[i] == 'G')
                {
                    if (total != 0.0)
                        last *= GOLDEN_RT;

                    last = GOLDEN_RT;
                    lastCheck = last;
                    whichNum = '1';
                }
                else if (copy[i] == 'A')
                {
                    if (total != 0.0)
                        last *= APERY_CONST;

                    last = APERY_CONST;
                    lastCheck = last;
                    whichNum = '1';
                }
                else if (copy[i] == 'S')
                {
                    if (total != 0.0)
                        last *= M_SQRT2;

                    last = M_SQRT2;
                    lastCheck = last;
                    whichNum = '1';
                }
                else if (copy[i] == 'M')
                {
                    if (total != 0.0)
                        last *= M_SQRT_3;

                    last = M_SQRT_3;
                    lastCheck = last;
                    whichNum = '1';
                }
                else if (copy[i] == 'K')
                {
                    if (total != 0.0)
                        last *= G;

                    last = G;
                    lastCheck = last;
                    whichNum = '1';
                }
                else if (copy[i] == '.')
                {
                    if (isdigit(copy[i + 1]))
                    {
                        lastNum = '1';
                        continue;
                    }
                }
            }
            //Determines operation to use
            if (state == '\0' && !isdigit(copy[i]))
            {
                if (validateOperation(copy[i]) == 0)
                {
                    state = copy[i];
                    numNum = 0;
                }
            }
        }
        state = '\0';
        whichNum = '0';
        last = 0.0;
        numNum = 0;
        lastNum = '0';
        divide = 10.0;
        rootOperations[0] = '\0';
    }
    ans = total;
    return total;
}

//Check for "--" or "+-"
char* setUp(char* copy)
{
    for (int i = 0; i < strlen(copy); i++)
    {
        //if copy[i] is a space, save an iteration
        if (copy[i] == ' ' || isdigit(copy[i]))
            continue;
        if (copy[i] == '+')
        {
            if (copy[i + 1] != ' ')
            {
                if (copy[i + 1] == '-')
                {
                    copy[i] = '-';
                    copy[i + 1] = ' ';
                }
                else if (isdigit(copy[i + 1]))
                    copy[i] = ' ';
                else
                    copy[i + 1] = ' ';
            }
        }
        else if (copy[i] == '-')
        {
            if (copy[i + 1] != ' ')
            {
                if (copy[i + 1] == '-')
                {
                    copy[i] = '+';
                    copy[i + 1] = ' ';
                }
                else if (isdigit(copy[i + 1]))
                    copy[i] = 'm';
                else
                    copy[i + 1] = ' ';
            }
        }
    }
    return copy;
}

//Get first number of equation
long double convertFloat(char* input, long double total)
{
    char lastNum = '0';
    int multNeg = 1;
    int numNum = 1;
    float divide = 10.0;
    long double temp = total;

    //Used to covert copy string to a float
    for (int i = 0; i < strlen(input); i++)
    {
        //This code is in charge of switching from adding integer parts to adding decimals
        if (!isdigit(input[i]))
        {
            //If input[i] is a decimal point, start adding decimals
            if (input[i] == '.')
            {
                if (!isdigit(input[i + 1]))
                    break;
                else
                    lastNum = '1';
            }
            //If input[i] is a valid operation, this implies that the first number has terminated
            else if (validateOperation(input[i]) == 0)
                break;
            //For Pi
            else if (input[i] == 'P')
            {
                if (total != 0.0)
                    if (input[i - 1] == ' ')
                        return NAN;
                    else
                        total *= M_PI;
                else
                {
                    total = M_PI;
                    temp = total;
                }
            }
            //For e
            else if (input[i] == 'E')
            {
                if (total != 0.0)
                {
                    if (input[i - 1] == ' ')
                        return NAN;
                    else
                        total *= M_E;
                }
                else
                {
                    total = M_E;
                    temp = total;
                }
            }
            //For Golden Ratio
            else if (input[i] == 'G')
            {
                if (total != 0.0)
                {
                    if (input[i - 1] == ' ')
                        return NAN;
                    else
                        total *= GOLDEN_RT;
                }
                else
                {
                    total = GOLDEN_RT;
                    temp = total;
                    continue;
                }
            }
            //For Apery's Constant
            else if (input[i] == 'A')
            {
                if (total != 0.0)
                    if (input[i - 1] == ' ')
                        return NAN;
                    else
                        total *= APERY_CONST;
                else
                {
                    total = APERY_CONST;
                    temp = total;
                    continue;
                }
            }
            //For Pythagoras' Constant
            else if (input[i] == 'S')
            {
                if (total != 0.0)
                    if (input[i - 1] == ' ')
                        return NAN;
                    else
                        total *= M_SQRT2;
                else
                {
                    total = M_SQRT2;
                    temp = total;
                    continue;
                }
            }
            //For Theodorus' Constant
            else if (input[i] == 'M')
            {
                if (total != 0.0)
                    if (input[i - 1] == ' ')
                        return NAN;
                    else
                        total *= M_SQRT_3;
                else
                {
                    total = M_SQRT_3;
                    temp = total;
                    continue;
                }
            }
            //For Catalan's Constant
            else if (input[i] == 'K')
            {
                if (total != 0.0)
                    if (input[i - 1] == ' ')
                        return NAN;
                    else
                        total *= G;
                else
                {
                    total = G;
                    temp = total;
                    continue;
                }
            }
            //If input[i] is a root, skip
            else if (validateRoot(input[i]) == 0)
                continue;
            else if (input[i] == 'm')
                multNeg = -1;
            else
                return NAN;
        }
        //This part actually converts the number
        else
        {
            if (temp != 0.0)
                return NAN;

            if (lastNum == '0')
            {
                total += input[i] - '0';
                if (isdigit(input[i + 1]))
                    total *= 10;
            }
            else
            {
                total += (input[i] - '0') / pow(divide, numNum);
                numNum++;
            }
        }
    }
    total *= multNeg;
    return total;
}

//Get number of operations
unsigned int numberOfOperations(char* input)
{
    unsigned int times = 0;
    for (int i = 0; i < strlen(input); i++)
    {
        if (input[i] == ' ' || isdigit(input[i]))
            continue;
        //Check how many operations we have to do
        if (validateOperation(input[i]) == 0)
        {
            if (validNext(input[i + 1]) == 0)
                times++;
        }
    }
    return times;
}

//Foot functions
//Square root function
float squareRoot(float number)
{
    if (number < 0)
        return NAN;
    return sqrt(number);
}
//Fifth root function
float fifthRoot(float number)
{
    if (number < 0)
        return pow(fabsf(number), 0.2) * -1;
    return pow(number, 0.2);
}

//Factorial functions
//Combinatorics function
int nCr(long double num1, long double num2)
{
    return tgamma(num1) / (tgamma(num2) * tgamma(num1 - num2 + 1));
}
//Permutations function
int nPr(long double num1, long double num2)
{
    return tgamma(num1) / tgamma(num1 - num2 + 1);
}

//String char checking
//See if input[i] is a valid operation (+, -, etc.)
int validateOperation(char c)
{
    if (c == '+' || c == '*' || c == '-' || c == '/' || c == '^' || c == '%' || c == 'e' || c == 'C' || c == 'P')
        return 0;
    return 1;
}
//Validate char
int validNext(char c)
{
    if (c == ' ' || isdigit(c) || c == 'm')
        return 0;
    return 1;
}
//See if input[i] represents a root/trig/hyperbolic trig/log function (sqrt, cbrt, sin, cos, sinh, cosh, log, ln, etc.)
int validateRoot(char c)
{
    if (c == '@' || c == '#' || c == '$' || c == '~' || c == '<' || c == '&' || c == '!' || c == ';'
        || c == ':' || c == 34 || c == '>' || c == '?' || c == '|' || c == '{' || c == '}' || c == '('
        || c == ')' || c == 'c' || c == 39 || c == 92 || c == '\f' || c == 'f' || c == 'l' || c == 'v'
        || c == 'v' || c == 'n' || c == 'o' || c == 'p' || c == 'q' || c == 'r' || c == 's' || c == 't'
        || c == 'u' || c == 'k' || c == ' ' || c == 'S' || c == 'M' || c == 'w')
        return 0;
    return 1;
}
//Set chars to ' '
char* removeChar(char* input, int index, int c)
{
    for (int i = 0; i < c - 1; i++)
        input[index + 1 + i] = ' ';
    return input;
}
//Append root representation onto a string
char* assignrootOperations(char* rootOperations, int numNum, char* copy, int i, char state)
{
    //sqrt
    if (copy[i] == '#')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(rootOperations, "0");
        }
        else
            if (numNum == 0)
                strcat(rootOperations, "1");
    }
    //cbrt
    else if (copy[i] == '@')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(rootOperations, "2");
        }
        else
            if (numNum == 0)
                strcat(rootOperations, "3");
    }
    //quartic root
    else if (copy[i] == '$')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(rootOperations, "4");
        }
        else
            if (numNum == 0)
                strcat(rootOperations, "5");
    }
    //quintic root
    else if (copy[i] == '~')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(rootOperations, "6");
        }
            else
                if (numNum == 0)
                    strcat(rootOperations, "7");
    }
    //squaring
    else if (copy[i] == '<')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(rootOperations, "8");
        }
        else
            if (numNum == 0)
                strcat(rootOperations, "9");
    }
    //cubing
    else if (copy[i] == '&')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(rootOperations, "[");
        }
        else
            if (numNum == 0)
                strcat(rootOperations, "]");
    }
    //sixth root
    else if (copy[i] == '!')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(rootOperations, ";");
            else
                strcat(rootOperations, "F");
        }
        else
            if (numNum == 0)
                strcat(rootOperations, ":");
            else
                strcat(rootOperations, "G");
    }
    //sin
    else if (copy[i] == ':')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(rootOperations, "{");
        }
        else
            if (numNum == 0)
                strcat(rootOperations, "}");
    }
    //cos
    else if (copy[i] == ';')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(rootOperations, "~");
        }
        else
            if (numNum == 0)
                strcat(rootOperations, "`");
    }
    //tan
    else if (copy[i] == 92)
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(rootOperations, "=");
        }
        else
            if (numNum == 0)
                strcat(rootOperations, "_");
    }
    //arcsin
    else if (copy[i] == '>')
        {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(rootOperations, "(");
        }
        else
            if (numNum == 0)
                strcat(rootOperations, ")");
    }
    //arccos
    else if (copy[i] == '?')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(rootOperations, ",");
        }
        else
            if (numNum == 0)
                strcat(rootOperations, ".");
    }
    //arctan
    else if (copy[i] == '|')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(rootOperations, "<");
        }
        else
            if (numNum == 0)
                strcat(rootOperations, ">");
    }
    //sinh
    else if (copy[i] == 34)
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(rootOperations, " ");
        }
        else
            if (numNum == 0)
                strcat(rootOperations, "a");
    }
    //cosh
    else if (copy[i] == 39)
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(rootOperations, "b");
        }
        else
            if (numNum == 0)
                strcat(rootOperations, "c");
    }
    //tanh
    else if (copy[i] == '\f')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(rootOperations, "d");
        }
        else
            if (numNum == 0)
                strcat(rootOperations, "e");
    }
    //arcsinh
    else if (copy[i] == '{')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(rootOperations, "+");
        }
        else
            if (numNum == 0)
                strcat(rootOperations, "-");
    }
    //arccosh
    else if (copy[i] == '}')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(rootOperations, "*");
        }
        else
            if (numNum == 0)
                strcat(rootOperations, "/");
    }
    //arctanh
    else if (copy[i] == '(')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(rootOperations, "@");
        }
        else
            if (numNum == 0)
                strcat(rootOperations, "#");
    }
    //ceil
    else if (copy[i] == 'c')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(rootOperations, "f");
        }
        else
            if (numNum == 0)
                strcat(rootOperations, "g");
    }
    //floor
    else if (copy[i] == 'f')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(rootOperations, "h");
        }
        else
            if (numNum == 0)
                strcat(rootOperations, "i");
    }
    //ln
    else if (copy[i] == 'l')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(rootOperations, "j");
        }
        else
            if (numNum == 0)
                strcat(rootOperations, "k");
    }
    //log base 10
    else if (copy[i] == 'k')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(rootOperations, "l");
        }
        else
            if (numNum == 0)
                strcat(rootOperations, "m");
    }
    //log base 2
    else if (copy[i] == 'n')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(rootOperations, "n");
        }
        else
            if (numNum == 0)
                strcat(rootOperations, "o");
    }
    //log base 3
    else if (copy[i] == 'o')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(rootOperations, "p");
        }
        else
            if (numNum == 0)
                strcat(rootOperations, "q");
    }
    //log base 4
    else if (copy[i] == 'p')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(rootOperations, "r");
        }
        else
            if (numNum == 0)
                strcat(rootOperations, "s");
    }
    //log base 5
    else if (copy[i] == 'q')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(rootOperations, "t");
        }
        else
            if (numNum == 0)
                strcat(rootOperations, "u");
    }
    //log base 6
    else if (copy[i] == 'r')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(rootOperations, "v");
        }
        else
            if (numNum == 0)
                strcat(rootOperations, "w");
    }
    //log base 7
    else if (copy[i] == 's')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(rootOperations, "x");
        }
        else
            if (numNum == 0)
                strcat(rootOperations, "y");
    }
    //log base 8
    else if (copy[i] == 't')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(rootOperations, "z");
        }
        else
            if (numNum == 0)
                strcat(rootOperations, "A");
    }
    //log base 9
    else if (copy[i] == 'u')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(rootOperations, "B");
        }
        else
            if (numNum == 0)
                strcat(rootOperations, "C");
    }
    //log base 1
    else if (copy[i] == 'v')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(rootOperations, "D");
        }
        else
            if (numNum == 0)
                strcat(rootOperations, "E");
    }
    //abslute value
    else if (copy[i] == 'w')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(rootOperations, "H");
        }
        else
            if (numNum == 0)
                strcat(rootOperations, "I");
    }
    return rootOperations;
}
