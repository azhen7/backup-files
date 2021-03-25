#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>

char* getTime(void);
char* generateNewTime(char* input);
int kbhit(void);

int main(void)
{
    char* lapTrack[20];
    char* time;
    char t;
    unsigned int index = 0;
    int choice = 0;

    system("clear");
    time = getTime();
    printf("%s\n", time);

    while (1)
    {
        sleep(1);
        system("clear");
        generateNewTime(time);
        printf("%s\n", time);
        if (kbhit())
        {
            t = fgetc(stdin);
            lapTrack[index] = time;

            if (t == 10)
                break;
            else
                printf("Lap registered: %s\n", lapTrack[index]);

            if (index == 20)
                printf("No more laps allowed\n");

            index++;
        }
    }
    if (index == 0)
    {
        printf("0 laps registered\n");
        return 0;
    }
    if (index == 1)
    {
        printf("1 lap registered: %s\n", lapTrack[0]);
        return 0;
    }

    printf("%i laps registered\n", index);

    do
    {
        choice = get_int("Lap: ");
        if (choice >= index)
        {
            printf("Lap choice out of max index\n");
            return 0;
        }
        printf("Lap %i: %s\n", choice, lapTrack[choice - 1]);
    }
    while (choice > 0);
}

char* getTime(void)
{
    int hours = atoi(__TIME__);
    char* append = strchr(__TIME__, ':');
    hours -= 4;
    if (hours < 0)
       hours = 24 + hours;

    char* ret = (char*) malloc(10);
    sprintf(ret, "%i%s", hours, append);
    return ret;
}

char* generateNewTime(char* input)
{
    char* buffer = (char*) malloc(8);

    int hours = atoi(input);
    int minutes;
    int seconds;

    minutes = (input[strlen(input) - 5] - '0') * 10 + (input[strlen(input) - 4] - '0');
    seconds = (input[strlen(input) - 2] - '0') * 10 + (input[strlen(input) - 1] - '0');

    seconds++;
    if (seconds >= 60)
    {
        minutes++;
        seconds %= 60;
    }
    if (minutes >= 60)
    {
        hours++;
        minutes %= 60;
    }
    if (hours >= 24)
        hours = 0;

    char* appendMin = (char*) malloc(2);
    char* appendSec = (char*) malloc(2);

    sprintf(appendMin, "%i:", minutes);
    sprintf(appendSec, "%i", seconds);

    if (hours < 9)
        strcat(buffer, "0");
    sprintf(buffer, "%i:", hours);

    if (minutes < 10)
        strcat(buffer, "0");
    strcat(buffer, appendMin);

    if (seconds < 10)
        strcat(buffer, "0");
    strcat(buffer, appendSec);

    strcpy(input, buffer);
    return input;
}

int kbhit(void)
{
    struct termios oldt, newt;
    int ch, oldf;

    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);

    ch = getchar();

    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);

    if (ch != EOF)
    {
        ungetc(ch, stdin);
        return 1;
    }
    return 0;
}
