/***************************************************************************************************************
 * - 5/25/2021: Version 1.02
 *      - Added PI functionality.
 *
 * - 5/26/2021: Version 1.03
 *      - Bug 1 (incorrect value of PI) - PATCHED
 *      - Bug 2 (nCr and nPr doesn't work properly) - PATCHED
 *      - Bug 3 (incorrect value of a + b * c) - PATCHED - BEDMAS is handled differently now
 *          - This lead to Bug (a - b where a < b) - PATCHED
 *      - Bug 4 (incorrect value of a % b + c) - PATCHED
 *      - Bug 5 (incorrect value of a + b % c) - PATCHED
 *      - Bug 6 (fraction addition doesn't work) - PATCHED
 *      - Bug 7 (where adding 5 numbers returns -nan) - PATCHED - Zeroing all elements is now handled manually instead of using memset()
 *      - Bug 8 (cPI has incorrect value, where c is a number (e.g. 2PI)) - PATCHED
 *      - Added the constants: Golden Ratio, Root 2, Root 3, Euler's number.
 *
 * - 5/27/2021: Version 1.04
 *      - Added Silver Ratio, Apery's Constant.
 *      - Bug 9 (Seg fault when input string has no spaces) - PATCHED
 *      - Added sqrt and cbrt
 *          - Bug 10 (sqrt(a) where a < 0 = 0) - PATCHED
 *          - Bug 11 (a + sqrt(b) returns value of sqrt(a) + b) - PATCHED
 *      - Automatic text formatting function was removed.
 *
 * - 5/28/2021: Version 1.05
 *      - sqrt and cbrt has been removed
 *      - Added root() function (root(a, b) returns bth root of a)
 *          - Bug 12 (a root( + b, c returns value of a + root(b, c)) - PATCHED
 *          - Bug 13 (a + root(b, c) = NAN) - PATCHED
 *      - Bug 14 (4 nCr 2 = 2 * the correct value) - PATCHED
 *      - Added log_base function (log_base(a, b) returns log base b of a)
 *      - Added GCD and LCM functions
 *      - Bug 15 (a + root(b, c) = NAN) - PATCHED
 *      - Bug 16 (root(b, c) + a has incorrect value) - PATCHED
 *      - Bug 17 (root(b, c) * a has incorrect value) - PATCHED
 *
 * - 5/29/2021: Version 1.06
 *      - Bug 18 (a * root(b, c) has incorrect value) - PATCHED
 *      - Bug 19 (root(b, c) * a = NULL) - PATCHED
 *      - Bug 20 (Seg fault after entering root(b, c)) - PATCHED
 *      - Bug 21 (sin(9) = NAN) - PATCHED
 *      - New feature: If result returned is an integer, 0 decimal places are printed.
 *
 * - 5/30/2021: Version 1.07
 *      - Added base converter - you can convert numbers in different bases. Type "convert bases" to
 *        use the number base converter
 *      - Bug 22 (tan( + 4 + 4 returns value of tan(4) + 4) - PATCHED - Now, nums[location] is checked for whether
 *        it is before next operation
 *      - Bug 23 (second input when first input starts with "cos(" or "tan(" displays error) - PATCHED
 *      - Bug 24 (-a * b returns value of -a - b) - PATCHED
 *      - Added E function (4E3)
 *      - Update to nCr and nPr: you now cannot do "a nCr b" where b is a decimal
 *
 *  - 5/31/2021: Version 1.08
 *      - Bug 25 (a + sin(b) returns value of sin(b)) - PATCHED
 *      - Update to trig functions - If character right after "(" is not a number, NAN is returned
 *      - Added arcsin, arccos, arctan, arcsinh, arccosh, arctanh
 *      - Added iterative log function
 *      - Re-added sqrt and cbrt for convenience
 *      - Added square and cube functions (which square and cube a number, respectively)
 *      - Added code that checks for double decimal points
 *
 *  - 6/1/2021: Version 1.09
 *      - Bug 26 (square(b) = NAN) - PATCHED
 *      - Bug 27 (log(9 + 2 returns a value, not NAN) - PATCHED
 *      - Added ln and log for convenience
 *      - Changed iterative log from "iterate_log(" to "log*("
 *      - Bug 30 (a / b % c returns infinity) - PATCHED
****************************************************************************************************************/

