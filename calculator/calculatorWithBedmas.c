/***************************************************************************************************************
 * Developper logs:
 * - 5/25/2021: Version 1.02
 *      - Added PI functionality.
 *      - Note: Fix bug where it says "PI = 6.283..."
 *
 * - 5/26/2021: Version 1.03
 *      - Bug 1 (incorrect value of PI) - PATCHED
 *      - Bug 2 (nCr and nPr doesn't work properly) - PATCHED
 *      - Bug 3 (incorrect value of a + b * c) - PATCHED - BEDMAS is handled differently now
 *          - This lead to Bug (a - b where a < b) - PATCHED
 *      - Bug 4 (incorrect value of a % b + c) - PATCHED
 *      - Bug 5 (incorrect value of a + b % c) - PATCHED
 *      - Bug 6 (fraction addition doesn't work) - PATCHED
 *      - Bug 7 (where adding 5 of any number returns -nan) - PATCHED - Zeroing all elements is now handled manually instead of using memset()
 *      - Bug 8 (cPI has incorrect value, where c is a number (e.g. 2PI)) - PATCHED
 *
 * - 5/26/2021: Version 1.04
 *      - Added the constants: Golden Ratio, Root 2, Root 3, Euler's number.
 *
 * - 5/27/2021: Version 1.05
 *      - Added Silver Ratio, Apery's Constant.
 *      - Bug 9 (Seg fault when input string has no spaces) - PATCHED
 *      - Added sqrt and cbrt
 *          - Bug 10 (sqrt(a) where a < 0 = 0) - PATCHED
 *          - Bug 11 (a + sqrt(b) returns value of sqrt(a) + b) - PATCHED
 *
 * - 5/28/2021: Version 1.06
 *      - sqrt and cbrt has been removed
 *      - Added root() function (root(a, b) returns bth root of a (e.g. root(4, 2) returns square root of 4))
 *          - Bug 12 (a root( + b, c returns value of a + root(b, c)) - PATCHED
 *          - Bug 13 (a + root(b, c) = NAN) - PATCHED
 *          - Bug 14 (4 nCr 2 = 2 * the correct value) - PATCHED
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

    system("clear");
    printf("Enter a bunch of equations below: \n");

    while (1)
    {
        getEquation = get_string("");
        result = solveEquation(getEquation);

        //Erase equation typed by user
        fputs("\033[A\033[2K", stdout);
        rewind(stdout);

        printf("%s = %f\n", getEquation, result);
        putchar('\n');
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
        if (isalpha(equation[i]))
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
            else if (equation[i] == 'G')
            {
                if (strncmp(arr, "GOLDEN_RT", 9) == 0)
                {
                    removeChar(equation, i, 8);
                    i += 8;
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
                //cbrt
                if (strncmp(arr, "root(", 5) == 0)
                {
                    removeChar(equation, i - 1, 5);
                    functionPositions[numberOfFunctions] = i;
                    numberOfFunctions++;
                    i += 5;
                    strcat(functions, "1");
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
            else if (equation[i] == 'E');
            else
                return NAN;
        }
    }

    setUp(equation);

    times = numberOfOperations(equation);

    char* state = (char*) malloc(times);
    int* operationPositions = (int*) malloc(times);
    unsigned int operationPositionIndex = 0;
    unsigned short numberOfSeperators = 0;
    int positions[times + 1];
    memset(positions, -1, times + 1);

    for (int i = 0; i < strlen(equation); i++)
    {
        if (validateOperation(equation[i]) == 0)
        {
            if (equation[i] != ',')
            {
                strncat(state, &equation[i], 1);
                operationPositions[operationPositionIndex] = i;
                operationPositionIndex++;
            }
            else
            {
                numberOfSeperators++;
                if (strlen(functions) < numberOfSeperators)
                    return NAN;
            }
        }
    }

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
    }

    unsigned int location = 0;
    unsigned index = 0;
    for (int i = 0; i < numberOfFunctions; i++)
    {
        for (int j = 0; j < times + 1; j++)
        {
            if (functionPositions[index] < positions[j])
            {
                if (functionPositions[index] > operationPositions[j - 1] && operationPositionIndex > 0)
                {
                    location = j;
                    break;
                }
                else if (operationPositionIndex == 0)
                    break;
                else
                    return NAN;
            }
        }
        if (functions[i] == '1')
            nums[location] = pow(nums[location], 1 / nums[location + 1]);
        index++;
    }
    //Modulo operation
    for (int i = 0; i < times; i++)
    {
        if (state[i] == '%')
        {
            nums[i + 1] = fmod(nums[i], nums[i + 1]);
            nums[i] = 0 + 1 * (state[i - 1] == '*');
            if (state[i - 1] == '+')
                state[i] = '+';
            else if (state[i - 1] == '-')
                state[i] = '-';
            else if (state[i - 1] == '*')
                state[i] = '*';
            else if (state[i - 1] == '/')
                state[i] = '/';
        }
    }
    //Multiplications, Division, nCr, nPr
    for (int i = 0; i < times; i++)
    {
        if (state[i] == '*')
        {
            nums[i + 1] *= nums[i];
            nums[i] = 0;
            state[i] = state[i - 1];
        }
        else if (state[i] == '/')
        {
            nums[i] /= nums[i + 1];
            nums[i + 1] = nums[i];
            nums[i] = 0;
            state[i] = state[i - 1];
        }
        else if (state[i] == 'C')
        {
            nums[i + 1] = tgamma(nums[i] + 1) / (tgamma(nums[i + 1] + 1) * tgamma(nums[i] - nums[i + 1] + 1));
            total += nums[i + 1];
            nums[i] = 0;
        }
        else if (state[i] == 'P')
        {
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
    for (int i = 0; i < times; i++)
    {
        if (state[i] == '+')
            total += nums[i + 1];
        else if (state[i] == '-')
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
                    break;
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
            else if (validateRoot(input[i]) == 0 || input[i] == ' ')
                continue;
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
