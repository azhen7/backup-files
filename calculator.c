#define _GNU_SOURCE //It's there so the comM_PIler would stop complaining that isascii() does not exist.
#define ARRAY_SIZE 8
#define M_PI 3.141592653589793238462643383279502884197169399375105820974944592307816406286208998628034825342117067982148086513282306647 //value of M_PI

#include <stdio.h> //Used for printf()
#include <cs50.h> //Used for get_string()
#include <string.h> //Used for strlen(), strcat, strncat(), strcmp(), strncmp()
#include <math.h> //Used for pow(), sqrt(), cbrt(), fabsf(), log(), log10()
#include <stdlib.h> //Used for malloc(), system()
#include <ctype.h> //Used for isdigit(), isascii()
#include "log.h" //For some additional logarithm functions

//Used to solve equation
double solveEquation(char* input);

//Get some numbers
long double convertFloat(char* input, long double total);
unsigned int numberOfOperations(char* input);

//String char checking
int validNext(char c);
int validateOperation(char c);
int validateRoot(char c);
int letterExceptionCheck(char c);

//Change strings
char* removeChar(char* input, int index, int c);
char* assignRoots(char* Roots, int numNum, char* copy, int i, char state);
char* setUp(char* copy);

//Root functions
float squareRoot(float number);
float fifthRoot(float number);

//Factorial
long double factorial(float number);

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

        printf("%s = %f\n", getEquation, result);
        printf("Note that this result did not take BEDMAS into account.\n\n");
    }
}