#include "defs.h"

double solveEquation(char* input);
double convertFloat(char* input, double total, int startIndex, int endIndex);
unsigned int numberOfOperations(char* input);
double getMathConstant(char* input, int index, float mathConstant);
double returnValueOfMathConstant(char* input, int i);

int main(void)
{
    char* getEquation = NULL;
    double result = 0.0;
    int base_input;
    int base_convert;
    char* convertedValue;

    system("clear");
    printf("Enter a bunch of equations below: \n");

    while (1)
    {
        getEquation = get_string("");

        if (strcmp(getEquation, "convert bases") == 0)
        {
            do
            {
                base_input = get_int("Enter base of input: ");
            }
            while (base_input > 36 || base_input < 2);

            do
            {
                base_convert = get_int("Enter base to convert input to: ");
            }
            while (base_convert > 36 || base_input < 2);

            getEquation = get_string("Enter input: ");

            if (validateInput(getEquation, base_input))
                printf("Invalid input.\n\n");
            else
            {
                convertedValue = convert(getEquation, base_input, base_convert);

                if (convertedValue != NULL)
                    printf("Your input in base %i is: %s\n\n", base_convert, convertedValue);
                else
                    printf("malloc(): memory allocation failed.\n Operation discontinued.");
            }
        }
        else
        {
            result = solveEquation(getEquation);

            //Erase equation typed by user
            fputs("\033[A\033[2K", stdout);
            rewind(stdout);

            if (fabs(round(result) - result) < 0.000000001)
                printf("%s = %.0f\n", getEquation, result);
            else
                printf("%s = %f\n", getEquation, result);

            putchar('\n');
        }
    }
}

