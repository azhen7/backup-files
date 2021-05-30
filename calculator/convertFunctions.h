#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <math.h>

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
        return NULL;

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
                sprintf(&temp, "%c", mod + 48 + (7 * (mod >= 10)));

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
                    if (input[i] - 87 > base_input - 1)
                        return 1;
                }
                else if (isupper(input[i]))
                {
                    if (input[i] - 55 > base_input - 1)
                        return 1;
                }
            }
        }
        else
            return 1;
    }
    return 0;
}
