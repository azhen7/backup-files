#include "defs.h"

int main(void)
{
    char* getEquation = NULL;
    double result = 0.0;

    system("clear");
    printf("Enter a bunch of equations below: \n");

    while (1)
    {
        getEquation = get_string("");
        result = solveEquation(getEquation);

        //Erase equation typed by user
        fputs("\033[A\033[2K", stdout);
        rewind(stdout);

        if (strcmp(getEquation, "clear") == 0)
        {
            system("clear");
            printf("Enter a bunch of equations below: \n");
        }
        else
        {
            printf("%s = %f\n", getEquation, result);
            printf("Note that this result did not take BEDMAS into account.\n\n");
        }
    }
}

double solveEquation(char* input)
{
    static double ans = 0;
    unsigned int times = 0, location = 0;
    short copyIndexStart = 0, multNeg = 1, x = 0, root = 0, numNum = 1;
    float divide = 10.0, lastCheck = 0.0;
    double last = 0.0, total = 0.0;
    char state = '\0', whichNum = '0', lastNum = '0';
    char* copy = (char*) malloc(strlen(input) * sizeof(char));
    char* rootOperations = NULL;
    char* arr = strchr(input, ' ');

    if (arr != NULL)
        if (strlen(input) == 0 || strcmp(input, arr) == 0)
            return NAN;
    formatInput(input);
    strcpy(copy, input);

    if (strcmp(copy, "NAN") == 0)
        return NAN;

    //Used to check for square root, cube root, quartic root, quintic root and sixth root
    for (int i = 0; i < strlen(copy); i++)
    {
        if (!isascii(copy[i]))
            return NAN;
        if (validateOperation(copy[i]) == 0)
        {
            state = copy[i];
            continue;
        }
        else if (isalpha(copy[i]))
        {
            arr = (char*) malloc(sizeof(char) * ARRAY_SIZE);
            copyIndexStart = i;
            strncat(arr, &copy[copyIndexStart], ARRAY_SIZE);
            if (copy[i] == 'm' || copy[i] == 'e' || copy[i] == 'E')
                continue;

            else if (copy[i] == 's')
            {
                //Square root
                if (strncmp(arr, "sqrt(", 5) == 0)
                {
                    copy[copyIndexStart] = '#';
                    removeChar(copy, copyIndexStart, 5);
                    root++;
                    i += 4;
                }
                //Squaring a number
                else if (strncmp(arr, "square(", 7) == 0)
                {
                    copy[copyIndexStart] = '<';
                    removeChar(copy, copyIndexStart, 7);
                    root++;
                    i += 6;
                }
                //Sixth root
                else if (strncmp(arr, "sixthrt(", 8) == 0)
                {
                    copy[copyIndexStart] = '!';
                    removeChar(copy, copyIndexStart, 8);
                    root++;
                    i += 7;
                }
                //Seventh root
                else if (strncmp(arr, "septrt(", 7) == 0)
                {
                    copy[copyIndexStart] = 'x';
                    removeChar(copy, copyIndexStart, 7);
                    root++;
                    i += 6;
                }
                //sin and sinh
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
                else if (strncmp(arr, "sinc(", 5) == 0)
                {
                    copy[copyIndexStart] = 'J';
                    removeChar(copy, copyIndexStart, 5);
                    root++;
                    i += 4;
                }
                else if (strncmp(arr, "sec(", 4) == 0)
                {
                    copy[copyIndexStart] = 'L';
                    removeChar(copy, copyIndexStart, 4);
                    root++;
                    i += 3;
                }
                else
                    return NAN;
            }
            else if (copy[i] == 'a')
            {
                //Inverse trig and inverse hyperbolic functions
                if (strncmp(arr, "arcsin(", 7) == 0)
                {
                    copy[copyIndexStart] = '>';
                    removeChar(copy, copyIndexStart, 7);
                    root++;
                    i += 6;
                }
                else if (strncmp(arr, "arccos(", 7) == 0)
                {
                    copy[copyIndexStart] = '?';
                    removeChar(copy, copyIndexStart, 7);
                    root++;
                    i += 6;
                }
                else if (strncmp(arr, "arctan(", 7) == 0)
                {
                    copy[copyIndexStart] = '|';
                    removeChar(copy, copyIndexStart, 7);
                    root++;
                    i += 6;
                }
                else if (strncmp(arr, "arcsinh(", 8) == 0)
                {
                    copy[copyIndexStart] = '{';
                    removeChar(copy, copyIndexStart, 8);
                    root++;
                    i += 7;
                }
                else if (strncmp(arr, "arccosh(", 8) == 0)
                {
                    copy[copyIndexStart] = '}';
                    removeChar(copy, copyIndexStart, 8);
                    root++;
                    i += 7;
                }
                else if (strncmp(arr, "arctanh(", 8) == 0)
                {
                    copy[copyIndexStart] = '(';
                    removeChar(copy, copyIndexStart, 8);
                    root++;
                    i += 7;
                }
                //ans
                else if (strncmp(arr, "ans", 3) == 0)
                {
                    if (state == '\0')
                        total = ans;
                    else
                        last = ans;
                    removeChar(copy, copyIndexStart, 3);
                    i += 2;
                }
                //Absolute value
                else if (strncmp(arr, "abs(", 4) == 0)
                {
                    copy[copyIndexStart] = 'w';
                    removeChar(copy, copyIndexStart, 4);
                    i += 3;
                }
                //Arithmetic mean
                else if (strncmp(arr, "avg(", 4) == 0)
                {
                    copy[copyIndexStart] = 'F';
                    removeChar(copy, copyIndexStart, 4);
                    i += 3;
                }
                else
                    return NAN;
            }
            else if (copy[i] == 'c')
            {
                //Cube root
                if (strncmp(arr, "cbrt(", 5) == 0)
                {
                    copy[copyIndexStart] = '@';
                    removeChar(copy, copyIndexStart, 5);
                    root++;
                    i += 4;
                }
                //Cubing a number
                else if (strncmp(arr, "cube(", 5) == 0)
                {
                    copy[copyIndexStart] = '&';
                    removeChar(copy, copyIndexStart, 5);
                    root++;
                    i += 4;
                }
                //cos
                else if (strncmp(arr, "cos(", 4) == 0)
                {
                    copy[copyIndexStart] = ';';
                    removeChar(copy, copyIndexStart, 4);
                    root++;
                    i += 3;
                }
                //cosh
                else if (strncmp(arr, "cosh(", 5) == 0)
                {
                    copy[copyIndexStart] = 39;
                    removeChar(copy, copyIndexStart, 5);
                    root++;
                    i += 4;
                }
                //ceiling
                else if (strncmp(arr, "ceil(", 5) == 0)
                {
                    copy[copyIndexStart] = 'c';
                    removeChar(copy, copyIndexStart, 5);
                    root++;
                    i += 4;
                }
                //cotangent
                else if (strncmp(arr, "cot(", 4) == 0)
                {
                    copy[copyIndexStart] = 'N';
                    removeChar(copy, copyIndexStart, 4);
                    root++;
                    i += 3;
                }
                //cosecant
                else if (strncmp(arr, "cosec(", 6) == 0)
                {
                    copy[copyIndexStart] = 'O';
                    removeChar(copy, copyIndexStart, 6);
                    root++;
                    i += 5;
                }
                else
                    return NAN;
            }
            //4th root and 5th root
            else if (copy[i] == 'q')
            {
                if (strncmp(arr, "quartrt(", 8) == 0)
                {
                    copy[copyIndexStart] = '$';
                    removeChar(copy, copyIndexStart, 8);
                    root++;
                    i += 7;
                }
                else if (strncmp(arr, "quintrt(", 8) == 0)
                {
                    copy[copyIndexStart] = '~';
                    removeChar(copy, copyIndexStart, 8);
                    root++;
                    i += 7;
                }
                else
                    return NAN;
            }
            //tan and tanh
            else if (copy[i] == 't')
            {
                if (strncmp(arr, "tan(", 4) == 0)
                {
                    copy[copyIndexStart] = 92;
                    removeChar(copy, copyIndexStart, 4);
                    root++;
                    i += 3;
                }
                else if (strncmp(arr, "tanh(", 5) == 0)
                {
                    copy[copyIndexStart] = '\f';
                    removeChar(copy, copyIndexStart, 5);
                    root++;
                    i += 4;
                }
                else
                    return NAN;
            }
            //Floor
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
            //Logarithm functions
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
            //Delian's Constant
            else if (copy[i] == 'D')
            {
                if (strncmp(arr, "DELIAN_C", 8) == 0)
                {
                    removeChar(copy, copyIndexStart, 8);
                    i += 7;
                }
                else
                    return NAN;
            }
            //Pi
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
            //GCD and Golden Ratio
            else if (copy[i] == 'G')
            {
                if (strncmp(arr, "GOLDEN_RT", 9) == 0)
                {
                    removeChar(copy, copyIndexStart, 9);
                    i += 8;
                }
                else if (strncmp(arr, "GCD(", 4) == 0)
                {
                    copy[i] = 'y';
                    removeChar(copy, copyIndexStart, 4);
                    i += 3;
                }
                else if (strncmp(arr, "GELFOND_C", 9) == 0)
                {
                    copy[i] = 'B';
                    removeChar(copy, copyIndexStart, 9);
                    i += 8;
                }
                else
                    return NAN;
            }
            //Apery's Constant
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
            //Square root of 2 and 3
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
            //Catalan's Constant
            else if (copy[i] == 'C')
            {
                if (strncmp(arr, "CATALAN_C", 9) == 0)
                {
                    copy[i] = 'K';
                    removeChar(copy, copyIndexStart, 9);
                    i += 8;
                }
                else
                    return NAN;
            }
            //Hermite's Constant
            else if (copy[i] == 'H')
            {
                if (strncmp(arr, "HERMITE_C", 9) == 0)
                {
                    removeChar(copy, copyIndexStart, 9);
                    i += 8;
                }
                else
                    return NAN;
            }
            //Combinatoris & Permutations
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
            else if (copy[i] == 'L')
            {
                if (strncmp(arr, "LCM(", 4) == 0)
                {
                    copy[i] = 'z';
                    removeChar(copy, copyIndexStart, 4);
                    i += 3;
                }
                else
                    return NAN;
            }
            else if (copy[i] == 'g')
            {
                if (strncmp(arr, "geoMean(", 8) == 0)
                {
                    copy[i] = 'I';
                    removeChar(copy, copyIndexStart, 8);
                    i += 7;
                }
                else
                    return NAN;
            }
            else
                return NAN;
        }
    }
    //Check for negative first number or stuff like subtracting negative numbers and adding negative numbers
    setUp(copy);

    arr = (char*) malloc(sizeof(char) * strlen(copy));
    copyStr(arr, copy);
    strcpy(copy, arr);

    state = '\0';
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
            if (copy[i] == ' ')
                continue;
            if (i == strlen(copy))
                whichNum = '1';
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
                        total = log(total);
                    else if (rootOperations[a] == 'k')
                        last = log(last);

                    //log base 10
                    else if (rootOperations[a] == 'l')
                        total = log_base(total, last);

                    //factorial
                    else if (rootOperations[a] == 'F')
                    {
                        if (total < 0)
                            return NAN;
                        else if (total > 15)
                            return INFINITY;
                        total = tgamma(total + 1);
                    }
                    else if (rootOperations[a] == 'G')
                    {
                        if (last < 0)
                            return NAN;
                        else if (last > 15)
                            return INFINITY;
                        last = tgamma(last + 1);
                    }

                    //absolute value
                    else if (rootOperations[a] == 'H')
                        total = fabsl(total);
                    else if (rootOperations[a] == 'I')
                        last = fabsl(last);

                    //seventh root
                    else if (rootOperations[a] == 'J')
                        total = seventhRoot(total);
                    else if (rootOperations[a] == 'K')
                        last = seventhRoot(last);

                    //GCD
                    else if (rootOperations[a] == 'L')
                    {
                        if ((int) last != last || (int) total != total)
                            return NAN;
                        else
                        {
                            if (last < 0 || total < 0)
                                return NAN;
                            if (total == 0.0)
                                total = last;
                            else if (last == 0.0);
                            else
                                total = calculateGCD(total, last);
                        }
                    }
                    //LCM
                    else if (rootOperations[a] == 'M')
                    {
                        if ((int) last != last || (int) total != total)
                            return NAN;
                        else
                        {
                            if (last < 0 || total < 0)
                                return NAN;
                            if (total == 0 || last == 0)
                                total = 0;
                            else
                                total = fabsl(total * last) / calculateGCD(total, last);
                        }
                    }
                    //Arithmetic mean
                    else if (rootOperations[a] == 'N')
                    {
                        total += last;
                        total /= 2;
                    }
                    //Geometric mean
                    else if (rootOperations[a] == 'O')
                    {
                        total *= last;
                        total = sqrt(total);
                    }

                    //sinc
                    else if (rootOperations[a] == 'P')
                        total = sinc(total);
                    else if (rootOperations[a] == 'Q')
                        last = sinc(last);

                    //sec
                    else if (rootOperations[a] == 'R')
                        total = sec(total);
                    else if (rootOperations[a] == 'S')
                        last = sec(last);

                    //cotan
                    else if (rootOperations[a] == 'T')
                        total = cot(total);
                    else if (rootOperations[a] == 'U')
                        last = cot(last);

                    //cosec
                    else if (rootOperations[a] == 'V')
                        total = cosec(total);
                    else if (rootOperations[a] == 'W')
                        last = cosec(last);
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
                //Exponential notation
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
                //Combinatorics
                else if (state == 'C')
                {
                    if ((int) last != last || (int) total != total)
                        return NAN;
                    else
                    {
                        if (total < last)
                            total = 0;
                        else
                            total = tgamma(total + 1) / (tgamma(last + 1) * tgamma(total - last + 1));
                    }
                }
                //Permutations
                else if (state == 'P')
                {
                    if ((int) last != last || (int) total != total)
                        return NAN;
                    else
                    {
                        if (total < last)
                            total = 0;
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
                assignRootOperations(rootOperations, numNum, copy, i, state);

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
                //Pi
                else if (copy[i] == 'P')
                {
                    if (total != 0.0)
                        last *= M_PI;

                    last = M_PI;
                    lastCheck = last;
                    whichNum = '1';
                }
                //e
                else if (copy[i] == 'E')
                {
                    if (total != 0.0)
                        last *= M_E;

                    last = M_E;
                    lastCheck = M_E;
                    whichNum = '1';
                }
                //Golden Ratio
                else if (copy[i] == 'G')
                {
                    if (total != 0.0)
                        last *= GOLDEN_RT;

                    last = GOLDEN_RT;
                    lastCheck = last;
                    whichNum = '1';
                }
                //Apery's Constant
                else if (copy[i] == 'A')
                {
                    if (total != 0.0)
                        last *= APERY_CONST;

                    last = APERY_CONST;
                    lastCheck = last;
                    whichNum = '1';
                }
                //Square root of 2
                else if (copy[i] == 'S')
                {
                    if (total != 0.0)
                        last *= M_SQRT2;

                    last = M_SQRT2;
                    lastCheck = last;
                    whichNum = '1';
                }
                //Square root of 3
                else if (copy[i] == 'M')
                {
                    if (total != 0.0)
                        last *= M_SQRT_3;

                    last = M_SQRT_3;
                    lastCheck = last;
                    whichNum = '1';
                }
                //Catalan's Constant
                else if (copy[i] == 'K')
                {
                    if (total != 0.0)
                        last *= G;

                    last = G;
                    lastCheck = last;
                    whichNum = '1';
                }
                //Delian's Constant
                else if (copy[i] == 'D')
                {
                    if (total != 0.0)
                        last *= DELIAN_CONST;

                    last = DELIAN_CONST;
                    lastCheck = last;
                    whichNum = '1';
                }
                //Hermite's Constant
                else if (copy[i] == 'H')
                {
                    if (total != 0.0)
                        last *= HERMITE_CONST;

                    last = HERMITE_CONST;
                    lastCheck = last;
                    whichNum = '1';
                }
                //Gelfond's Constant
                else if (copy[i] == 'B')
                {
                    if (total != 0.0)
                        last *= GELFOND_CONST;

                    last = GELFOND_CONST;
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
            if (validateOperation(copy[i]) == 0)
            {
                state = copy[i];
                numNum = 0;
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

//GCD
double calculateGCD(double a, double b)
{
    double temp = 0;
    if (a < b)
    {
        temp = a;
        a = b;
        b = temp;
    }
    while (b != 0)
    {
        temp = b;
        b = fmod(a, b);
        a = temp;
    }
    return a;
}
//Get first number of equation
double convertFloat(char* input, double total)
{
    if (strcmp(input, "NAN") == 0)
        return NAN;
    char lastNum = '0';
    int multNeg = 1;
    int numNum = 1;
    float divide = 10.0;
    double temp = total;

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
                    total *= M_E;
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
                    total *= GOLDEN_RT;
                else
                {
                    total = GOLDEN_RT;
                    temp = total;
                }
            }
            //For Apery's Constant
            else if (input[i] == 'A')
            {
                if (total != 0.0)
                    total *= APERY_CONST;
                else
                {
                    total = APERY_CONST;
                    temp = total;
                }
            }
            //For Pythagoras' Constant
            else if (input[i] == 'S')
            {
                if (total != 0.0)
                    total *= M_SQRT2;
                else
                {
                    total = M_SQRT2;
                    temp = total;
                }
            }
            //For Theodorus' Constant
            else if (input[i] == 'M')
            {
                if (total != 0.0)
                    total *= M_SQRT_3;
                else
                {
                    total = M_SQRT_3;
                    temp = total;
                }
            }
            //For Catalan's Constant
            else if (input[i] == 'K')
            {
                if (total != 0.0)
                    total *= G;
                else
                {
                    total = G;
                    temp = total;
                }
            }
            //For Delian's Constant
            else if (input[i] == 'D')
            {
                if (total != 0.0)
                    total *= DELIAN_CONST;
                else
                {
                    total = DELIAN_CONST;
                    temp = total;
                }
            }
            //For Hermite's Constant
            else if (input[i] == 'H')
            {
                if (total != 0.0)
                    total *= HERMITE_CONST;
                else
                {
                    total = HERMITE_CONST;
                    temp = total;
                }
            }
            //For Gelfond's Constant
            else if (input[i] == 'B')
            {
                if (total != 0.0)
                    total *= GELFOND_CONST;
                else
                {
                    total = GELFOND_CONST;
                    temp = total;
                }
            }
            //If input[i] is a root, skip
            else if (validateRoot(input[i]) == 0 || input[i] == ' ')
                continue;
            else if (input[i] == 'm')
                multNeg = -1;
            else if (input[i] == 'a' || input[i] == 'y');
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
