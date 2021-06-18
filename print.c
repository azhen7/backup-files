//My own implementation of printf
#define _GNU_SOURCE
#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include <limits.h>

int print(char* str, ...);
void precisionFloat(char* strfromPrecision, int lengthOfIntegerPart, int precision, long double doubleNum);
void cutOffExcessDecimalDigits(char* decimalAsStr, int len);
char* long_long_to_str(long long int num, char* buffer);

int main(void) {
    print("%lli\n", -7);
}

int print(char* str, ...) {
    int numCharsPrinted = 0;
    long long ll_intNum = 0;
    double doubleNum = 0.0;
    long double l_doubleNum;
    char* strVar = NULL;

    va_list vl;
    va_start(vl, str);
    for (int i = 0; i < strlen(str); i++) {
        //Conversion specifications
        if (str[i] == '%') {
            i++;
            //%i or %d
            if (str[i] == 'i' || str[i] == 'd') {
                int numDigits = 0;
                ll_intNum = va_arg(vl, int);

                if (ll_intNum >= INT_MAX) {
                    puts("\rERROR: Argument too large to represent as int.");
                    return -1;
                }
                int intNum = ll_intNum;

                if (intNum == 0)
                    putchar('0');
                if (intNum < 0)
                {
                    putchar('-');
                    intNum = -intNum;
                }

                numDigits = floor(log10(abs(intNum))) + 1;
                char* strFromInt = malloc(numDigits);
                long_long_to_str((long long int) intNum, strFromInt);
                fputs(strFromInt, stdout);
                numCharsPrinted += numDigits - 1;
            }
            //%f
            else if (str[i] == 'f' || (str[i] == 'l' && str[i + 1] == 'f')) {
                doubleNum = va_arg(vl, double);
                if (fabs(doubleNum) < 0.000001) {
                    doubleNum = va_arg(vl, int);
                }
                int len = floor(log10(abs((int) doubleNum))) + 1;
                char* decimalAsStr = malloc(len + 7);

                gcvt(doubleNum, len + 6, decimalAsStr);
                //If decimalAsStr is has no decimal places, append .000000 onto the end of it
                if ((int) atof(decimalAsStr) == atof(decimalAsStr))
                    strcat(decimalAsStr, ".000000");
                //Otherwise, append 0s until there are 6 decimal digits
                else {
                    int addLength = strlen(decimalAsStr);
                    for (int j = 0; j + addLength < 7 + len; j++)
                        strcat(decimalAsStr, "0");
                }
                cutOffExcessDecimalDigits(decimalAsStr, len); //Cut off excess digits so that there are only 6 decimal digits. Round accordingly.
                fputs(decimalAsStr, stdout);
                numCharsPrinted += 7 + len;
                free(decimalAsStr);
            }
            //%c
            else if (str[i] == 'c') {
                int intNum = va_arg(vl, int);
                putchar(intNum);
            }
            //%s
            else if (str[i] == 's') {
                strVar = va_arg(vl, char*);
                fputs(strVar, stdout);
                numCharsPrinted += strlen(strVar) - 1;
            }
            //%li and %lli / %lld (long int and long long int conversion specifications)
            else if (str[i] == 'l') {
                i++;
                //%li or %ld
                if (str[i] == 'i' || str[i] == 'd') {
                    ll_intNum = va_arg(vl, long int);
                    int l_intNum = ll_intNum;
                    int numDigits = 0;
                    if (l_intNum == 0)
                        putchar('0');
                    if (l_intNum < 0)
                    {
                        putchar('-');
                        l_intNum = -l_intNum;
                    }

                    numDigits = floor(log10(llabs(l_intNum))) + 1;
                    char* strFromInt = malloc(numDigits);
                    long_long_to_str(l_intNum, strFromInt);
                    fputs(strFromInt, stdout);
                    numCharsPrinted += numDigits - 1;
                }
                //%lli or %lld
                else if (str[i] == 'l') {
                    i++;
                    if (str[i] == 'i' || str[i] == 'd') {
                        int numDigits = 0;
                        ll_intNum = va_arg(vl, long long int);
                        if (ll_intNum == 0)
                            putchar('0');
                        if (ll_intNum < 0)
                        {
                            putchar('-');
                            ll_intNum = -ll_intNum;
                        }

                        numDigits = floor(log10(labs(ll_intNum))) + 1;
                        char* strFromInt = malloc(numDigits);
                        long_long_to_str(ll_intNum, strFromInt);
                        fputs(strFromInt, stdout);
                        numCharsPrinted += numDigits - 1;
                    }
                }
                else {
                    puts("\rERROR: Invalid conversion specifier.");
                    return -1;
                }
            }
            //Precision %f and %Lf
            else if (str[i] == '.') {
                i++;
                if (isdigit(str[i]) || str[i] == '-') {
                    int precision = atoi(&str[i]);
                    if (precision < 0) {
                        print("\rERROR: Invalid conversion specifier \'-\' at character %i of str\n", i + 1);
                        return -1;
                    }
                    while (isdigit(str[i]))
                        i++;
                    //If precision %f is %.nf, print float argument to n decimal places
                    if (str[i] == 'f') {
                        doubleNum = va_arg(vl, double);
                        if (fabs(doubleNum) < 0.000001)
                            doubleNum = va_arg(vl, int);

                        char* strfromPrecision;
                        int len = floor(log10(abs((int) doubleNum))) + 1;
                        if (precision == 0)
                            strfromPrecision = malloc(len);
                        else
                            strfromPrecision = malloc(len + 1 + precision);

                        gcvt(doubleNum, len + precision, strfromPrecision);
                        if ((int) atof(strfromPrecision) == atof(strfromPrecision)) {
                            strcat(strfromPrecision, ".");
                            for (int j = 0; j < precision; j++)
                                strcat(strfromPrecision, "0");
                        }
                        else {
                            for (int j = 0; strlen(strfromPrecision) - len - 1 < precision; j++)
                                strcat(strfromPrecision, "0");
                        }

                        if (strlen(strfromPrecision) > len + 1 + precision) {
                            precisionFloat(strfromPrecision, len, precision, doubleNum);
                        }

                        fputs(strfromPrecision, stdout);
                        numCharsPrinted += strlen(strfromPrecision) - 1;
                        free(strfromPrecision);
                    }
                    //If precision %Lf is %.nLf, print long double argument to n decimal places
                    else if (str[i] == 'L') {
                        i++;
                        if (str[i] == 'f') {
                            l_doubleNum = va_arg(vl, long double);
                            doubleNum = va_arg(vl, double);
                            if (l_doubleNum != doubleNum) {
                                l_doubleNum = doubleNum;
                                if (fabsl(l_doubleNum) < 0.000001)
                                    l_doubleNum = va_arg(vl, int);
                            }

                            char* strfromPrecision;
                            int len = floor(log10(abs((int) doubleNum))) + 1;
                            if (precision == 0)
                                strfromPrecision = malloc(len);
                            else
                                strfromPrecision = malloc(floor(log10(abs(precision))) + 1);

                            gcvt(doubleNum, len + precision, strfromPrecision);
                            if ((int) strtold(strfromPrecision, NULL) == strtold(strfromPrecision, NULL))
                                strcat(strfromPrecision, ".000000");
                            else {
                                for (int j = 0; strlen(strfromPrecision) - len - 1 < precision; j++)
                                    strcat(strfromPrecision, "0");
                            }

                            if (strlen(strfromPrecision) > len + 1 + precision) {
                                precisionFloat(strfromPrecision, len, precision, l_doubleNum);
                            }

                            fputs(strfromPrecision, stdout);
                            numCharsPrinted += strlen(strfromPrecision) - 1;
                            free(strfromPrecision);
                        }
                    }
                }
                //For %.f
                else if (str[i] == 'f') {
                    if (str[i] == 'f') {
                        doubleNum = va_arg(vl, double);
                        if (fabs(doubleNum) < 0.000001)
                            doubleNum = va_arg(vl, int);

                        int roundedDoubleNum = round(doubleNum);
                        char* roundedStr;
                        if (doubleNum == 0)
                            roundedStr = malloc(4);
                        else
                            roundedStr = (char*) malloc(floor(log10(abs(roundedDoubleNum))) + 1);

                        int len = floor(log10(abs((int) doubleNum))) + 1;
                        gcvt(round(doubleNum), len, roundedStr);
                        fputs(roundedStr, stdout);
                        numCharsPrinted += strlen(roundedStr) - 1;
                        free(roundedStr);
                    }
                }
                //For %.Lf
                else if (str[i] == 'L') {
                    i++;
                    if (str[i] == 'f') {
                        l_doubleNum = va_arg(vl, long double);
                        doubleNum = va_arg(vl, double);
                        if (l_doubleNum != doubleNum && doubleNum != 0) {
                            l_doubleNum = doubleNum;
                            if (fabsl(l_doubleNum) < 0.000001)
                                l_doubleNum = va_arg(vl, int);
                        }

                        int roundedDoubleNum = round(l_doubleNum);
                        char* roundedStr;
                        if (l_doubleNum == 0)
                            roundedStr = malloc(4);
                        else
                            roundedStr = (char*) malloc(floor(log10(abs(roundedDoubleNum))) + 1);

                        int len = floor(log10(abs((int) doubleNum))) + 1;
                        gcvt(round(doubleNum), len, roundedStr);
                        fputs(roundedStr, stdout);
                        numCharsPrinted += strlen(roundedStr) - 1;
                        free(roundedStr);
                    }
                }
                else {
                    puts("\rERROR: Invalid conversion specifier.");
                    return -1;
                }
            }
            //For long (long) --- (e.g. long long int, long double)
            else if (str[i] == 'L') {
                i++;
                //%Ld or %Li
                if (str[i] == 'd' || str[i] == 'i') {
                    int numDigits = 0;
                    ll_intNum = va_arg(vl, long long int);
                    if (ll_intNum == 0)
                        putchar('0');
                    if (ll_intNum < 0)
                    {
                        putchar('-');
                        ll_intNum = -ll_intNum;
                    }

                    numDigits = floor(log10(labs(ll_intNum))) + 1;
                    char* strFromInt = malloc(numDigits);
                    long_long_to_str(ll_intNum, strFromInt);
                    fputs(strFromInt, stdout);
                    numCharsPrinted += numDigits - 1;
                }
                //%Lf
                else if (str[i] == 'f') {
                    l_doubleNum = va_arg(vl, long double);
                    doubleNum = va_arg(vl, double);
                    if (l_doubleNum != doubleNum) {
                        l_doubleNum = doubleNum;
                        if (fabsl(l_doubleNum) < 0.000001)
                            l_doubleNum = va_arg(vl, int);
                    }

                    int integerPartOfDecimal = (int) l_doubleNum;
                    char* decimalAsStr;
                    if (integerPartOfDecimal == 0)
                        decimalAsStr = malloc(8);
                    else
                        decimalAsStr = malloc(floor(log10(abs(integerPartOfDecimal))) + 51);

                    int len = floor(log10(abs((int) l_doubleNum))) + 1;
                    gcvt(l_doubleNum, len + 6, decimalAsStr);
                    if ((int) atof(decimalAsStr) == atof(decimalAsStr))
                        strcat(decimalAsStr, ".000000");
                    else {
                        int addLength = strlen(decimalAsStr);
                        for (int j = 0; j + addLength < 7 + len; j++)
                            strcat(decimalAsStr, "0");
                    }
                    cutOffExcessDecimalDigits(decimalAsStr, len);
                    fputs(decimalAsStr, stdout);
                    numCharsPrinted += strlen(decimalAsStr) - 1;
                    free(decimalAsStr);
                }
                else {
                    puts("\rERROR: Invalid conversion specifier.");
                    return -1;
                }
            }
            //%u
            else if (str[i] == 'u') {
                unsigned int unsignedIntNum;
                unsignedIntNum = va_arg(vl, unsigned int);
                int len = floor(log10(unsignedIntNum)) + 1;
                char* unsignedIntToStr = malloc(len);
                gcvt(unsignedIntNum, len, unsignedIntToStr);
                fputs(unsignedIntToStr, stdout);
                numCharsPrinted += strlen(unsignedIntToStr) - 1;
                free(unsignedIntToStr);
            }
            //%%
            else if (str[i] == '%')
                putchar('%');
            //Invalid conversion specification
            else {
                puts("\rERROR: Invalid conversion specifier.");
                return -1;
            }
        }
        else
            putchar(str[i]);

        numCharsPrinted++;
    }
    va_end(vl);
    return numCharsPrinted;
}

