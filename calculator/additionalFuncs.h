#include <math.h>

int main(void);

//log function
double log_base(float number, float base)
{
    return log10(number) / log10(base);
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
//GCD
double calculateGCD(double a, double b)
{
    double temp = 0;
    if (a < b)
    {
        temp = a;
        a = b;
        b = temp;
    }
    while (b != 0)
    {
        temp = b;
        b = fmod(a, b);
        a = temp;
    }
    return a;
}
//iterative log
unsigned int iterative_log(double a, double base)
{
    unsigned int iterateCount = 0;
    while (a > 1)
    {
        iterateCount++;
        a = log_base(a, base);
    }
    return iterateCount;
}
