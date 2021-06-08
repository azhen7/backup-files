#include <math.h>

int main(void);

//log function
double log_base(float number, float base)
{
    return log10(number) / log10(base);
}
//Function which compares two elements
int cmpfunc (const void * a, const void * b) {
   return (* (int*) a - * (int*) b );
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
int iterative_log(double a, double base)
{
    if (base < 1.444667 || a <= 1)
        return -1;
    unsigned int iterateCount = 0;
    while (a > 1)
    {
        iterateCount++;
        a = log_base(a, base);
    }
    return iterateCount;
}
