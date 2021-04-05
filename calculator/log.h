#include <math.h>

int main(void);

//Log functions
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
    return log10(number) / log10(M_E);
}

//Root and trig and related functions functions
//Square root function
float squareRoot(float number)
{
    if (number < 0)
        return NAN;
    return sqrt(number);
}
//Fifth root function
float fifthRoot(float number)
{
    if (number < 0)
        return pow(fabsf(number), 0.2) * -1;
    return pow(number, 0.2);
}
//Seventh root function
float seventhRoot(float number)
{
    if (number < 0)
        return pow(fabsf(number), 1 / 7) * -1;
    return pow(number, 1 / 7);
}
//sinc function
float sinc(float number)
{
    if (number == 0)
        return 1;
    return sin(number) / number;
}
//secant fucntion
float sec(float number)
{
    return 1 / cos(number);
}
//cotangent function
float cot(float number)
{
    return 1 / tan(number);
}
//cosecant function
float cosec(float number)
{
    return 1 / sin(number);
}