double solveEquation(char* input)
{
    unsigned int times = 0, posIndex = 0;
    double total = 0.0;
    char* equation = (char*) malloc(strlen(input) * sizeof(char));
    char* arr = (char*) malloc(ARRAY_SIZE);
    char* functions = (char*) malloc(strlen(input));
    int* functionPositions = (int*) malloc(strlen(input));
    unsigned int numberOfFunctions = 0;

    if (strlen(input) == 0)
        return NAN;

    for (int i = 0; i < strlen(input); i++)
    {
        if (input[i] != ' ')
            break;
        if (i == strlen(input) - 1)
            return NAN;
    }

    strcpy(equation, input);

    if (strcmp(equation, "NAN") == 0)
        return NAN;

    for (int i = 0; i < strlen(equation); i++)
    {
        if (!isascii(equation[i]))
            return NAN;
        else if (isalpha(equation[i]))
        {
            strncpy(arr, &input[i], ARRAY_SIZE);
            if (equation[i] == 'P' || equation[i] == 'p')
            {
                if (strncmp(arr, "PI", 2) == 0 || strncmp(arr, "pi", 2) == 0)
                {
                    equation[i] = '!';
                    removeChar(equation, i, 1);
                    i++;
                }
                else
                    return NAN;
            }
            else if (equation[i] == 'A')
            {
                if (strncmp(arr, "APERY_CNST", 10) == 0)
                {
                    removeChar(equation, i, 9);
                    i += 9;
                }
                else
                    return NAN;
            }
            else if (equation[i] == 'a')
            {
                if (strncmp(arr, "arcsin(", 7) == 0)
                {
                    if (!isdigit(equation[i + 7]))
                        return NAN;
                    removeChar(equation, i - 1, 7);
                    functionPositions[numberOfFunctions] = i;
                    numberOfFunctions++;
                    i += 7;
                    strcat(functions, "d");
                }
                else if (strncmp(arr, "arccos(", 7) == 0)
                {
                    if (!isdigit(equation[i + 7]))
                        return NAN;
                    removeChar(equation, i - 1, 7);
                    functionPositions[numberOfFunctions] = i;
                    numberOfFunctions++;
                    i += 7;
                    strcat(functions, "e");
                }
                else if (strncmp(arr, "arctan(", 7) == 0)
                {
                    if (!isdigit(equation[i + 7]))
                        return NAN;
                    removeChar(equation, i - 1, 7);
                    functionPositions[numberOfFunctions] = i;
                    numberOfFunctions++;
                    i += 7;
                    strcat(functions, "f");
                }
                else if (strncmp(arr, "arcsinh(", 8) == 0)
                {
                    if (!isdigit(equation[i + 8]))
                        return NAN;
                    removeChar(equation, i - 1, 8);
                    functionPositions[numberOfFunctions] = i;
                    numberOfFunctions++;
                    i += 8;
                    strcat(functions, "g");
                }
                else if (strncmp(arr, "arccosh(", 8) == 0)
                {
                    if (!isdigit(equation[i + 8]))
                        return NAN;
                    removeChar(equation, i - 1, 8);
                    functionPositions[numberOfFunctions] = i;
                    numberOfFunctions++;
                    i += 8;
                    strcat(functions, "h");
                }
                else if (strncmp(arr, "arctanh(", 8) == 0)
                {
                    if (!isdigit(equation[i + 8]))
                        return NAN;
                    removeChar(equation, i - 1, 8);
                    functionPositions[numberOfFunctions] = i;
                    numberOfFunctions++;
                    i += 8;
                    strcat(functions, "i");
                }
                else
                    return NAN;
            }
            else if (equation[i] == 'G')
            {
                if (strncmp(arr, "GOLDEN_RT", 9) == 0)
                {
                    removeChar(equation, i, 8);
                    i += 8;
                }
                else if (strncmp(arr, "GCD(", 4) == 0)
                {
                    removeChar(equation, i - 1, 4);
                    functionPositions[numberOfFunctions] = i;
                    numberOfFunctions++;
                    i += 4;
                    strcat(functions, "2");
                }
                else
                    return NAN;
            }
            else if (equation[i] == 'S')
            {
                if (strncmp(arr, "SQRT_2", 6) == 0)
                {
                    equation[i] = 'T';
                    removeChar(equation, i, 5);
                    i += 5;
                }
                else if (strncmp(arr, "SQRT_3", 6) == 0)
                {
                    equation[i] = 'R';
                    removeChar(equation, i, 5);
                    i += 5;
                }
                else if (strncmp(arr, "SILVER_RT", 9) == 0)
                {
                    equation[i] = 'Y';
                    removeChar(equation, i, 8);
                    i += 8;
                }
                else
                    return NAN;
            }
            else if (equation[i] == 'r')
            {
                if (strncmp(arr, "root(", 5) == 0)
                {
                    if (!isdigit(equation[i + 5]))
                        return NAN;
                    removeChar(equation, i - 1, 5);
                    functionPositions[numberOfFunctions] = i;
                    numberOfFunctions++;
                    i += 5;
                    strcat(functions, "0");
                }
                else
                    return NAN;
            }
            else if (equation[i] == 's')
            {
                if (strncmp(arr, "sin(", 4) == 0)
                {
                    if (!isdigit(equation[i + 4]))
                        return NAN;
                    removeChar(equation, i - 1, 4);
                    functionPositions[numberOfFunctions] = i;
                    numberOfFunctions++;
                    i += 4;
                    strcat(functions, "4");
                }
                else if (strncmp(arr, "sec(", 4) == 0)
                {
                    if (!isdigit(equation[i + 4]))
                        return NAN;
                    removeChar(equation, i - 1, 4);
                    functionPositions[numberOfFunctions] = i;
                    numberOfFunctions++;
                    i += 4;
                    strcat(functions, "8");
                }
                else if (strncmp(arr, "sinh(", 5) == 0)
                {
                    if (!isdigit(equation[i + 5]))
                        return NAN;
                    removeChar(equation, i - 1, 5);
                    functionPositions[numberOfFunctions] = i;
                    numberOfFunctions++;
                    i += 5;
                    strcat(functions, "a");
                }
                else if (strncmp(arr, "sinc(", 5) == 0)
                {
                    if (!isdigit(equation[i + 5]))
                        return NAN;
                    removeChar(equation, i - 1, 5);
                    functionPositions[numberOfFunctions] = i;
                    numberOfFunctions++;
                    i += 5;
                    strcat(functions, "j");
                }
                else if (strncmp(arr, "sqrt(", 5) == 0)
                {
                    if (!isdigit(equation[i + 5]))
                        return NAN;
                    removeChar(equation, i - 1, 5);
                    functionPositions[numberOfFunctions] = i;
                    numberOfFunctions++;
                    i += 5;
                    strcat(functions, "k");
                }
                else if (strncmp(arr, "square(", 7) == 0)
                {
                    if (!isdigit(equation[i + 7]))
                        return NAN;
                    removeChar(equation, i - 1, 7);
                    functionPositions[numberOfFunctions] = i;
                    numberOfFunctions++;
                    i += 7;
                    strcat(functions, "m");
                }
                else
                    return NAN;
            }
            else if (equation[i] == 'l')
            {
                if (strncmp(arr, "log(", 4) == 0)
                {
                    if (!isdigit(equation[i + 4]))
                        return NAN;
                    removeChar(equation, i - 1, 4);
                    functionPositions[numberOfFunctions] = i;
                    numberOfFunctions++;
                    i += 4;
                    strcat(functions, "1");
                }
                else if (strncmp(arr, "log*(", 5) == 0)
                {
                    if (!isdigit(equation[i + 5]))
                        return NAN;
                    removeChar(equation, i - 1, 5);
                    functionPositions[numberOfFunctions] = i;
                    numberOfFunctions++;
                    i += 5;
                    strcat(functions, "A");
                }
                else if (strncmp(arr, "ln(", 3) == 0)
                {
                    if (!isdigit(equation[i + 3]))
                        return NAN;
                    removeChar(equation, i - 1, 3);
                    functionPositions[numberOfFunctions] = i;
                    numberOfFunctions++;
                    i += 3;
                    strcat(functions, "o");
                }
                else if (strncmp(arr, "log10(", 6) == 0)
                {
                    if (!isdigit(equation[i + 6]))
                        return NAN;
                    removeChar(equation, i - 1, 6);
                    functionPositions[numberOfFunctions] = i;
                    numberOfFunctions++;
                    i += 6;
                    strcat(functions, "p");
                }
                else
                    return NAN;
            }
            else if (equation[i] == 'L')
            {
                if (strncmp(arr, "LCM(", 4) == 0)
                {
                    removeChar(equation, i - 1, 4);
                    functionPositions[numberOfFunctions] = i;
                    numberOfFunctions++;
                    i += 4;
                    strcat(functions, "3");
                }
                else
                    return NAN;
            }
            else if (equation[i] == 'n')
            {
                if (strncmp(arr, "nPr", 3) == 0)
                {
                    equation[i] = 'P';
                    removeChar(equation, i, 2);
                    i += 2;
                }
                else if (strncmp(arr, "nCr", 3) == 0)
                {
                    equation[i] = 'C';
                    removeChar(equation, i, 2);
                    i += 2;
                }
                else
                    return NAN;
            }
            else if (equation[i] == 'c')
            {
                if (strncmp(arr, "cos(", 4) == 0)
                {
                    if (!isdigit(equation[i + 4]))
                        return NAN;
                    removeChar(equation, i - 1, 4);
                    functionPositions[numberOfFunctions] = i;
                    numberOfFunctions++;
                    i += 4;
                    strcat(functions, "5");
                }
                else if (strncmp(arr, "cosec(", 6) == 0)
                {
                    if (!isdigit(equation[i + 6]))
                        return NAN;
                    removeChar(equation, i - 1,  6);
                    functionPositions[numberOfFunctions] = i;
                    numberOfFunctions++;
                    i += 6;
                    strcat(functions, "7");
                }
                else if (strncmp(arr, "cot(", 4) == 0)
                {
                    if (!isdigit(equation[i + 4]))
                        return NAN;
                    removeChar(equation, i - 1, 4);
                    functionPositions[numberOfFunctions] = i;
                    numberOfFunctions++;
                    i += 4;
                    strcat(functions, "9");
                }
                else if (strncmp(arr, "cosh(", 5) == 0)
                {
                    if (!isdigit(equation[i + 5]))
                        return NAN;
                    removeChar(equation, i - 1, 5);
                    functionPositions[numberOfFunctions] = i;
                    numberOfFunctions++;
                    i += 5;
                    strcat(functions, "b");
                }
                else if (strncmp(arr, "cbrt(", 5) == 0)
                {
                    if (!isdigit(equation[i + 5]))
                        return NAN;
                    removeChar(equation, i - 1, 5);
                    functionPositions[numberOfFunctions] = i;
                    numberOfFunctions++;
                    i += 5;
                    strcat(functions, "l");
                }
                else if (strncmp(arr, "cube(", 5) == 0)
                {
                    if (!isdigit(equation[i + 5]))
                        return NAN;
                    removeChar(equation, i - 1, 5);
                    functionPositions[numberOfFunctions] = i;
                    numberOfFunctions++;
                    i += 5;
                    strcat(functions, "n");
                }
                else
                    return NAN;
            }
            else if (equation[i] == 't')
            {
                if (strncmp(arr, "tan(", 4) == 0)
                {
                    if (!isdigit(equation[i + 4]))
                        return NAN;
                    removeChar(equation, i - 1, 4);
                    functionPositions[numberOfFunctions] = 1;
                    numberOfFunctions++;
                    i += 4;
                    strcat(functions, "6");
                }
                else if (strncmp(arr, "tanh(", 5) == 0)
                {
                    if (!isdigit(equation[i + 5]))
                        return NAN;
                    removeChar(equation, i - 1, 5);
                    functionPositions[numberOfFunctions] = i;
                    numberOfFunctions++;
                    i += 5;
                    strcat(functions, "c");
                }
                else
                    return NAN;
            }
            else if (equation[i] == 'E' || equation[i] == 'e' || equation[i] == 'x');
            else
                return NAN;
        }
    }

    setUp(equation);

    times = numberOfOperations(equation);

    char* operations = (char*) malloc(times);
    int operationPositions[times];
    int numberOfOperationsLeadingUpToFunction[times];
    unsigned short operationPositionIndex = 0, numberOfSeperators = 0;
    int positions[times + 1];
    memset(positions, -1, times + 1);

    for (int i = 0; i < times; i++)
        numberOfOperationsLeadingUpToFunction[i] = 0;

    for (int i = 0; i < strlen(equation); i++)
    {
        if (validateOperation(equation[i]) == 0)
        {
            if (equation[i] == '-' && isdigit(equation[i + 1]) && !isdigit(equation[i - 1]))
                continue;
            strncat(operations, &equation[i], 1);
            operationPositions[operationPositionIndex] = i;
            operationPositionIndex++;
            if (equation[i] != ',')
                numberOfOperationsLeadingUpToFunction[strlen(functions)]++;
            else
            {
                numberOfSeperators++;
                if (strlen(functions) < numberOfSeperators)
                    return NAN;
            }
        }
    }

    unsigned int seperatorPositions[numberOfSeperators];
    numberOfSeperators = 0;
    for (int i = 0; i < strlen(equation); i++)
    {
        if (isdigit(equation[i]))
        {
            if (i > 0)
            {
                if (!isdigit(equation[i - 1]) && equation[i - 1] != 'm' && equation[i - 1] != '.')
                {
                    positions[posIndex] = i;
                    posIndex++;
                }
            }
            else
            {
                if (equation[i + 1] != '!')
                {
                    positions[posIndex] = i;
                    posIndex++;
                }
            }
        }
        else
        {
            if (equation[i] == '-' && isdigit(equation[i + 1]) && !isdigit(equation[i - 1]))
            {
                equation[i] = 'm';
                positions[posIndex] = i;
                posIndex++;
                times--;
            }
            else if (validateConstantChar(equation[i]))
            {
                positions[posIndex] = i;
                posIndex++;
            }
        }
    }
    double nums[times + 1];
    for (int i = 0; i < times + 1; i++)
        nums[i] = 0;

    //Get all the numbers
    for (int i = 0; i < times + 1; i++)
    {
        nums[i] = convertFloat(equation, nums[i], positions[i], strlen(equation));
        //Check for maximum / minimum / NAN
        if (nums[0] == NAN)
            return NAN;
        else if (nums[0]> UINT_MAX)
            return INFINITY;
        else if (nums[0] < LLONG_MIN)
            return -INFINITY;

        if (operations[i] == ',')
        {
            seperatorPositions[numberOfSeperators] = i;
            numberOfSeperators++;
        }
    }

    unsigned int location = 0;
    for (int i = 0; i < numberOfFunctions; i++)
    {
        for (int j = 0; j < times + 1; j++)
        {
            if (functionPositions[i] < positions[j])
            {
                if (functionPositions[i] >= operationPositions[j - 1] && numberOfOperationsLeadingUpToFunction[i] >= 0)
                {
                    if (operationPositionIndex > 1)
                    {
                        if (positions[j] <= operationPositions[j] && operations[j] == ',')
                        {
                            location = j;
                            break;
                        }
                        else
                            return NAN;
                    }
                    else
                    {
                        location = j;
                        break;
                    }
                }
                else if (operations[j] == ',')
                    break;
                else
                    return NAN;
            }
        }
        //nth root
        if (functions[i] == '0')
        {
            nums[location + 1] = pow(nums[location], 1 / nums[location + 1]);
            if (seperatorPositions[i] == 0)
                nums[location] = 0;
            else
            {
                if (operations[seperatorPositions[i] - 1] == '*' || operations[seperatorPositions[i] - 1] == '/')
                    nums[location] = 1;
                else
                    nums[location] = 0;
            }
        }
        //log
        else if (functions[i] == '1')
        {
            nums[location + 1] = log_base(nums[location], nums[location + 1]);
            if (seperatorPositions[i] == 0)
                nums[location] = 0;
            else
            {
                if (operations[seperatorPositions[i] - 1] == '*' || operations[seperatorPositions[i] - 1] == '/')
                    nums[location] = 1;
                else
                    nums[location] = 0;
            }
        }
        //GCD
        else if (functions[i] == '2')
        {
            if (nums[location] != (int) nums[location] || nums[location + 1] != (int) nums[location + 1])
                return NAN;
            nums[location + 1] = calculateGCD(nums[location], nums[location + 1]);
            if (seperatorPositions[i] == 0)
                nums[location] = 0;
            else
            {
                if (operations[seperatorPositions[i] - 1] == '*' || operations[seperatorPositions[i] - 1] == '/')
                    nums[location] = 1;
                else
                    nums[location] = 0;
            }
        }
        //LCM
        else if (functions[i] == '3')
        {
            if (nums[location] != (int) nums[location] || nums[location + 1] != (int) nums[location + 1])
                return NAN;
            nums[location + 1] = fabs(nums[location] * nums[location + 1]) / calculateGCD(nums[location], nums[location + 1]);
            if (seperatorPositions[i] == 0)
                nums[location] = 0;
            else
            {
                if (operations[seperatorPositions[i] - 1] == '*' || operations[seperatorPositions[i] - 1] == '/')
                    nums[location] = 1;
                else
                    nums[location] = 0;
            }
        }
        //sin
        else if (functions[i] == '4')
            nums[location] = sin(nums[location]);
        //cos
        else if (functions[i] == '5')
            nums[location] = cos(nums[location]);
        //tan
        else if (functions[i] == '6')
            nums[location] = tan(nums[location]);
        //cosecant
        else if (functions[i] == '7')
            nums[location] = cosec(nums[location]);
        //secant
        else if (functions[i] == '8')
            nums[location] = sec(nums[location]);
        //cotangent
        else if (functions[i] == '9')
            nums[location] = cot(nums[location]);
        //sinh
        else if (functions[i] == 'a')
            nums[location] = sinh(nums[location]);
        //cosh
        else if (functions[i] == 'b')
            nums[location] = cosh(nums[location]);
        //tanh
        else if (functions[i] == 'c')
            nums[location] = tanh(nums[location]);
        //arcsin
        else if (functions[i] == 'd')
            nums[location] = asin(nums[location]);
        //arccos
        else if (functions[i] == 'e')
            nums[location] = acos(nums[location]);
        //arctan
        else if (functions[i] == 'f')
            nums[location] = atan(nums[location]);
        //arcsinh
        else if (functions[i] == 'g')
            nums[location] = asinh(nums[location]);
        //arccosh
        else if (functions[i] == 'h')
            nums[location] = acosh(nums[location]);
        //arctanh
        else if (functions[i] == 'i')
            nums[location] = atanh(nums[location]);
        //sinc
        else if (functions[i] == 'j')
            nums[location] = sinc(nums[location]);
        //sqrt
        else if (functions[i] == 'k')
            nums[location] = sqrt(nums[location]);
        //cbrt
        else if (functions[i] == 'l')
            nums[location] = cbrt(nums[location]);
        //square
        else if (functions[i] == 'm')
            nums[location] *= nums[location];
        //cube
        else if (functions[i] == 'n')
            nums[location] *= nums[location] * nums[location];
        //natural log
        else if (functions[i] == 'o')
            nums[location] = log(nums[location]);
        //log base 10
        else if (functions[i] == 'p')
            nums[location] = log10(nums[location]);
        //iterative log
        else if (functions[i] == 'A')
        {
            nums[location + 1] = iterative_log(nums[location], nums[location + 1]);
            if (seperatorPositions[i] == 0)
                nums[location] = 0;
            else
            {
                if (operations[seperatorPositions[i] - 1] == '*' || operations[seperatorPositions[i] - 1] == '/')
                    nums[location] = 1;
                else
                    nums[location] = 0;
            }
        }
    }

    //E
    for (int i = 0; i < times; i++)
    {
        if (operations[i] == 'e')
        {
            if ((int) nums[i + 1] != nums[i + 1])
                return NAN;

            nums[i + 1] = (int) (nums[i] * pow(10, nums[i + 1]));
            nums[i] = 0 + 1 * (operations[i + 1] == '*' || operations[i + 1] == '/');
            if (operations[i - 1] != 'C' && operations[i - 1] != 'P')
                operations[i] = operations[i - 1];
        }
    }
    //Modulo operation
    for (int i = 0; i < times; i++)
    {
        if (operations[i] == '%')
        {
            nums[i + 1] = fmod(nums[i], nums[i + 1]);
            nums[i] = 0 + 1 * (operations[i - 1] == '*' || operations[i - 1] == '/');
            if (operations[i - 1] != 'C' && operations[i - 1] != 'P')
                operations[i] = operations[i - 1];
        }
        else if (operations[i] == ',')
        {
            if (operations[i - 1] != 'C' && operations[i - 1] != 'P')
                operations[i] = operations[i - 1];
        }
    }
    //Multiplications, Division, nCr, nPr
    for (int i = 0; i < times; i++)
    {
        if (operations[i] == '*')
        {
            nums[i + 1] *= nums[i];
            nums[i] = 0;
            if (operations[i - 1] != 'C' && operations[i - 1] != 'P')
                operations[i] = operations[i - 1];
        }
        else if (operations[i] == '/')
        {
            nums[i] /= nums[i + 1];
            nums[i + 1] = nums[i];
            nums[i] = 0;
            if (operations[i - 1] != 'C' && operations[i - 1] != 'P')
                operations[i] = operations[i - 1];
        }
        else if (operations[i] == 'C')
        {
            if ((int) nums[i] != nums[i] || (int) nums[i + 1] != nums[i + 1])
                return NAN;
            nums[i + 1] = tgamma(nums[i] + 1) / (tgamma(nums[i + 1] + 1) * tgamma(nums[i] - nums[i + 1] + 1));
            total += nums[i + 1];
            nums[i] = 0;
        }
        else if (operations[i] == 'P')
        {
            if ((int) nums[i] != nums[i] || (int) nums[i + 1] != nums[i + 1])
                return NAN;
            nums[i + 1] = tgamma(nums[i] + 1) / tgamma(nums[i] - nums[i + 1] + 1);
            total += nums[i + 1];
            nums[i] = 0;
        }

    }
    //Assign total the first non-zero number
    for (int i = 0; i < times + 1; i++)
    {
        if (nums[i] != 0)
        {
            total = nums[i];
            break;
        }
    }
    //Addition, Subtraction
    for (int i = 0; i < operationPositionIndex + 1; i++)
    {
        if (operations[i] == '+')
            total += nums[i + 1];
        else if (operations[i] == '-')
            total -= nums[i + 1];
    }
    if (times == 0)
        total = nums[0];

    return total;
}

