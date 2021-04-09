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
    unsigned int times = 0, location = 0, posIndex = 0, multiply = 0;
    short copyIndexStart = 0, multNeg = 1, x = 0, root = 0, numNum = 1;
    float divide = 10.0, lastCheck = 0.0;
    double total = 0.0;
    char whichNum = '0', lastNum = '0';
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

    //Check for negative first number or stuff like subtracting negative numbers and adding negative numbers
    setUp(copy);
    times = numberOfOperations(copy);
    arr = (char*) malloc(sizeof(char) * strlen(copy));
    copyStr(arr, copy);
    strcpy(copy, arr);

    //Used to check for square root, cube root, quartic root, quintic root and sixth root
    char* state = (char*) malloc(times);
    int positions[times + 1];
    for (int i = 0; i < times + 1; i++)
        positions[i] = -1;
    for (int i = 0; i < strlen(copy); i++)
    {
        if (!isascii(copy[i]))
            return NAN;
        if (validateOperation(copy[i]) == 0)
        {
            if (copy[i] == '-' || copy[i] == '+')
                multiply++;
            strncat(state, &copy[i], 1);
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
                //iterative log
                else if (strncmp(arr, "log * (", 7) == 0)
                {
                    copy[copyIndexStart] = 'm';
                    removeChar(copy, copyIndexStart, 7);
                    root++;
                    i += 6;
                }
                //log; inputed base
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
                    strcat(state, "C");
                    removeChar(copy, copyIndexStart, 3);
                }
                else if (strncmp(arr, "nPr", 3) == 0)
                {
                    copy[i] = 'P';
                    strcat(state, "P");
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

    double nums[times + 1];
    memset(nums, 0, times + 1);
    double nums1 = 0.0;
    double nums2 = 0.0;

    x = multiply;

    if (multiply == 0)
        multiply++;
    lastNum = '0';
    numNum = 0;
    multNeg = 1;

    rootOperations = (char*) malloc(root * sizeof(char));

    for (int i = 0; i < strlen(copy); i++)
    {
        if (isdigit(copy[i]))
        {
            if (i > 0)
            {
                if (!isdigit(copy[i - 1]))
                {
                    positions[posIndex] = i;
                    posIndex++;
                }
            }
            else
            {
                positions[posIndex] = i;
                posIndex++;
            }
        }
    }

    //Get all the numbers
    for (int i = 0; i < times + 1; i++)
    {
        nums[i] = convertFloat(copy, nums[i], positions[i]);
        //Check for maximum / minimum / NAN
        if (nums[0] == NAN)
            return NAN;
        else if (nums[0]> UINT_MAX)
            return INFINITY;
        else if (nums[0] < LLONG_MIN)
            return -INFINITY;
    }
    //nums[1] = convertFloat(copy, nums[1], 2);
    //Exponents
    for (int i = 0; i < times; i++)
    {
        if (state[i] == '^')
        {
            nums1 = nums[i];
            nums2 = nums[i + 1];
            nums[i] = pow(nums1, nums2);
            nums[i + 1] = 1;
            total += nums[i];
        }
    }
    //Multiplications, Division, etc.
    for (int j = 0; j < multiply; j++)
    {
        for (int i = j; i < times; i++)
        {
            if (state[i] == '*')
            {
                nums1 = nums[i + 1];
                nums2 = nums[i];
                nums[i + 1] *= nums[i];
                nums[i] = 0;
            }
            else if (state[i] == '/')
            {
                nums[i] /= nums[i + 1];
                nums[i + 1] = nums[i];
                nums[i] = 0;
            }
            else if (state[i] == 'C')
            {
                nums1 = nums[i];
                nums2 = nums[i + 1];
                nums[i] = tgamma(nums1 + 1) / (tgamma(nums2 + 1) * tgamma(nums1 - nums2));
                nums[i + 1] = nums[i];
                nums[i] = 0;
            }
            else if (state[i] == 'P')
            {
                nums1 = nums[i];
                nums2 = nums[i + 1];
                nums[i] = tgamma(nums1 + 1) / tgamma(nums1 - nums2);
                nums[i + 1] = nums[i];
                nums[i] = 0;
            }
            else if (state[i] == '+' || state[i] == '-')
                total = nums[i];
            if (x == 0)
                total = nums[i + 1];
        }
    }
    int mul = 1;
    //Addition and Subtraction
    for (int i = 0; i < times; i++)
    {
        if (state[i] == '+')
        {
            if (state[i + 1] != '+' && i != strlen(state) - 1)
            {
                while (state[i + mul] != '+' && i + mul < strlen(state)- 1)
                    mul++;
                i += mul;
            }
            total += nums[i + 1];
        }
        else if (state[i] == '-')
        {
            if (state[i + 1] != '+' && strlen(state) != 1)
            {
                while (state[i + mul] != '+' && i + mul < strlen(state) - 1)
                    mul++;
                i += mul;
            }
            total -= nums[i + 1];
        }
    }
    return total;
}
//Get first number of equation
double convertFloat(char* input, double total, int startIndex)
{
    if (strcmp(input, "NAN") == 0)
        return NAN;
    char lastNum = '0';
    int multNeg = 1;
    int numNum = 1;
    float divide = 10.0;

    //Used to covert copy string to a float
    for (int i = startIndex; i < strlen(input); i++)
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
