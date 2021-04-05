#define _GNU_SOURCE
#include <stdio.h>
#include <cs50.h>
#include "additionalFuncs.h"   //For some additional logarithm functions
#include "manipulateStr.h"     //Used to check and manipulate input string

#define ARRAY_SIZE 9
#define GOLDEN_RT 1.6180339887498       //Golden Ration ((1 + sqrt(5)) / 2)
#define APERY_CONST 1.202056903159      //Apery's Constant (1 + 1/2^3 + 1/3^3 + 1/4^3 + 1/5^3 + ...)
#define M_SQRT_3 1.73205080757          //Theodorus' Constant (sqrt(3))
#define G 0.9159655941                  //Catalan's Constant (1 - 1/3^2 + 1/5^2 - ...)
#define DELIAN_CONST 1.25992104         //Delian's Constant (cbrt(2))
#define HERMITE_CONST 1.1547005         //Hermite's Constant (2 / sqrt(3) OR 1/cos(PI / 6))
#define GELFOND_CONST 23.1406926327     //Gelfond's Constant (e ^ PI)

//Used to solve equation
double solveEquation(char* input);
//Get the first number and number of operations
double convertFloat(char* input, double total);
unsigned int numberOfOperations(char* input);
//String char checking
unsigned int validNext(char c);
unsigned int validateOperation(char c);
unsigned int validateRoot(char c);
//GCD
double calculateGCD(double a, double b);
//Change strings
void removeChar(char* input, int index, int c);
void assignRootOperations(char* rootOperations, int numNum, char* copy, int i, char state);
void setUp(char* copy);
void copyStr(char* destination, char* source);
void formatInput(char* input);
//Root and trig and related functions
float squareRoot(float number);     //square root
float fifthRoot(float number);      //fifth root
float seventhRoot(float number);    //seventh root
float sinc(float number);           //sine cardinal (sinc)
float sec(float number);            //secant
float cot(float number);            //cotangent
float cosec(float number);          //cosecant