//Get first number of equation
double convertFloat(char* input, double total, int startIndex, int endIndex)
{
    if (strcmp(input, "NAN") == 0)
        return NAN;
    char lastNum = '0';
    short multNeg = 1;
    int numNum = 1;
    short divide = 10;

    //Used to covert equation string to a float
    for (int i = startIndex; i < endIndex; i++)
    {
        //This code is in charge of switching from adding integer parts to adding decimals
        if (!isdigit(input[i]))
        {
            //If input[i] is a decimal point, start adding decimals
            if (input[i] == '.')
            {
                if (!isdigit(input[i + 1]))
                {
                    if (input[i + 1] == '.' || isalpha(input[i + 1]) || isspace(input[i + 1]))
                        return NAN;
                    else
                        break;
                }
                else
                    lastNum = '1';
            }
            //If input[i] is a valid operation, this implies that the first number has terminated
            else if (validateOperation(input[i]) == 0)
                    break;
            else if (validateConstantChar(input[i]))
            {
                total = returnValueOfMathConstant(input, i);
                break;
            }
            else if (input[i] == 'm')
                    multNeg = -1;
            //If input[i] is a root, skip
            else if (input[i] == ' ')
                break;
            else
                return NAN;
        }
        //This part actually converts the number
        else
        {
            if (lastNum == '0')
            {
                total += input[i] - '0';
                if (isdigit(input[i + 1]))
                    total *= 10;
            }
            else
            {
                total += (input[i] - '0') / (float) pow(divide, numNum);
                numNum++;
            }
        }
    }
    total *= multNeg;
    return total;
}

