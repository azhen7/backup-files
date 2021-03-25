#include <stdio.h>
#include <ctype.h>
#include <cs50.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

char* invert_letters(char* input);
char* convert(char* input, int base_input, int base_convert);
int validateInput(char* input, int base_input);
long int convertBaseTen(char* input, int base_input);
void timeOfExecution();

int main(int argc, char* argv[])
{
    timeOfExecution();
    char* input; //input
    char* result; //the result
    int base_input; //base of input
    int base_convert; //base to convert to

    if (argc != 2)
    {
        if (argc > 2)
            printf("Too many arguments.\n");
        else
            printf("Too few arguments.\n");
        return 0;
    }

    for (int i = 0; i < atoi(argv[1]); i++)
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

        input = get_string("Enter input: ");

        if (validateInput(input, base_input))
            printf("Invalid input.\n\n");
        else
        {
            result = convert(input, base_input, base_convert);

            if (strcmp(result, "-1") != 0)
                printf("Your input in base %i is: %s\n\n", base_convert, result);
            else
                perror("Memory allocation failed.\n");
        }
    }
}

void timeOfExecution()
{
    int hours = atoi(__TIME__);
    char* append = strchr(__TIME__, ':');
    hours -= 4;
    if (hours < 0)
       hours = 24 + hours;

    char* ret = (char*) malloc(10);
    sprintf(ret, "%i%s", hours, append);
    printf("Program started at %s EST.\n", ret);
}

char* invert_letters(char* input)
{
    char temp;
    for (int i = 0, n = strlen(input); i < n / 2; i++)
    {
        temp = input[i];
        input[i] = input[n - i - 1];
        input[n - i - 1] = temp;
    }
    return input;
}

//Convert input
char* convert(char* input, int base_input, int base_convert)
{
    long int decimalForm = 0;
    int addToDecimal;

    decimalForm = convertBaseTen(input, base_input);

    //Allocate 50 bytes of memory for result
    char* result = (char*) malloc(50 * sizeof(char));

    if (result == NULL)
    {
        return (char*) -1;
    }

    if (base_convert != 10 && base_input != 10)
        printf("Converting to base 10: %li\n", decimalForm);

    //If base_convert == base_input, the input in base_input is the same as the output in base_convert => 100 in base 5 = 100 in base 5
    if (base_convert != base_input)
    {
        if (base_convert == 10)
            sprintf(result, "%li", decimalForm);
        else
        {
            int times = 0; //Number of times to divide input by base to convert to
            int mod;
            char temp = '\0';

            addToDecimal = decimalForm;
            while (addToDecimal != 0)
            {
                times++;
                addToDecimal /= base_convert;
            }

            times++;

            for (int i = 0; i < times && decimalForm != 0; i++)
            {
                //Find the remainder of decimalForm / base_convert. Update decimalForm to be the quotient of decimalForm / base_convert
                mod = decimalForm % base_convert;
                decimalForm /= base_convert;

                //Append the remainder to the result array. If mod >= 10, append the mod in the form of letters
                sprintf(&temp, "%c", mod + 48 + (39 * (mod >= 10)));

                strcat(result, &temp);
            }
            if (base_convert == 16)
                strcat(result, "x0");

            //Read the remainders backwards
            invert_letters(result);
        }
    }
    else
        sprintf(result, "%s", input);

    return result;
}

//Validate the input
int validateInput(char* input, int base_input)
{
    int addToDecimal;
    //Check if input is valid
    for (int i = 0; i < strlen(input); i++)
    {
        if (isdigit(input[i]))
        {
            addToDecimal = input[i] - '0';
            if (addToDecimal > base_input - 1)
                return 1;
        }
        else if (isalpha(input[i]))
        {
            if (base_input <= 10)
                return 1;
            else
            {
                if (islower(input[i]))
                {
                    if ((int) input[i] - 87 > base_input - 1)
                        return 1;
                }
                else if (isupper(input[i]))
                {
                    if ((int) input[i] - 55 > base_input - 1)
                        return 1;
                }
            }
        }
        else
            return 1;
    }
    return 0;
}

long int convertBaseTen(char* input, int base_input)
{
    long int decimal = 0;
    int addToDecimal = 0;

    //Convert input to decimal
    if (base_input == 10)
        decimal = atoi(input);
    else
    {
        //Convert input to base 10
        for (int i = 0, n = strlen(input); i < n; i++)
        {
            if (isdigit(input[i]))
            {
                addToDecimal = input[i] - '0';
                addToDecimal *= pow(base_input, n - i - 1);
                decimal += addToDecimal;
            }
            else if (isalpha(input[i]))
            {
                if (isupper(input[i]))
                {
                    addToDecimal = (int) input[i] - 55;
                    addToDecimal *= pow(base_input, n - i - 1);
                    decimal += addToDecimal;
                }
                else if (islower(input[i]))
                {
                    addToDecimal = (int) input[i] - 87;
                    addToDecimal *= pow(base_input, n - i - 1);
                    decimal += addToDecimal;
                }
            }
        }
    }
    return decimal;
}