void precisionFloat(char* strfromPrecision, int lengthOfIntegerPart, int precision, long double doubleNum) {
    int j = lengthOfIntegerPart + precision + 1;
    if (strfromPrecision[j] >= '5') {
        if (precision <= 6) {
            if (precision == 0)
                gcvt((int) doubleNum, lengthOfIntegerPart, strfromPrecision);
            else {
                int n = 1;
                strfromPrecision[j] = '0';
                while (strfromPrecision[j - n] == '9') {
                    strfromPrecision[j - n] = '0';
                    strfromPrecision[j - n - 1]++;
                    n++;
                }
                strfromPrecision[j - n]++;
            }
        }
        else {
            for (int a = 0; a < precision - 6; a++)
                strcat(strfromPrecision, "0");
        }
    }
    char* newStr = malloc(lengthOfIntegerPart + 1 + precision);
    strncat(newStr, strfromPrecision, lengthOfIntegerPart + precision + 1 * (precision != 0));
    strfromPrecision = newStr;
}

void cutOffExcessDecimalDigits(char* decimalAsStr, int len) {
    if (strlen(decimalAsStr) > 7 + len) {
        int j = 7 + len;
        if (decimalAsStr[j] >= '5') {
            if (decimalAsStr[j] == '9') {
                int n = j - 1;
                decimalAsStr[j] = '0';
                while (decimalAsStr[n] == '9') {
                    decimalAsStr[n]++;
                    n--;
                }
            }
            else {
                decimalAsStr[j]++;
            }
        }
    }
}

char* long_long_to_str(long long int num, char* buffer) {
    int len = floor(log10(llabs(num))) + 1;
    for (int i = len - 1; i >= 0; i--) {
        buffer[i] = (num % 10) + '0';
        num /= 10;
    }
    return buffer;
}