//Get value of math constant multiplied by coefficient
double getMathConstant(char* input, int index, float mathConstant)
{
    float value = 0.0, coefForConsts;
    int lookback = 1, startIndexCoefficient = 0;
    if (index > 0 && isdigit(input[index - 1]))
    {
        coefForConsts = 0;
        while ((isdigit(input[index - lookback]) || input[index - lookback] == '.') && index - lookback >= 0)
        {
            startIndexCoefficient++;
            lookback++;
        }

        coefForConsts = convertFloat(input, coefForConsts, index - startIndexCoefficient, index);

        value = coefForConsts * mathConstant;
    }
    else
       value = mathConstant;

    return value;
}

//Return value of math constant multiplied by coefficient
double returnValueOfMathConstant(char* input, int i)
{
    //Pi
    if (input[i] == '!')
        return getMathConstant(input, i, M_PI);
    //Golden Ratio
    else if (input[i] == 'G')
        return getMathConstant(input, i, GOLDEN_RT);
    //Square root of 2
    else if (input[i] == 'T')
        return getMathConstant(input, i, M_SQRT2);
    //Square root of 3
    else if (input[i] == 'R')
        return getMathConstant(input, i, M_SQRT_3);
    //Euler's number
    else if (input[i] == 'E')
        return getMathConstant(input, i, M_E);
    //Silver Ratio
    else if (input[i] == 'Y')
        return getMathConstant(input, i, SILVER_RT);
    //Apery's Constant
    else if (input[i] == 'A')
        return getMathConstant(input, i, APERY_CONST);
    return 0.0;
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
