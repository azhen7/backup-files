#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char* addTime(char* starting, int add, char* halfOfDay);
char* addTime_french(char* starting, int add, char* halfOfDay);
int validate_startTime(char* input);
int convertMinutes(char* input);

int main(void)
{
    char* startTime = NULL;
    char* whichHalfofDay = NULL;
    char* finalTime = NULL;
    char* finalTime_f = NULL;
    int add = 0;
    int hours;
    int minutes;

    while (1)
    {
        startTime = get_string("Start time: ");

        if (validate_startTime(startTime) == 0)
        {
            do
            {
                whichHalfofDay = get_string("Which half of day: ");
            }
            while (strcmp(whichHalfofDay, "PM") != 0 && strcmp(whichHalfofDay, "AM") != 0);

            add = get_int("Add time (minutes): ");

            finalTime = addTime(startTime, add, whichHalfofDay);
            finalTime_f = addTime_french(startTime, add, whichHalfofDay);

            printf("Input converted to hours and minutes: %i h %i min\n", add / 60, add % 60);

            printf("New time: %s\n", finalTime);
            printf("French time: %s\n", finalTime_f);
            putchar('\n');
        }
        else
            printf("Invalid start time.\n\n");
    }
}

int validate_startTime(char* input)
{
    unsigned short colonNumber = 0;
    for (int i = 0; i < strlen(input); i++)
    {
        if (!isdigit(input[i]))
        {
            if (input[i] == 58)
            {
                colonNumber++;
                if (colonNumber > 1)
                    return 1;
            }
            else
                return 1;
        }
    }
    int checkHour = atoi(input);
    if (checkHour > 12)
        return 1;

    int checkMinute = convertMinutes(input);
    if (checkMinute > 59)
        return 1;

    if (checkHour > 9)
        return 1 * (strlen(input) < 5);
    else
        return 1 * (strlen(input) < 4);
}

char* addTime(char* starting, int add, char* halfOfDay)
{
    char* halfDay = (char*) malloc(2);
    strcpy(halfDay, halfOfDay);

    int numberOfDaysLater = 0;

    int minutes = convertMinutes(starting);
    int hours = atoi(starting);

    hours += 12 * (strcmp(halfOfDay, "AM") != 0);

    int addHours = add / 60;
    int addMinutes = add % 60;

    char* appendLatter = (char*) malloc(10);

    char* finalTime = (char*) malloc(7 * sizeof(char));

    minutes += addMinutes;
    hours += addHours;

    if (hours > 23)
    {
        hours %= 24;
        strcpy(halfDay, "AM");
    }

    if (minutes > 59)
    {
        hours += (minutes / 60);
        minutes %= 60;
    }

    if (hours > 12)
    {
        hours -= 12;
        if (add >= (720 - addMinutes - add))
        {
            if (strcmp(halfDay, "AM") == 0)
                strcpy(halfDay, "PM");
            else
                strcpy(halfDay, "AM");
        }
    }

    numberOfDaysLater = add / 1440;

    sprintf(finalTime, "%i:", hours);

    if (minutes % 10 == minutes)
        strcat(finalTime, "0");

    sprintf(appendLatter, "%i %s %i day(s) later", minutes, halfDay, numberOfDaysLater);
    strcat(finalTime, appendLatter);

    return finalTime;
}

char* addTime_french(char* starting, int add, char* halfOfDay)
{
    int minutes = convertMinutes(starting);
    int hours = atoi(starting);

    hours += 12 * (strcmp(halfOfDay, "AM") != 0);

    int addHours = add / 60;
    int addMinutes = add % 60;

    char* appendMinutes = (char*) malloc(2);

    char* finalTime = (char*) malloc(7 * sizeof(char));

    minutes += addMinutes;
    hours += addHours;

    if (minutes > 59)
    {
        hours += (minutes / 60);
        minutes %= 60;
    }

    if (hours > 23)
        hours %= 24;

    sprintf(finalTime, "%ih ", hours);

    if (minutes % 10 == minutes)
        strcat(finalTime, "0");

    sprintf(appendMinutes, "%i", minutes);
    strcat(finalTime, appendMinutes);

    return finalTime;
}

int convertMinutes(char* input)
{
    int minutes = 0;
    char* stringWithColon = strchr(input, ':');

    for (int i = 1, len = strlen(stringWithColon); i < len; i++)
    {
        minutes += stringWithColon[i] - '0';
        if (i != len - 1)
            minutes *= 10;
    }

    return minutes;
}