double solveEquation(char* input)
{
    static double ans = 0.0;
    unsigned int times = 0;
    unsigned int location = 0;
    short copyIndexStart = 0;
    short multNeg = 1;
    short x = 0;
    short root = 0;
    short numNum = 1;
    float divide = 10.0;
    float lastCheck = 0.0;
    long double last = 0.0;
    long double total = 0.0;
    char state = '\0';
    char whichNum = '0';
    char lastNum = '0';
    char* copy = (char*) malloc(strlen(input) * sizeof(char));
    char* Roots = NULL;

    //copy input to copy
    strcpy(copy, input);

    //Check for negative first number or stuff like subtracting negative numbers and adding negative numbers
    setUp(copy);

    //Used to check for square roots, cube roots, quartic roots, and quintic roots
    for (int i = 0; i < strlen(copy); i++)
    {
        if (!isascii(copy[i]) == 1)
            return NAN;
        if (isalpha(copy[i]))
        {
            char arr[ARRAY_SIZE];
            arr[0] = '\0';
            if (copy[i] == 'm' || copy[i] == 'e' || copy[i] == 'E' || copy[i] == '!')
                continue;

            else if (copy[i] == 's')
            {
                copyIndexStart = i;

                strncat(arr, &copy[copyIndexStart], ARRAY_SIZE);
                if (strncmp(arr, "sqrt", 4) == 0)
                {
                    copy[copyIndexStart] = '#';
                    removeChar(copy, copyIndexStart, 4);
                    root++;
                    i += 3;
                }
                else if (strncmp(arr, "square", 6) == 0)
                {
                    copy[copyIndexStart] = '<';
                    removeChar(copy, copyIndexStart, 6);
                    root++;
                    i += 5;
                }
                else if (strncmp(arr, "sixthrt", 7) == 0)
                {
                    copy[copyIndexStart] = '!';
                    removeChar(copy, copyIndexStart, 7);
                    root++;
                    i += 6;
                }
                else if (strncmp(arr, "sin", 3) == 0)
                {
                    copy[copyIndexStart] = ':';
                    removeChar(copy, copyIndexStart, 3);
                    root++;
                    i += 2;
                }
                else if (strncmp(arr, "sinh", 4) == 0)
                {
                    copy[copyIndexStart] = 34;
                    removeChar(copy, copyIndexStart, 4);
                    root++;
                    i += 3;
                }
                else
                    return NAN;
            }
            else if (copy[i] == 'a')
            {
                copyIndexStart = i;
                strncat(arr, &copy[copyIndexStart], ARRAY_SIZE);
                if (strncmp(arr, "arcsin", 6) == 0)
                {
                    copy[copyIndexStart] = '>';
                    removeChar(copy, copyIndexStart, 6);
                    root++;
                }
                else if (strncmp(arr, "arccos", 6) == 0)
                {
                    copy[copyIndexStart] = '?';
                    removeChar(copy, copyIndexStart, 6);
                    root++;
                }
                else if (strncmp(arr, "arctan", 6) == 0)
                {
                    copy[copyIndexStart] = '|';
                    removeChar(copy, copyIndexStart, 6);
                    root++;
                }
                else if (strncmp(arr, "arcsnh", 6) == 0)
                {
                    copy[copyIndexStart] = '{';
                    removeChar(copy, copyIndexStart, 6);
                    root++;
                }
                else if (strncmp(arr, "arccsh", 6) == 0)
                {
                    copy[copyIndexStart] = '}';
                    removeChar(copy, copyIndexStart, 6);
                    root++;
                }
                else if (strncmp(arr, "arctnh", 6) == 0)
                {
                    copy[copyIndexStart] = '(';
                    removeChar(copy, copyIndexStart, 6);
                    root++;
                }
                else if (strncmp(arr, "ans", 3) == 0)
                {
                    total = ans;
                    i -= 3;
                    removeChar(copy, copyIndexStart, 3);
                }
                else
                    return NAN;
                i += 5;
            }
            else if (copy[i] == 'c')
            {
                copyIndexStart = i;
                strncat(arr, &copy[copyIndexStart], ARRAY_SIZE);
                if (strncmp(arr, "cbrt", 4) == 0)
                {
                    copy[copyIndexStart] = '@';
                    removeChar(copy, copyIndexStart, 4);
                    root++;
                }
                else if (strncmp(arr, "cube", 4) == 0)
                {
                    copy[copyIndexStart] = '&';
                    removeChar(copy, copyIndexStart, 4);
                    root++;
                }
                else if (strncmp(arr, "cosine", 6) == 0)
                {
                    copy[copyIndexStart] = ';';
                    removeChar(copy, copyIndexStart, 6);
                    root++;
                    i += 2;
                }
                else if (strncmp(arr, "cosh", 4) == 0)
                {
                    copy[copyIndexStart] = 39;
                    removeChar(copy, copyIndexStart, 4);
                    root++;
                }
                else if (strncmp(arr, "ceil", 4) == 0)
                {
                    copy[copyIndexStart] = 'c';
                    removeChar(copy, copyIndexStart, 4);
                    root++;
                }
                else
                    return NAN;
                i += 3;
            }
            else if (copy[i] == 'q')
            {
                copyIndexStart = i;
                strncat(arr, &copy[copyIndexStart], ARRAY_SIZE);
                if (strncmp(arr, "quartrt", 7) == 0)
                {
                    copy[copyIndexStart] = '$';
                    removeChar(copy, copyIndexStart, 7);
                    root++;
                }
                else if (strncmp(arr, "quintrt", 7) == 0)
                {
                    copy[copyIndexStart] = '~';
                    removeChar(copy, copyIndexStart, 7);
                    root++;
                }
                else
                    return NAN;
                i += 6;
            }
            else if (copy[i] == 't')
            {
                copyIndexStart = i;
                strncat(arr, &copy[copyIndexStart], ARRAY_SIZE);
                if (strncmp(arr, "tan", 3) == 0)
                {
                    copy[copyIndexStart] = 92;
                    removeChar(copy, copyIndexStart, 3);
                    root++;
                }
                else if (strncmp(arr, "tanh", 4) == 0)
                {
                    copy[copyIndexStart] = '\f';
                    removeChar(copy, copyIndexStart, 4);
                    root++;
                    i++;
                }
                else
                    return NAN;
                i += 2;
            }
            else if (copy[i] == 'f')
            {
                copyIndexStart = i;
                strncat(arr, &copy[copyIndexStart], ARRAY_SIZE);
                if (strncmp(arr, "floor", 5) == 0)
                {
                    copy[copyIndexStart] = 'f';
                    removeChar(copy, copyIndexStart, 5);
                    root++;
                    i += 4;
                }
                else
                    return NAN;
            }
            else if (copy[i] == 'l')
            {
                copyIndexStart = i;
                strncat(arr, &copy[copyIndexStart], ARRAY_SIZE);
                //ln
                if (strncmp(arr, "ln", 2) == 0)
                {
                    copy[copyIndexStart] = 'l';
                    removeChar(copy, copyIndexStart, 6);
                    root++;
                    i++;
                }
                else if (strncmp(arr, "logone", 6) == 0)
                {
                    copy[copyIndexStart] = 'v';
                    removeChar(copy, copyIndexStart, 6);
                    root++;
                    i += 5;
                }
                //log base 2
                else if (strncmp(arr, "logtwo", 6) == 0)
                {
                    copy[copyIndexStart] = 'n';
                    removeChar(copy, copyIndexStart, 6);
                    root++;
                    i += 5;
                }
                //log base 3
                else if (strncmp(arr, "logthr", 6) == 0)
                {
                    copy[copyIndexStart] = 'o';
                    removeChar(copy, copyIndexStart, 6);
                    root++;
                    i += 5;
                }
                //log base 4
                else if (strncmp(arr, "logfour", 7) == 0)
                {
                    copy[copyIndexStart] = 'p';
                    removeChar(copy, copyIndexStart, 7);
                    root++;
                    i += 6;
                }
                //log base 5
                else if (strncmp(arr, "logfive", 7) == 0)
                {
                    copy[copyIndexStart] = 'q';
                    removeChar(copy, copyIndexStart, 7);
                    root++;
                    i += 6;
                }
                //log base 6
                else if (strncmp(arr, "logsix", 6) == 0)
                {
                    copy[copyIndexStart] = 'r';
                    removeChar(copy, copyIndexStart, 6);
                    root++;
                    i += 5;
                }
                //log base 7
                else if (strcmp(arr, "logseven") == 0)
                {
                    copy[copyIndexStart] = 's';
                    removeChar(copy, copyIndexStart, 8);
                    root++;
                    i += 7;
                }
                //log base 8
                else if (strcmp(arr, "logeight") == 0)
                {
                    copy[copyIndexStart] = 't';
                    removeChar(copy, copyIndexStart, 8);
                    root++;
                    i += 7;
                }
                //log base 9
                else if (strncmp(arr, "lognine", 7) == 0)
                {
                    copy[copyIndexStart] = 'u';
                    removeChar(copy, copyIndexStart, 7);
                    root++;
                    i += 6;
                }
                //log base 10
                else if (strncmp(arr, "log", 3) == 0)
                {
                    copy[copyIndexStart] = 'k';
                    removeChar(copy, copyIndexStart, 3);
                    root++;
                    i += 2;
                }
                else
                    return NAN;
            }
            else if (copy[i] == 'P')
            {
                copyIndexStart = i;
                strncat(arr, &copy[copyIndexStart], ARRAY_SIZE);
                if (strncmp(arr, "PI", 2) == 0)
                {
                    copy[i + 1] = ' ';
                    i++;
                }
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

    Roots = (char*) malloc(root * sizeof(char));
    for (int j = 0; j < times; j++)
    {
        for (int i = location; i < strlen(copy) + 1; i++)
        {
            //If there's a space at copy[i], save an iteration
            if (copy[i] == ' ')
                continue;
            if (whichNum == '1' && !isdigit(copy[i]) && copy[i] != '.' && copy[i] != '!')
            {
                //Roots and additional operations
                for (int a = 0; a < strlen(Roots); a++)
                {
                    //sqrt
                    if (Roots[a] == '0')
                        total = squareRoot(total);
                    else if (Roots[a] == '1')
                        last = squareRoot(last);

                    //cbrt
                    else if (Roots[a] == '2')
                        total = cbrt(total);
                    else if (Roots[a] == '3')
                        last = cbrt(last);

                    //quartic root
                    else if (Roots[a] == '4')
                        total = squareRoot(squareRoot(total));
                    else if (Roots[a] == '5')
                        last = squareRoot(squareRoot(last));

                    //quintic root
                    else if (Roots[a] == '6')
                        total = fifthRoot(total);
                    else if (Roots[a] == '7')
                        last = fifthRoot(last);

                    //sixth root
                    else if (Roots[a] == ';')
                        total = cbrt(squareRoot(total));
                    else if (Roots[a] == ':')
                        last = cbrt(squareRoot(last));

                    //square
                    else if (Roots[a] == '8')
                        total *= total;
                    else if (Roots[a] == '9')
                        last *= last;

                    //cube
                    else if (Roots[a] == '[')
                        total = pow(total, 3);
                    else if (Roots[a] == ']')
                        last = pow(last, 3);

                    //sin
                    else if (Roots[a] == '{')
                        total = sin(total);
                    else if (Roots[a] == '}')
                        last = sin(last);

                    //cos
                    else if (Roots[a] == '~')
                        total = cos(total);
                    else if (Roots[a] == '`')
                        last = cos(last);

                    //tan
                    else if (Roots[a] == '=')
                        total = tan(total);
                    else if (Roots[a] == '_')
                        last = tan(last);

                    //arcsin
                    else if (Roots[a] == '(')
                        total = asin(total);
                    else if (Roots[a] == ')')
                        last = asin(last);

                    //arccos
                    else if (Roots[a] == ',')
                        total = acos(total);
                    else if (Roots[a] == '.')
                        last = acos(last);

                    //arctan
                    else if (Roots[a] == '<')
                        total = atan(total);
                    else if (Roots[a] == '>')
                        last = atan(last);

                    //sinh
                    else if (Roots[a] == ' ')
                        total = sinh(total);
                    else if (Roots[a] == 'a')
                        last = sinh(last);

                    //cosh
                    else if (Roots[a] == 'b')
                        total = cosh(total);
                    else if (Roots[a] == 'c')
                        last = cosh(last);

                    //tanh
                    else if (Roots[a] == 'd')
                        total = tanh(total);
                    else if (Roots[a] == 'e')
                        last = tanh(last);

                    //arcsinh
                    else if (Roots[a] == '+')
                        total = asinh(total);
                    else if (Roots[a] == '-')
                        last = asinh(last);

                    //arccosh
                    else if (Roots[a] == '*')
                        total = acosh(total);
                    else if (Roots[a] == '/')
                        last = acosh(last);

                    //arctanh
                    else if (Roots[a] == '@')
                        total = atanh(total);
                    else if (Roots[a] == '#')
                        last = atanh(last);

                    //ceil
                    else if (Roots[a] == 'f')
                        total = (int) total + 1;
                    else if (Roots[a] == 'g')
                        last = (int) last + 1;

                    //floor
                    else if (Roots[a] == 'h')
                        total = (int) total;
                    else if (Roots[a] == 'i')
                        last = (int) last;

                    //ln
                    else if (Roots[a] == 'j')
                        total = ln(total);
                    else if (Roots[a] == 'k')
                        last = ln(last);

                    //log base 10
                    else if (Roots[a] == 'l')
                        total = log10(total);
                    else if (Roots[a] == 'm')
                        last = log10(last);

                    //log base 2
                    else if (Roots[a] == 'n')
                        total = log2(total);
                    else if (Roots[a] == 'o')
                        last = log2(last);

                    //log base 3
                    else if (Roots[a] == 'p')
                        total = log3(total);
                    else if (Roots[a] == 'q')
                        last = log3(last);

                    //log base 4
                    else if (Roots[a] == 'r')
                        total = log4(total);
                    else if (Roots[a] == 's')
                        last = log4(last);

                    //log base 5
                    else if (Roots[a] == 't')
                        total = log5(total);
                    else if (Roots[a] == 'u')
                        last = log5(last);

                    //log base 6
                    else if (Roots[a] == 'v')
                        total = log6(total);
                    else if (Roots[a] == 'w')
                        last = log6(last);

                    //log base 7
                    else if (Roots[a] == 'x')
                        total = log7(total);
                    else if (Roots[a] == 'y')
                        last = log7(last);

                    //log base 8
                    else if (Roots[a] == 'z')
                        total = log8(total);
                    else if (Roots[a] == 'A')
                        last = log8(last);

                    //log base 9
                    else if (Roots[a] == 'B')
                        total = log9(total);
                    else if (Roots[a] == 'C')
                        last = log9(last);

                    //log base 1
                    else if (Roots[a] == 'D')
                        total = log1(total);
                    else if (Roots[a] == 'E')
                        last = log1(last);

                    //factorial
                    else if (Roots[a] == 'F')
                    {
                        if (total < 0)
                            return NAN;
                        total = factorial(total);
                    }
                    else if (Roots[a] == 'G')
                    {
                        if (last < 0)
                            return NAN;
                        last = factorial(last);
                    }
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
                location = i;
                break;
            }

            if (x == 0)
                whichNum = '1';
            if (isdigit(copy[i]))
                numNum = 1;

            if (!isdigit(copy[i]))
                Roots = assignRoots(Roots, numNum, copy, i, state);

            if (copy[i] == 'm' && state != '\0')
                multNeg = -1;

            //Converts last number to float
            if (isdigit(copy[i]) && state != '\0')
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

            //Determines operation to use
            if (state == '\0' && !isdigit(copy[i]))
            {
                if (validateOperation(copy[i]) == 0)
                {
                    state = copy[i];
                    numNum = 0;
                }
            }

            if (copy[i] == 'P' && state != '\0')
            {
                last = M_PI;
                lastCheck = last;
                whichNum = '1';
            }
            else if (copy[i] == 'E' && state != '\0')
            {
                last = M_E;
                lastCheck = M_E;
                whichNum = '1';
            }

            if (copy[i] == '.' && state != '\0')
            {
                if (isdigit(copy[i + 1]))
                {
                    lastNum = '1';
                    continue;
                }
            }
        }
        state = '\0';
        whichNum = '0';
        last = 0.0;
        numNum = 0;
        lastNum = '0';
        divide = 10.0;
        Roots[0] = '\0';
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
        if (copy[i] == ' ')
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

char* assignRoots(char* Roots, int numNum, char* copy, int i, char state)
{
    //sqrt
    if (copy[i] == '#')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(Roots, "0");
        }
        else
            if (numNum == 0)
                strcat(Roots, "1");
    }
    //cbrt
    else if (copy[i] == '@')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(Roots, "2");
        }
        else
            if (numNum == 0)
                strcat(Roots, "3");
    }
    //quartic root
    else if (copy[i] == '$')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(Roots, "4");
        }
        else
            if (numNum == 0)
                strcat(Roots, "5");
    }
    //quintic root
    else if (copy[i] == '~')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(Roots, "6");
        }
            else
                if (numNum == 0)
                    strcat(Roots, "7");
    }
    //squaring
    else if (copy[i] == '<')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(Roots, "8");
        }
        else
            if (numNum == 0)
                strcat(Roots, "9");
    }
    //cubing
    else if (copy[i] == '&')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(Roots, "[");
        }
        else
            if (numNum == 0)
                strcat(Roots, "]");
    }
    //sixth root
    else if (copy[i] == '!')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(Roots, ";");
            else
                strcat(Roots, "F");
        }
        else
            if (numNum == 0)
                strcat(Roots, ":");
            else
                strcat(Roots, "G");
    }
    //sin
    else if (copy[i] == ':')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(Roots, "{");
        }
        else
            if (numNum == 0)
                strcat(Roots, "}");
    }
    //cos
    else if (copy[i] == ';')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(Roots, "~");
        }
        else
            if (numNum == 0)
                strcat(Roots, "`");
    }
    //tan
    else if (copy[i] == 92)
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(Roots, "=");
        }
        else
            if (numNum == 0)
                strcat(Roots, "_");
    }
    //arcsin
    else if (copy[i] == '>')
        {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(Roots, "(");
        }
        else
            if (numNum == 0)
                strcat(Roots, ")");
    }
    //arccos
    else if (copy[i] == '?')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(Roots, ",");
        }
        else
            if (numNum == 0)
                strcat(Roots, ".");
    }
    //arctan
    else if (copy[i] == '|')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(Roots, "<");
        }
        else
            if (numNum == 0)
                strcat(Roots, ">");
    }
    //sinh
    else if (copy[i] == 34)
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(Roots, " ");
        }
        else
            if (numNum == 0)
                strcat(Roots, "a");
    }
    //cosh
    else if (copy[i] == 39)
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(Roots, "b");
        }
        else
            if (numNum == 0)
                strcat(Roots, "c");
    }
    //tanh
    else if (copy[i] == '\f')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(Roots, "d");
        }
        else
            if (numNum == 0)
                strcat(Roots, "e");
    }
    //arcsinh
    else if (copy[i] == '{')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(Roots, "+");
        }
        else
            if (numNum == 0)
                strcat(Roots, "-");
    }
    //arccosh
    else if (copy[i] == '}')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(Roots, "*");
        }
        else
            if (numNum == 0)
                strcat(Roots, "/");
    }
    //arctanh
    else if (copy[i] == '(')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(Roots, "@");
        }
        else
            if (numNum == 0)
                strcat(Roots, "#");
    }
    //ceil
    else if (copy[i] == 'c')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(Roots, "f");
        }
        else
            if (numNum == 0)
                strcat(Roots, "g");
    }
    //floor
    else if (copy[i] == 'f')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(Roots, "h");
        }
        else
            if (numNum == 0)
                strcat(Roots, "i");
    }
    //ln
    else if (copy[i] == 'l')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(Roots, "j");
        }
        else
            if (numNum == 0)
                strcat(Roots, "k");
    }
    //log base 10
    else if (copy[i] == 'k')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(Roots, "l");
        }
        else
            if (numNum == 0)
                strcat(Roots, "m");
    }
    //log base 2
    else if (copy[i] == 'n')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(Roots, "n");
        }
        else
            if (numNum == 0)
                strcat(Roots, "o");
    }
    //log base 3
    else if (copy[i] == 'o')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(Roots, "p");
        }
        else
            if (numNum == 0)
                strcat(Roots, "q");
    }
    //log base 4
    else if (copy[i] == 'p')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(Roots, "r");
        }
        else
            if (numNum == 0)
                strcat(Roots, "s");
    }
    //log base 5
    else if (copy[i] == 'q')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(Roots, "t");
        }
        else
            if (numNum == 0)
                strcat(Roots, "u");
    }
    //log base 6
    else if (copy[i] == 'r')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(Roots, "v");
        }
        else
            if (numNum == 0)
                strcat(Roots, "w");
    }
    //log base 7
    else if (copy[i] == 's')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(Roots, "x");
        }
        else
            if (numNum == 0)
                strcat(Roots, "y");
    }
    //log base 8
    else if (copy[i] == 't')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(Roots, "z");
        }
        else
            if (numNum == 0)
                strcat(Roots, "A");
    }
    //log base 9
    else if (copy[i] == 'u')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(Roots, "B");
        }
        else
            if (numNum == 0)
                strcat(Roots, "C");
    }
    //log base 1
    else if (copy[i] == 'v')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(Roots, "D");
        }
        else
            if (numNum == 0)
                strcat(Roots, "E");
    }
    return Roots;
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
            if (input[i] == '.')
            {
                if (!isdigit(input[i + 1]))
                    break;
                else
                {
                    lastNum = '1';
                    continue;
                }
            }
            else if (input[i] == 'P')
            {
                if (total != 0.0)
                    return NAN;
                else
                {
                    total = M_PI;
                    temp = total;
                }
            }
            else if (input[i] == 'E')
            {
                if (total != 0.0)
                    return NAN;
                else
                {
                    total = M_E;
                    temp = total;
                }
            }
            else if (validateRoot(input[i]) == 0)
                continue;
            else if (letterExceptionCheck(input[i]) == 0)
            {
                if (input[i] == 'm')
                    multNeg = -1;
            }
            else
                break;
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

