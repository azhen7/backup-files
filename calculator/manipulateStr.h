#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(void);

//String char checking
//See if input[i] is a valid operation (+, -, etc.)
unsigned int validateOperation(char c)
{
    if (c == '+' || c == '*' || c == '-' || c == '/' || c == '^' || c == '%' || c == 'e' || c == 'C' || c == 'P'
        || c == ',')
        return 0;
    return 1;
}
//See if input[i] represents a root/trig/hyperbolic trig/log function (sqrt, cbrt, sin, cos, sinh, cosh, log, ln, etc.)
unsigned int validateRoot(char c)
{
    if (c == '@' || c == '#' || c == '$' || c == '~' || c == '<' || c == '&' || c == '!' || c == ';'
        || c == ':' || c == 34 || c == '>' || c == '?' || c == '|' || c == '{' || c == '}' || c == '('
        || c == ')' || c == 'c' || c == 39 || c == 92 || c == '\f' || c == 'f' || c == 'l' || c == 'v'
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

//Changing strings
//Set chars to ' '
void removeChar(char* input, int index, int c)
{
    for (int i = 0; i < c - 1; i++)
        input[index + 1 + i] = ' ';
}
//Copy input to copy without spaces
void copyStr(char* destination, char* source)
{
    for (int i = 0; i < strlen(source); i++)
    {
        if (source[i] == 32)
            continue;
        strncat(destination, &source[i], 1);
    }
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
        }
        if (input[i] == ' ')
        {
            if (isdigit(input[i + 1]))
            {
                operation = 0;
                encounteredSpace = 0;
            }
            if (encounteredSpace == 0 && operation == 0)
            {
                strcat(formattedInput, " ");
                encounteredSpace = 1;
            }
        }
        else if (validateOperation(input[i]) == 1)
        {
            strncat(formattedInput, &input[i], 1);
            encounteredSpace = 0;
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
                else if (isdigit(copy[i + 1]) || validateRoot(copy[i + 1]) == 0);
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
                else if (isdigit(copy[i + 1]) || validateRoot(copy[i + 1]) == 0)
                {
                    if (encounteredNum == 0)
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
//Append root representation onto a string
void assignRootOperations(char* rootOperations, int numNum, char* copy, int i, char state)
{
    //sqrt
    if (copy[i] == '#')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(rootOperations, "0");
        }
        else
            if (numNum == 0)
                strcat(rootOperations, "1");
    }
    //cbrt
    else if (copy[i] == '@')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(rootOperations, "2");
        }
        else
            if (numNum == 0)
                strcat(rootOperations, "3");
    }
    //quartic root
    else if (copy[i] == '$')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(rootOperations, "4");
        }
        else
            if (numNum == 0)
                strcat(rootOperations, "5");
    }
    //quintic root
    else if (copy[i] == '~')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(rootOperations, "6");
        }
            else
                if (numNum == 0)
                    strcat(rootOperations, "7");
    }
    //squaring
    else if (copy[i] == '<')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(rootOperations, "8");
        }
        else
            if (numNum == 0)
                strcat(rootOperations, "9");
    }
    //cubing
    else if (copy[i] == '&')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(rootOperations, "[");
        }
        else
            if (numNum == 0)
                strcat(rootOperations, "]");
    }
    //sixth root
    else if (copy[i] == '!')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(rootOperations, ";");
            else
                strcat(rootOperations, "F");
        }
        else
            if (numNum == 0)
                strcat(rootOperations, ":");
            else
                strcat(rootOperations, "G");
    }
    //sin
    else if (copy[i] == ':')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(rootOperations, "{");
        }
        else
            if (numNum == 0)
                strcat(rootOperations, "}");
    }
    //cos
    else if (copy[i] == ';')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(rootOperations, "~");
        }
        else
            if (numNum == 0)
                strcat(rootOperations, "`");
    }
    //tan
    else if (copy[i] == 92)
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(rootOperations, "=");
        }
        else
            if (numNum == 0)
                strcat(rootOperations, "_");
    }
    //arcsin
    else if (copy[i] == '>')
        {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(rootOperations, "(");
        }
        else
            if (numNum == 0)
                strcat(rootOperations, ")");
    }
    //arccos
    else if (copy[i] == '?')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(rootOperations, ",");
        }
        else
            if (numNum == 0)
                strcat(rootOperations, ".");
    }
    //arctan
    else if (copy[i] == '|')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(rootOperations, "<");
        }
        else
            if (numNum == 0)
                strcat(rootOperations, ">");
    }
    //sinh
    else if (copy[i] == 34)
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(rootOperations, " ");
        }
        else
            if (numNum == 0)
                strcat(rootOperations, "a");
    }
    //cosh
    else if (copy[i] == 39)
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(rootOperations, "b");
        }
        else
            if (numNum == 0)
                strcat(rootOperations, "c");
    }
    //tanh
    else if (copy[i] == '\f')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(rootOperations, "d");
        }
        else
            if (numNum == 0)
                strcat(rootOperations, "e");
    }
    //arcsinh
    else if (copy[i] == '{')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(rootOperations, "+");
        }
        else
            if (numNum == 0)
                strcat(rootOperations, "-");
    }
    //arccosh
    else if (copy[i] == '}')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(rootOperations, "*");
        }
        else
            if (numNum == 0)
                strcat(rootOperations, "/");
    }
    //arctanh
    else if (copy[i] == '(')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(rootOperations, "@");
        }
        else
            if (numNum == 0)
                strcat(rootOperations, "#");
    }
    //ceil
    else if (copy[i] == 'c')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(rootOperations, "f");
        }
        else
            if (numNum == 0)
                strcat(rootOperations, "g");
    }
    //floor
    else if (copy[i] == 'f')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(rootOperations, "h");
        }
        else
            if (numNum == 0)
                strcat(rootOperations, "i");
    }
    //ln
    else if (copy[i] == 'l')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(rootOperations, "j");
        }
        else
            if (numNum == 0)
                strcat(rootOperations, "k");
    }
    //log base 10
    else if (copy[i] == 'k')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(rootOperations, "l");
        }
        else
            if (numNum == 0)
                strcat(rootOperations, "m");
    }
    //log base 2
    else if (copy[i] == 'n')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(rootOperations, "n");
        }
        else
            if (numNum == 0)
                strcat(rootOperations, "o");
    }
    //log base 3
    else if (copy[i] == 'o')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(rootOperations, "p");
        }
        else
            if (numNum == 0)
                strcat(rootOperations, "q");
    }
    //log base 4
    else if (copy[i] == 'p')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(rootOperations, "r");
        }
        else
            if (numNum == 0)
                strcat(rootOperations, "s");
    }
    //log base 5
    else if (copy[i] == 'q')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(rootOperations, "t");
        }
        else
            if (numNum == 0)
                strcat(rootOperations, "u");
    }
    //log base 6
    else if (copy[i] == 'r')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(rootOperations, "v");
        }
        else
            if (numNum == 0)
                strcat(rootOperations, "w");
    }
    //log base 7
    else if (copy[i] == 's')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(rootOperations, "x");
        }
        else
            if (numNum == 0)
                strcat(rootOperations, "y");
    }
    //log base 8
    else if (copy[i] == 't')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(rootOperations, "z");
        }
        else
            if (numNum == 0)
                strcat(rootOperations, "A");
    }
    //log base 9
    else if (copy[i] == 'u')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(rootOperations, "B");
        }
        else
            if (numNum == 0)
                strcat(rootOperations, "C");
    }
    //log base 1
    else if (copy[i] == 'v')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(rootOperations, "D");
        }
        else
            if (numNum == 0)
                strcat(rootOperations, "E");
    }
    //absolute value
    else if (copy[i] == 'w')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(rootOperations, "H");
        }
        else
            if (numNum == 0)
                strcat(rootOperations, "I");
    }
    //seventh root
    else if (copy[i] == 'x')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(rootOperations, "J");
        }
        else
            if (numNum == 0)
                strcat(rootOperations, "K");
    }
    //GCD
    else if (copy[i] == 'y')
    {
        if (numNum == 0)
            strcat(rootOperations, "L");
    }
    //LCM
    else if (copy[i] == 'z')
    {
        if (numNum == 0)
            strcat(rootOperations, "M");
    }
    //Arithmetic mean
    else if (copy[i] == 'F')
    {
        if (numNum == 0)
            strcat(rootOperations, "N");
    }
    //Geometric mean
    else if (copy[i] == 'I')
    {
        if (numNum == 0)
            strcat(rootOperations, "O");
    }
    //sinc
    else if (copy[i] == 'J')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(rootOperations, "P");
        }
        else
            if (numNum == 0)
                strcat(rootOperations, "Q");
    }
    //sec
    else if (copy[i] == 'L')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(rootOperations, "R");
        }
        else
            if (numNum == 0)
                strcat(rootOperations, "S");
    }
    //cotangent
    else if (copy[i] == 'N')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(rootOperations, "T");
        }
        else
            if (numNum == 0)
                strcat(rootOperations, "U");
    }
    //cosecant
    else if (copy[i] == 'O')
    {
        if (state == '\0')
        {
            if (numNum == 0)
                strcat(rootOperations, "V");
        }
        else
            if (numNum == 0)
                strcat(rootOperations, "W");
    }
}
