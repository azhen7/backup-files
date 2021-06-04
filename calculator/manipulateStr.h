#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(void);

//String char checking
//See if input[i] is a valid operation (+, -, etc.)
unsigned int validateOperation(char c)
{
    if (c == '+' || c == '*' || c == '-' || c == '/' || c == '^' || c == '%' || c == 'e' || c == 'C' || c == 'P'
        || c == ',' || c == 'x')
        return 0;
    return 1;
}
//Check whether char is representative of a math constant (e.g. PI)
unsigned int validateConstantChar(char c)
{
    if (c == '!' || c == 'T' || c == 'R' || c == 'G' || c == 'E' || c == 'Y' || c == 'A')
        return 1;
    return 0;
}
//Check whether char is first character of math constant
unsigned int validateConstantFirstChar(char c)
{
    if (c == 'P' || c == 'G' || c == 'S' || c == 'R' || c == 'A' || c == 'C' || c == 'p' || c == 's')
        return 1;
    return 0;
}
//Validate char
unsigned int validNext(char c)
{
    if (isdigit(c) || c == 'm' || c == ' ' || c == '-' || validateConstantChar(c))
        return 0;
    return 1;
}
//Changing strings
//Set chars to ' '
void removeChar(char* input, int index, int c)
{
    for (int i = 0; i < c; i++)
        input[index + 1 + i] = ' ';
}
char* copyStrWithoutSpaces(char* input)
{
    char* strWithoutSpaces = (char*) malloc(strlen(input));
    for (int i = 0; i < strlen(input); i++)
    {
        if (input[i] != ' ')
            strncat(strWithoutSpaces, &input[i], 1);
    }
    return strWithoutSpaces;
}
//Check for "--" or "+-"
void setUp(char* copy)
{
    unsigned short encounteredNum = 0;
    for (int i = 0; i < strlen(copy); i++)
    {
        //if copy[i] is a space, save an iteration
        if (copy[i] == ' ')
            continue;
        if (isdigit(copy[i]))
        {
            encounteredNum = 1;
            continue;
        }
        if (copy[i] == '+')
        {
            if (copy[i + 1] != ' ')
            {
                if (copy[i + 1] == '-')
                {
                    copy[i] = '-';
                    copy[i + 1] = ' ';
                }
                else if (isdigit(copy[i + 1]) || copy[i + 1] == 'P');
                else
                {
                    copy = (char*) malloc(3);
                    strcpy(copy, "NAN");
                    break;
                }
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
                else if (copy[i + 1] == '+')
                    copy[i + 1] = ' ';
                else if (isdigit(copy[i + 1]) || copy[i + 1] == 'P');
                else
                {
                    copy = (char*) malloc(3);
                    strcpy(copy, "NAN");
                    break;
                }
            }
        }
        else if (copy[i] == 'x')
            copy[i] = '*';
        else if (copy[i] == '*')
        {
            if (i > 0)
            {
                if (copy[i + 1] == '*' && copy[i + 2] != ' ')
                {
                    strcpy(copy, "NAN");
                    break;
                }
            }
            if (copy[i + 1] != ' ')
            {
                if (copy[i + 1] == '*')
                {
                    copy[i] = '^';
                    copy[i + 1] = ' ';
                }
                else if (isdigit(copy[i + 1]) || copy[i + 1] == '-');
                else
                {
                    copy = (char*) malloc(3);
                    strcpy(copy, "NAN");
                    break;
                }
            }
        }
        else if (copy[i] == '/')
        {
            if (copy[i + 1] != ' ')
            {
                copy = (char*) malloc(3);
                strcpy(copy, "NAN");
                break;
            }
        }
    }
}
