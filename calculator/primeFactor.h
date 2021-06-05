#include <math.h>
#include <stdlib.h>

//Checks if number is prime number
int isPrime(int num)
{
    int i;
    if (num % 2 == 0)
        return 1;
    if (num % 3 == 0)
        return 1;

    for (i = 1; 6 * i - 1 <= (int) sqrt(num); i++)
    {
        if (num % (6 * i - 1) == 0)
            return 1;
    }
    for (i = 1; 6 * i + 1 <= (int) sqrt(num); i++)
    {
        if (num % (6 * i + 1) == 0)
            return 1;
    }
    return 0;
}

//Gets number of prime factors in a number
int getNumberOfPrimeFactors(int num)
{
    if (isPrime(num) == 0)
        return 1;
    int i = 1;
    int primeFactorNumber = 0;
    if (num % 2 == 0)
        primeFactorNumber++;
    if (num % 3 == 0)
        primeFactorNumber++;

    int test;

    for (i = 1; 6 * i - 1 <= (int) num / 2; i++)
    {
        test = 6 * i - 1;
        if (num % (6 * i - 1) == 0 && isPrime(6 * i - 1) == 0)
            primeFactorNumber++;
    }
    for (i = 1; 6 * i + 1 <= (int) num / 2; i++)
    {
        test = 6 * i + 1;
        if (num % (6 * i + 1) == 0 && isPrime(6 * i + 1) == 0)
            primeFactorNumber++;
    }
    return primeFactorNumber;
}

//Gets the prime factors
int* getPrimeFactors(int num)
{
    int i = 1;
    int index = 0;
    int numberOfPrimeFactors = getNumberOfPrimeFactors(num);
    int* primeFactors = (int*) malloc(4 * numberOfPrimeFactors);
    if (num % 2 == 0)
    {
        primeFactors[index] = 2;
        index++;
    }
    if (num % 3 == 0)
    {
        primeFactors[index] = 3;
        index++;
    }
    for (i = 1; 6 * i - 1 <= (int) num / 2; i++)
    {
        if (num % (6 * i - 1) == 0 && isPrime(6 * i - 1) == 0)
        {
            primeFactors[index] = 6 * i - 1;
            index++;
        }
    }
    for (i = 1; 6 * i + 1 <= (int) num / 2; i++)
    {
        if (num % (6 * i + 1) == 0 && isPrime(6 * i + 1) == 0)
        {
            primeFactors[index] = 6 * i + 1;
            index++;
        }
    }
    return primeFactors;
}

//Gets the exponents of the prime factors
int* getPrimeFactorExponents(int num)
{
    int numberOfPrimeFactors = getNumberOfPrimeFactors(num);
    int primeFactorIndex = 0;
    int n = num;
    int* primeFactors = malloc(4 * numberOfPrimeFactors);
    primeFactors = getPrimeFactors(num);
    int* primeFactorsAndExponents = (int*) malloc(4 * numberOfPrimeFactors);
    for (int i = 0; i < numberOfPrimeFactors; i++)
    {
        while (n % primeFactors[i] == 0)
        {
            primeFactorsAndExponents[i]++;
            n /= primeFactors[i];
        }
    }
    return primeFactorsAndExponents;
}
