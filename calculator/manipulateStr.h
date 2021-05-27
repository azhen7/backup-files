#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(void);

//String char checking
//See if input[i] is a valid operation (+, -, etc.)
unsigned int validateOperation(char c)
{
    if (c == '+' || c == '*' || c == '-' || c == '/' || c == '^' || c == '%' || c == 'e' || c == 'C' || c == 'P')
        return 0;
    return 1;
}
//See if input[i] represents a root/trig/hyperbolic trig/log function (sqrt, cbrt, sin, cos, sinh, cosh, log, ln, etc.)
unsigned int validateRoot(char c)
{
    if (c == '@' || c == '#' || c == '$' || c == '~' || c == '<' || c == '&' || c == '!' || c == ';'
        || c == ':' || c == 34 || c == '>' || c == '?' || c == '|' || c == '{' || c == '}' || c == '('
        || c == ')' || c == 'c' || c == 39 || c == 92 || c == '\f' || c == 'f' || c == 'l' || c == 'm'
        || c == 'v' || c == 'n' || c == 'o' || c == 'p' || c == 'q' || c == 'r' || c == 's' || c == 't'
        || c == 'u' || c == 'k' || c == 'S' || c == 'M' || c == 'w' || c == 'x' || c == 'D' || c == 'y'
        || c == 'z' || c == 'F' || c == 'I' || c == 'J' || c == 'L' || c == 'N' || c == 'O')
        return 0;
    return 1;
}
//Validate char
unsigned int validNext(char c)
{
    if (isdigit(c) || c == 'm' || c == 'a' || c == ' ' || validateRoot(c) == 0)
        return 0;
    return 1;
}
//Check whether char is first character of math constant (e.g. PI)
unsigned int validateConstantChar(char c)
{
    if (c == '!' || c == 'T' || c == 'R' || c == 'G' || c == 'E')
        return 1;
    return 0;
}

//Changing strings
//Set chars to ' '
void removeChar(char* input, int index, int c)
{
    for (int i = 0; i < c; i++)
        input[index + 1 + i] = ' ';
}
//Format input
void formatInput(char* input)
{
    char* formattedInput = (char*) malloc(sizeof(char) * strlen(input));
    unsigned short encounteredSpace;
    unsigned short operation = 0;
    for (int i = 0; i < strlen(input); i++)
    {
        if (validateOperation(input[i]) == 0)
        {
            strncat(formattedInput, &input[i], 1);
            if (operation == 0)
                operation = 1;
            else
                operation = 0;
            if (isdigit(input[i + 1]) && !isalpha(input[i + 2]))
                strcat(formattedInput, " ");
        }
        if (isdigit(input[i]) && isalpha(input[i + 1]))
        {
            strncat(formattedInput, &input[i], 1);
            continue;
        }
        if (input[i] == ' ')
        {
            if (isdigit(input[i + 1]) || validateRoot(input[i + 1]) == 0)
            {
                operation = 0;
                encounteredSpace = 0;
            }
            if ((encounteredSpace == 0 && operation == 0) || isalpha(input[i - 1]) || isalpha(input[i + 1]))
            {
                strcat(formattedInput, " ");
                encounteredSpace = 1;
            }
        }
        else if (validateOperation(input[i]) == 1)
        {
            strncat(formattedInput, &input[i], 1);
            encounteredSpace = 0;
            if (validateOperation(input[i + 1]) == 0)
                strcat(formattedInput, " ");
        }
    }
    strcpy(input, formattedInput);
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
                else if (isdigit(copy[i + 1]) || validateRoot(copy[i + 1]) == 0 || copy[i + 1] == 'P');
                else
                {
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
                else if (isdigit(copy[i + 1]) || validateRoot(copy[i + 1]) == 0 || copy[i + 1] == 'P')
                {
                    if (encounteredNum == 0 && !isdigit(copy[i - 1]))
                        copy[i] = 'm';
                }
                else
                {
                    strcpy(copy, "NAN");
                    break;
                }
            }
        }
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
                else
                {
                    strcpy(copy, "NAN");
                    break;
                }
            }
        }
        else if (copy[i] == '/')
        {
            if (copy[i + 1] != ' ')
            {
                strcpy(copy, "NAN");
                break;
            }
        }
    }
}