//Factorial
long double factorial(float number)
{
    long double result = number;
    number--;
    for (int i = number; i >= 1; i--)
    {
        result *= i;
    }
    if (number != (int) number)
        result *= sqrt(M_PI);
    return result;
}

//Roots functions
float squareRoot(float number)
{
    if (number < 0)
        return NAN;
    return sqrt(number);
}

float fifthRoot(float number)
{
    if (number < 0)
        return pow(fabsf(number), 0.2) * -1;
    return pow(number, 0.2);
}

//Functions related to strings
int validNext(char c)
{
    if (c == ' ' || isdigit(c) || c == 'm')
        return 0;
    return 1;
}

int validateOperation(char c)
{
    if (c == '+' || c == '*' || c == '-' || c == '/' || c == '^' || c == '%' || c == 'e' || c == 'C')
        return 0;
    return 1;
}

int validateRoot(char c)
{
    if (c == '@' || c == '#' || c == '$' || c == '~' || c == ' ' || c == '<' || c == '&' || c == '!')
        return 0;
    return 1;
}

int letterExceptionCheck(char c)
{
    if (c == 'm' || c == 'c' || c == 'f' || c == 'l' || c == 'k' || c == 'n'
        || c == 'o' || c == 'p' || c == 'q' || c == 'r' || c == 's' || c == 't'
        || c == 'u' || c == 'v' || c == 'w' || c == 'x' || c == 'y' || c == 'z'
        || c == 'e' || c == '!' || c == 'C')
        return 0;
    return 1;
}

char* removeChar(char* input, int index, int c)
{
    for (int i = 0; i < c - 1; i++)
        input[index + 1 + i] = ' ';
    return input;
}
