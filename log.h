#define E 2.7182818284590452353602874713527
#include <math.h>

int main(void);

double log1(float number)
{
    if (number < 1)
        return -INFINITY;
    else if (number > 1)
        return INFINITY;
    else
        return NAN;
}

double log3(float number)
{
    return log10(number) / log10(3);
}

double log4(float number)
{
    return log10(number) / log10(4);
}

double log5(float number)
{
    return log10(number) / log10(5);
}

double log6(float number)
{
    return log10(number) / log10(6);
}

double log7(float number)
{
    return log10(number) / log10(7);
}

double log8(float number)
{
    return log10(number) / log10(8);
}

double log9(float number)
{
    return log10(number) / log10(9);
}

double ln(double number)
{
    return log10(number) / log10(E);
}
