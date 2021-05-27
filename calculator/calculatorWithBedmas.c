/**************************************************************************************************************************
 * Developper logs:
 * - 5/25/2021: Version 1.02 - Added PI functionality. Fix bug where it says "PI = 6.283..."
 * - 5/26/2021: Version 1.03
 *      - Bug 1 (incorrect value of PI) - PATCHED
 *      - Bug 2 (nCr and nPr doesn't work properly) - PATCHED
 *      - Bug 3 (incorrect value of a + b * c) - PATCHED - BEDMAS is handled differently now
 *          - This lead to Bug (a - b where a < b) - PATCHED
 *      - Bug 4 (incorrect value of a % b + c) - PATCHED
 *      - Bug 5 (incorrect value of a + b % c) - PATCHED
 *      - Bug 6 (fraction addition doesn't work) - PATCHED
 *      - Bug 7 (where adding 5 of any number returns -nan) - PATCHED - Zeroing all elements is now handled manually
 *      - Bug 8 (cPI has incorrect value, where c is a number (e.g. 2PI)) - PATCHED
 *
 * - 5/26/2021: Version 1.04 - Added the constants: Golden Ratio, Root 2, Root 3, Euler's number.
***************************************************************************************************************************/

#include "defs.h"

void push_back(char* str, int index);
double getMathConstant(char* input, int i, float mathConstant);

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
    unsigned int times = 0, location = 0, posIndex = 0, multiply = 0;
    short x = 0, root = 0;
    double total = 0.0;
    char* copy = (char*) malloc(strlen(input) * sizeof(char));
    char* testIfNull = strchr(input, ' ');
    char* arr = (char*) malloc(ARRAY_SIZE * sizeof(char));

    if (testIfNull != NULL)
        if (strlen(input) == 0 || strcmp(input, testIfNull) == 0)
            return NAN;

    formatInput(input);
    strcpy(copy, input);

    if (strcmp(copy, "NAN") == 0)
        return NAN;

    for (int i = 0; i < strlen(copy); i++)
    {
        if (!isascii(copy[i]))
            return NAN;
        if (isalpha(copy[i]))
        {
            strncat(arr, &input[i], ARRAY_SIZE);
            if (copy[i] == 'P')
            {
                if (strncmp(arr, "PI", 2) == 0)
                {
                    copy[i] = '!';
                    removeChar(copy, i, 1);
                    i++;
                }
                else
                    return NAN;
            }
            else if (copy[i] == 'G')
            {
                if (strncmp(arr, "GOLDEN_RT", 9) == 0)
                {
                    removeChar(copy, i, 8);
                    i += 8;
                }
            }
            else if (copy[i] == 'S')
            {
                if (strncmp(arr, "SQRT_2", 6) == 0)
                {
                    copy[i] = 'T';
                    removeChar(copy, i, 5);
                    i += 5;
                }
                else if (strncmp(arr, "SQRT_3", 6) == 0)
                {
                    copy[i] = 'R';
                    removeChar(copy, i, 5);
                    i += 5;
                }
            }
            else if (copy[i] == 'E');
            else if (copy[i] == 'n')
            {
                if (strncmp(arr, "nPr", 3) == 0)
                {
                    copy[i] = 'P';
                    removeChar(copy, i, 2);
                    i += 2;
                }
                else if (strncmp(arr, "nCr", 3) == 0)
                {
                    copy[i] = 'C';
                    removeChar(copy, i, 2);
                    i += 2;
                }
                else
                    return NAN;
            }
            else
                return NAN;
        }
    }

    setUp(copy);

    times = numberOfOperations(copy);

    char* state = (char*) malloc(times);
    int positions[times + 1];
    memset(positions, -1, times + 1);

    for (int i = 0; i < strlen(copy); i++)
    {
        if (validateOperation(copy[i]) == 0)
        {
            if (copy[i] == '-' || copy[i] == '+')
                multiply++;
            strncat(state, &copy[i], 1);
        }
    }

    x = multiply;

    if (multiply == 0)
        multiply++;

    for (int i = 0, n = strlen(copy); i < strlen(copy); i++)
    {
        if (isdigit(copy[i]))
        {
            if (i > 0)
            {
                if (!isdigit(copy[i - 1]) && copy[i - 1] != 'm' && copy[i - 1] != '.')
                {
                    positions[posIndex] = i;
                    posIndex++;
                }
            }
            else
            {
                if (copy[i + 1] != '!')
                {
                    positions[posIndex] = i;
                    posIndex++;
                }
            }
        }
        else
        {
            if (copy[i] == '-' && isdigit(copy[i + 1]) && !isdigit(copy[i - 1]))
            {
                copy[i] = 'm';
                positions[posIndex] = i;
                posIndex++;
                times--;
                push_back(state, 0);
            }
            else if (validateConstantChar(copy[i]))
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
        nums[i] = convertFloat(copy, nums[i], positions[i], strlen(copy));
        //Check for maximum / minimum / NAN
        if (nums[0] == NAN)
            return NAN;
        else if (nums[0]> UINT_MAX)
            return INFINITY;
        else if (nums[0] < LLONG_MIN)
            return -INFINITY;
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
            nums[i + 1] = tgamma(nums[i] + 1) / (tgamma(nums[i + 1] + 1) * tgamma(nums[i] - nums[i + 1]));
            nums[i + 1] /= 2;
            total += nums[i + 1];
            nums[i] = 0;
        }
        else if (state[i] == 'P')
        {
            nums[i + 1] = tgamma(nums[i] + 1) / tgamma(nums[i] - nums[i + 1]);
            nums[i + 1] /= 2;
            total += nums[i + 1];
            nums[i] = 0;
        }
        if (x == 0)
            total = nums[i + 1];
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

    //Used to covert copy string to a float
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
            else if (input[i] == '!')
            {
                total = getMathConstant(input, i, M_PI);
                break;
            }
            else if (input[i] == 'G')
            {
                total = getMathConstant(input, i, GOLDEN_RT);
                break;
            }
            else if (input[i] == 'T')
            {
                total = getMathConstant(input, i, M_SQRT2);
                break;
            }
            else if (input[i] == 'R')
            {
                total = getMathConstant(input, i, M_SQRT_3);
                break;
            }
            else if (input[i] == 'E')
            {
                total = getMathConstant(input, i, M_E);
            }
            else if (input[i] == 'm')
                    multNeg = -1;
            //If input[i] is a root, skip
            else if (validateRoot(input[i]) == 0 || input[i] == ' ')
                continue;
            else if (input[i] == 'a' || input[i] == 'y');
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

double getMathConstant(char* input, int i, float mathConstant)
{
    float value = 0.0, coefForConsts;
    int lookback = 1, startIndexCoefficient = 0;
    if (i > 0 && isdigit(input[i - 1]))
    {
        coefForConsts = 0;
        while ((isdigit(input[i - lookback]) || input[i - lookback] == '.') && i - lookback >= 0)
        {
            startIndexCoefficient++;
            lookback++;
        }

        coefForConsts = convertFloat(input, coefForConsts, i - startIndexCoefficient, i);

        value = coefForConsts * mathConstant;
    }
    else
       value = mathConstant;
    return value;
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

//Push back string
void push_back(char* str, int index)
{
    for (int i = index; i < strlen(str) - 1; i++)
        str[i] = str[i + 1];
}
