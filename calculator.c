#define _GNU_SOURCE //It's there so the compiler would stop complaining that isascii() does not exist.
#include <stdio.h> //Used for printf()
#include <cs50.h> //Used for get_string()
#include <string.h> //Used for strlen(), strncat(), strcmp(), strcat()
#include <math.h> //Used for pow(), sqrt(), cbrt(), fabsf(), log(), log10
#include <stdlib.h> //Used for malloc(), system()
#include <ctype.h> //Used for isdigit(), isalpha(), isascii()
#include "log.h" //For some additional logarithm functions

//Used to solve equation
double solveEquation(char* input);

//String char checking
int validNext(char* input, int i);
int validateOperation(char* input, int i);
int validateRoot(char* input, int i);
int letterExceptionCheck(char* input, int index);

//Change strings
char* removeChar(char* input, int index);

//Root functions
float squareRoot(float number);
float qurt(float number);

int main(void)
{
    char* getEquation;
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
    unsigned int times = 0;
    unsigned int location = 0;
    short copyIndexStart = 0;
    short multNeg = 1;
    short x = 0;
    short root = 0;
    short numNum = 1;
    short convertedState = 0;

    float divide = 10.0;
    double last = 0.0;
    double total = 0.0;

    char state = '\0';
    char whichNum = '0';
    char lastNum = '0';
    char* copy = (char*) malloc(strlen(input) * sizeof(char));
    char* Roots = NULL;

    //copy input to copy
    strcpy(copy, input);

    //Check for negative first number or stuff like subtracting negative numbers and adding negative numbers
    for (int i = 0; i < strlen(copy); i++)
    {
        //if copy[i] is a space, save an iteration
        if (copy[i] == ' ')
            continue;

        if (i != strlen(copy) - 1)
        {
            if (copy[i] == '+')
            {
                if (copy[i + 1] != ' ')
                {
                    if (copy[i + 1] == '-')
                    {
                        copy[i] = '-';
                        copy[i + 1] = ' ';
                    }
                    else if (isdigit(copy[i + 1]));
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
                    {
                        multNeg = -1;
                        copy[i] = 'm';
                    }
                    else
                        copy[i + 1] = ' ';
                }
            }
        }
        else
            break;
    }

    //Used to check for square roots, cube roots, quartic roots, and quintic roots
    for (int i = 0; i < strlen(copy); i++)
    {
        if (!isascii(copy[i]) == 1)
            return NAN;

        if (isalpha(copy[i]))
        {
            char arr[4] = {'\0'};
            if (copy[i] == 's')
            {
                copyIndexStart = i;

                strncat(arr, &copy[copyIndexStart], 4);
                if (strcmp(arr, "sqrt") == 0)
                {
                    copy[copyIndexStart] = '#';
                    removeChar(copy, copyIndexStart);
                    root++;
                }
                else if (strcmp(arr, "sqre") == 0)
                {
                    copy[copyIndexStart] = '<';
                    removeChar(copy, copyIndexStart);
                    root++;
                }
                else if (strcmp(arr, "sirt") == 0)
                {
                    copy[copyIndexStart] = '!';
                    removeChar(copy, copyIndexStart);
                    root++;
                }
                else if (strcmp(arr, "sine") == 0)
                {
                    copy[copyIndexStart] = ':';
                    removeChar(copy, copyIndexStart);
                    root++;
                }
                else if (strcmp(arr, "sinh") == 0)
                {
                    copy[copyIndexStart] = 34;
                    removeChar(copy, copyIndexStart);
                    root++;
                }
                else
                    return NAN;
            }
            else if (copy[i] == 'a')
            {
                copyIndexStart = i;
                strncat(arr, &copy[copyIndexStart], 4);
                if (strcmp(arr, "asin") == 0)
                {
                    copy[copyIndexStart] = '>';
                    removeChar(copy, copyIndexStart);
                    root++;
                }
                else if (strcmp(arr, "acos") == 0)
                {
                    copy[copyIndexStart] = '?';
                    removeChar(copy, copyIndexStart);
                    root++;
                }
                else if (strcmp(arr, "atan") == 0)
                {
                    copy[copyIndexStart] = '|';
                    removeChar(copy, copyIndexStart);
                    root++;
                }
                else if (strcmp(arr, "asnh") == 0)
                {
                    copy[copyIndexStart] = '{';
                    removeChar(copy, copyIndexStart);
                    root++;
                }
                else if (strcmp(arr, "acsh") == 0)
                {
                    copy[copyIndexStart] = '}';
                    removeChar(copy, copyIndexStart);
                    root++;
                }
                else if (strcmp(arr, "atnh") == 0)
                {
                    copy[copyIndexStart] = '(';
                    removeChar(copy, copyIndexStart);
                    root++;
                }
                else
                    return NAN;
            }
            else if (copy[i] == 'c')
            {
                copyIndexStart = i;
                strncat(arr, &copy[copyIndexStart], 4);
                if (strcmp(arr, "cbrt") == 0)
                {
                    copy[copyIndexStart] = '@';
                    removeChar(copy, copyIndexStart);
                    root++;
                }
                else if (strcmp(arr, "cube") == 0)
                {
                    copy[copyIndexStart] = '&';
                    removeChar(copy, copyIndexStart);
                    root++;
                }
                else if (strcmp(arr, "cosn") == 0)
                {
                    copy[copyIndexStart] = ';';
                    removeChar(copy, copyIndexStart);
                    root++;
                }
                else if (strcmp(arr, "cosh") == 0)
                {
                    copy[copyIndexStart] = 39;
                    removeChar(copy, copyIndexStart);
                    root++;
                }
                else if (strcmp(arr, "ceil") == 0)
                {
                    copy[copyIndexStart] = 'c';
                    removeChar(copy, copyIndexStart);
                    root++;
                }
                else
                    return NAN;
            }
            else if (copy[i] == 'q')
            {
                copyIndexStart = i;
                strncat(arr, &copy[copyIndexStart], 4);
                if (strcmp(arr, "qrrt") == 0)
                {
                    copy[copyIndexStart] = '$';
                    removeChar(copy, copyIndexStart);
                    root++;
                }
                else if (strcmp(arr, "qurt") == 0)
                {
                    copy[copyIndexStart] = '~';
                    removeChar(copy, copyIndexStart);
                    root++;
                }
                else
                    return NAN;
            }
            else if (copy[i] == 't')
            {
                copyIndexStart = i;
                strncat(arr, &copy[copyIndexStart], 4);
                if (strcmp(arr, "tang") == 0)
                {
                    copy[copyIndexStart] = 92;
                    removeChar(copy, copyIndexStart);
                    root++;
                }
                else if (strcmp(arr, "tanh") == 0)
                {
                    copy[copyIndexStart] = '\f';
                    removeChar(copy, copyIndexStart);
                    root++;
                }
                else
                    return NAN;
            }
            else if (copy[i] == 'f')
            {
                copyIndexStart = i;
                strncat(arr, &copy[copyIndexStart], 4);
                if (strcmp(arr, "flor") == 0)
                {
                    copy[copyIndexStart] = 'f';
                    removeChar(copy, copyIndexStart);
                    root++;
                }
                else
                    return NAN;
            }
            else if (copy[i] == 'l')
            {
                copyIndexStart = i;
                strncat(arr, &copy[copyIndexStart], 4);
                if (strcmp(arr, "loge") == 0)
                {
                    copy[copyIndexStart] = 'l';
                    removeChar(copy, copyIndexStart);
                    root++;
                }
                else if (strcmp(arr, "logr") == 0)
                {
                    copy[copyIndexStart] = 'k';
                    removeChar(copy, copyIndexStart);
                    root++;
                }
                else if (strcmp(arr, "lgtw") == 0)
                {
                    copy[copyIndexStart] = 'n';
                    removeChar(copy, copyIndexStart);
                    root++;
                }
                else if (strcmp(arr, "lgth") == 0)
                {
                    copy[copyIndexStart] = 'o';
                    removeChar(copy, copyIndexStart);
                    root++;
                }
                else if (strcmp(arr, "lgfr") == 0)
                {
                    copy[copyIndexStart] = 'p';
                    removeChar(copy, copyIndexStart);
                    root++;
                }
                else if (strcmp(arr, "lgfv") == 0)
                {
                    copy[copyIndexStart] = 'q';
                    removeChar(copy, copyIndexStart);
                    root++;
                }
                else
                    return NAN;
            }
            else if (copy[i] == 'm');
            else
                return NAN;
        }
    }

    for (int i = 0; i < strlen(copy); i++)
    {
        if (copy[i] == ' ' || isdigit(copy[i]))
            continue;
        //Check how many operations we have to do
        if (validateOperation(copy, i) == 0)
        {
            if (validNext(copy, i) == 0)
                times++;
        }
    }

    x = times;

    if (times == 0)
        times++;

    //Used to covert copy string to a float
    for (int i = 0; i < strlen(copy); i++)
    {
        //This code is in charge of switching from adding integer parts to adding decimals
        if (!isdigit(copy[i]))
        {
            if (isdigit(copy[i - 1]))
                break;
            if ((int) copy[i] == 46)
            {
                if (!isdigit(copy[i + 1]))
                    break;
                else
                    convertedState = 1;
            }
            else if (validateRoot(copy, i) == 0)
                continue;
            else if (letterExceptionCheck(copy, i) == 0);
            else
                break;
        }
        //This part actually converts the number
        else
        {
            if (convertedState == 0)
            {
                total += copy[i] - '0';
                if (isdigit(copy[i + 1]))
                    total *= 10;
            }
            else
            {
                total += (copy[i] - '0') / pow(divide, numNum);
                numNum++;
            }
        }
    }
    //If there was a negative sign in front of the first number, it is negative, so multiply it by -1.
    total *= multNeg;
    numNum = 0;

    Roots = (char*) malloc(root * sizeof(char));

    for (int j = 0; j < times; j++)
    {
        for (int i = location; i < strlen(copy) + 1; i++)
        {
            //printf("%c\n", copy[i]);
            //If there's a space at copy[i], save an iteration
            if (copy[i] == ' ')
                continue;

            if (whichNum == '1' && !isdigit(copy[i]) && copy[i] != '.')
            {
                for (int a = 0; a < root; a++)
                {
                    //Roots and additional operations
                    if (Roots[a] == '0')
                        total = squareRoot(total);

                    else if (Roots[a] == '1')
                        last = squareRoot(last);

                    else if (Roots[a] == '2')
                        total = cbrt(total);

                    else if (Roots[a] == '3')
                        last = cbrt(last);

                    else if (Roots[a] == '4')
                        total = squareRoot(squareRoot(total));

                    else if (Roots[a] == '5')
                        last = squareRoot(squareRoot(last));

                    else if (Roots[a] == '6')
                        total = qurt(total);

                    else if (Roots[a] == '7')
                        last = qurt(last);

                    else if (Roots[a] == ';')
                        total = cbrt(squareRoot(total));

                    else if (Roots[a] == ':')
                        last = cbrt(squareRoot(last));

                    else if (Roots[a] == '8')
                        total *= total;

                    else if (Roots[a] == '9')
                        last *= last;

                    else if (Roots[a] == '[')
                        total = pow(total, 3);

                    else if (Roots[a] == ']')
                        last = pow(last, 3);

                    else if (Roots[a] == '{')
                        total = sin(total);

                    else if (Roots[a] == '}')
                        last = sin(last);

                    else if (Roots[a] == '~')
                        total = cos(total);

                    else if (Roots[a] == '`')
                        last = cos(last);

                    else if (Roots[a] == '=')
                        total = tan(total);

                    else if (Roots[a] == '_')
                        last = tan(last);

                    else if (Roots[a] == '(')
                        total = asin(total);

                    else if (Roots[a] == ')')
                        last = asin(last);

                    else if (Roots[a] == ',')
                        total = acos(total);

                    else if (Roots[a] == '.')
                        last = acos(last);

                    else if (Roots[a] == '<')
                        total = atan(total);

                    else if (Roots[a] == '>')
                        last = atan(last);

                    else if (Roots[a] == ' ')
                        total = sinh(total);

                    else if (Roots[a] == 'a')
                        last = sinh(last);

                    else if (Roots[a] == 'b')
                        total = cosh(total);

                    else if (Roots[a] == 'c')
                        last = cosh(last);

                    else if (Roots[a] == 'd')
                        total = tanh(total);

                    else if (Roots[a] == 'e')
                        last = tanh(last);

                    else if (Roots[a] == '+')
                        total = asinh(total);

                    else if (Roots[a] == '-')
                        last = asinh(last);

                    else if (Roots[a] == '*')
                        total = acosh(total);

                    else if (Roots[a] == '/')
                        last = acosh(last);

                    else if (Roots[a] == '@')
                        total = atanh(total);

                    else if (Roots[a] == '#')
                        last = atanh(last);

                    else if (Roots[a] == 'f')
                        total = (int) total + 1;

                    else if (Roots[a] == 'g')
                        last = (int) last + 1;

                    else if (Roots[a] == 'h')
                        total = (int) total;

                    else if (Roots[a] == 'i')
                        last = (int) last;

                    else if (Roots[a] == 'j')
                        total = log(total);

                    else if (Roots[a] == 'k')
                        last = log(last);

                    else if (Roots[a] == 'l')
                        total = log10(total);

                    else if (Roots[a] == 'm')
                        last = log10(last);

                    else if (Roots[a] == 'n')
                        total = log2(total);

                    else if (Roots[a] == 'o')
                        last = log2(last);

                    else if (Roots[a] == 'p')
                        total = log3(total);

                    else if (Roots[a] == 'q')
                        last = log3(last);

                    else if (Roots[a] == 'r')
                        total = log4(total);

                    else if (Roots[a] == 's')
                        last = log4(last);

                    else if (Roots[a] == 't')
                        total = log5(total);

                    else if (Roots[a] == 'u')
                        last = log5(last);
                }

                //operation
                if (state != '\0')
                {
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
                }

                location = i;
                break;
            }

            if (x == 0)
                whichNum = '1';

            if (isdigit(copy[i]))
                numNum = 1;

            //Checks for roots
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
            if (copy[i] == '@')
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
            if (copy[i] == '$')
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
            if (copy[i] == '~')
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
            if (copy[i] == '<')
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
            if (copy[i] == '&')
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
            if (copy[i] == '!')
            {
                if (state == '\0')
                {
                    if (numNum == 0)
                        strcat(Roots, ";");
                }
                else
                    if (numNum == 0)
                        strcat(Roots, ":");
            }
            //sin
            if (copy[i] == ':')
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
            if (copy[i] == ';')
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
            if (copy[i] == 92)
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
            if (copy[i] == '>')
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
            if (copy[i] == '?')
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
            if (copy[i] == '|')
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
            if (copy[i] == 34)
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
            if (copy[i] == 39)
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
            if (copy[i] == '\f')
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
            if (copy[i] == '{')
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
            if (copy[i] == '}')
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
            if (copy[i] == '(')
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
            if (copy[i] == 'c')
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
            if (copy[i] == 'f')
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
            if (copy[i] == 'l')
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
            if (copy[i] == 'k')
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
            if (copy[i] == 'n')
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
            if (copy[i] == 'o')
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
            if (copy[i] == 'p')
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
            if (copy[i] == 'q')
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

            //Converts last number to float
            if (isdigit(copy[i]) && state != '\0')
            {
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
                if (validateOperation(copy, i) == 0)
                {
                    state = copy[i];
                    numNum = 0;
                }
            }

            if (copy[i] == '.')
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
    }
    return total;
}

//Roots functions
float squareRoot(float number)
{
    if (number < 0)
        return NAN;
    return sqrt(number);
}

float qurt(float number)
{
    if (number < 0)
        return pow(fabsf(number), 0.2) * -1;
    return pow(number, 0.2);
}


//Functions related to strings
int validNext(char* input, int i)
{
    if (input[i + 1] == ' ' || isdigit(input[i + 1]))
        return 0;
    return 1;
}

int validateOperation(char* input, int i)
{
    if (input[i] == '+' || input[i] == '*' || input[i] == '-' || input[i] == '/' || input[i] == '^' || input[i] == '%')
        return 0;
    return 1;
}

int validateRoot(char* input, int i)
{
    if (input[i] == '@' || input[i] == '#' || input[i] == '$' || input[i] == '~' || input[i] == ' ' || input[i] == '<' || input[i] == '&' || input[i] == '!')
        return 0;
    return 1;
}

int letterExceptionCheck(char* input, int index)
{
    if (input[index] == 'm' || input[index] == 'c' || input[index] == 'f' || input[index] == 'l' || input[index] == 'k' || input[index] == 'n'
        || input[index] == 'o' || input[index] == 'p' || input[index] == 'q' || input[index] == 'r' || input[index] == 's' || input[index] == 't'
        || input[index] == 'u')
        return 0;
    return 1;
}

char* removeChar(char* input, int index)
{
    for (int i = 0; i < 3; i++)
        input[index + 1 + i] = ' ';
    return input;
}