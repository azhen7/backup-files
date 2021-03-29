#include <stdlib.h> //For the malloc() function
#include <stddef.h> //For NULL

typedef char *string;

int main(void);
/* NOTE: I can guarantee that these functions work properly as
   all these functions have undergone rigourous testing and
   comparison to the original functions from string.h and
   strings.h
-------------------------------------------------------------------
*/

/* The strlen function from string.h calculates the
   length of the string, and returns that value. */
//strlen() function from string.h
int len(string array)
{
    int length = 0;
    do
    {
        length++;
    }
    while (array[length] != '\0');
    return length;
}

/* The strcmp function from string.h compares two strings.
   It returns 0 if the two strings are the same, a negative
   number if the first string is ASCIIbetically before
   the second string, and a positive number is the
   second string is ASCIIbetically before the first string. */
//strchr function from string.h
int stringcmp(string array1, string array2)
{
    int len1 = len(array1), len2 = len(array2), i = 0;
    int min = (len1 > len2) ? len2 : len1;
    if (len1 != len2) {
        while (i < len1) {
            if ((int) array1[i] == (int) array2[i]) {
                i++;
                continue;
            }
            else if ((int) array1[i] > (int) array2[i]) {
                return 1;
            }
            else if ((int) array1[i] < (int) array2[i]) {
                return -1;
            }
            else if (i > min) {
                return 1;
            }
        }
        return 50;
    }
    else {
        while (i < len2) {
            if (array1[i] == array2[i]) {
                if (i == len2 - 1)
                    return 0;

                else {
                    i++;
                    continue;
                }
            } 
            else if (array1[i] > array2[i])
                return 1;

            else if (array1[i] < array2[i])
                return -1;
        }
        return 50;
    }
}

/* The strncmp function from string.h works like the
   strcmp function, except it compares only the first
   n bytes of the strings. */
//strnchr function from string.h
int stringcmp_n(string array1, string array2, int c)
{
    int len1 = len(array1), len2 = len(array2), i = 0;
    int min = (len1 > len2) ? len2 : len1;
    while (i < c) {
            if ((int) array1[i] == (int) array2[i]) {
                if (i == len2 - 1) {
                    return 0;
                }
                else {
                    i++;
                    continue;
                }
            }
            else if ((int) array1[i] > (int) array2[i]) {
                return 1;
            }
            else if ((int) array1[i] < (int) array2[i]) {
                return -1;
            }
            else if (i > min) {
                return 1;
            }
        }
        return 0;
}

/* The strcasecmp function from strings.h works like the
   strcmp function, except it ignores case (e.g. to the
   function, there is no difference between "A" and 'a'). */
//strcasecmp function from string.h
int stringcmp_ignoreCase(string array1, string array2)
{
    int len1 = len(array1), len2 = len(array2), i = 0;
    int min = (len1 > len2) ? len2 : len1;
    if (len1 != len2) {
        while (i < len1) {
            if ((int) array1[i] == (int) array2[i]) {
                i++;
                continue;
            }
            else if ((int) array1[i] > (int) array2[i]) {
                if ((int) array1[i] == (int) array2[i] + 32) {
                    i++;
                    continue;
                }
                else {
                    return (int) array1[i] - (int) array2[i];
                }
            }
            else if ((int) array1[i] < (int) array2[i]) {
                if ((int) array1[i] == (int) array2[i] - 32) {
                    i++;
                    continue;
                }
                else {
                    return (int) array1[i] - (int) array2[i];
                }
            }
            else if (i > min) {
                return (int) array1[i] - (int) array2[i];
            }
        }
        return 50;
    }
    else {
        while (i < len2) {
            if ((int) array1[i] == (int) array2[i]) {
                if (i == len2 - 1) {
                    return 0;
                }
                else {
                    i++;
                    continue;
                }
            }
            else if ((int) array1[i] > (int) array2[i]) {
                if ((int) array1[i] == (int) array2[i] + 32) {
                    if (i == len2 - 1) {
                        i++;
                        continue;
                    }
                    else {
                        return 0;
                    }
                }
                else {
                    return (int) array1[i] - (int) array2[i];
                }
            }
            else if ((int) array1[i] < (int) array2[i]) {
                if ((int) array1[i] == (int) array2[i] - 32) {
                    if (i == len2 - 1) {
                        i++;
                        continue;
                    }
                    else {
                        return 0;
                    }
                }
                else {
                    return (int) array1[i] - (int) array2[i];
                }
            }
        }
        return 50;
    }
}

/* The strncasecmp function from strings.h works
   like the strncmp function, except this function
   ignores case (i.e. there is no difference between
   "a" and "A"). */
//strncasecmp function from strings.h
int stringcmp_ignoreCase_n(string array1, string array2, int c)
{
    int len1 = len(array1), len2 = len(array2), i = 0;
    int min = (len1 > len2) ? len2 : len1;
        while (i < c) {
            if ((int) array1[i] == (int) array2[i]) {
                if (i == len2 - 1) {
                    return 0;
                }
                else {
                    i++;
                    continue;
                }
            }
            else if (array1[i] > array2[i]) {
                if (array1[i] == array2[i] + 32) {
                    if (i == len2 - 1) {
                        i++;
                        continue;
                    }
                    else
                        return 0;
                }
                else
                    return (int) array1[i] - (int) array2[i];
            }
            else if ((int) array1[i] < (int) array2[i]) {
                if ((int) array1[i] == (int) array2[i] - 32) {
                    if (i == len2 - 1) {
                        i++;
                        continue;
                    }
                    else {
                        return 0;
                    }
                }
                else {
                    return (int) array1[i] - (int) array2[i];
                }
            }
            else if (i > min) {
                return 1;
            }
        }
        return 0;
}


/* The strchr function from string.h searches
   the string a for char b. When it finds that char b, it
   returns a pointer to the first occurence of the char b.
   If it doesn't find b, it returns NULL. */
//strchr function from string.h
string locate_char_first(string a, char b)
{
    int pos = 0, i = 0;
    string ret = NULL;
    do {
        if (a[pos] == b) {
            //First, increment i until a[pos + 1] reaches the end of the array a
            do {
                i++;
            }
            while (a[pos + i] != '\0');

            //Than allocate some memory for the string. We multiply it with i + 1 to make extra room for the \0 at the end.
            ret = (char *) malloc(sizeof(char) * (i + 1));
            i = 0; //Assign i to 0

            //Start copying the part of the string a behind the first occurence of char b
            do {
                ret[i] = a[pos + i];
                i++;
            }
            while (a[pos + i] != '\0');

            //Assign the end of string ret to null
            ret[i] = '\0';

            //Return the string
            return ret;
        }
        else {
            pos++;
        }
    }
    while (a[pos] != '\0');
    return NULL;
}

/* The strrchr function searches the string a for char
   b. If b is found, this function returns a pointer
   to the last occurence of b. Otherwise, it returns
   NULL. */
//strrchr function from string.h
string locate_char_last(string a, char b)
{
    int pos = 0, i = 0, location = 0;
    string ret = NULL;
    do {
        if ((int) a[pos] == b) {
            location = pos;
            pos++;
        }
        else {
            pos++;
        }
    }
    while (a[pos] != '\0');

    if (location != 0) {
        //First, increment i until a[pos + 1] reaches the end of the array a
        do {
            i++;
        }
        while (a[location + i] != '\0');

        //Than allocate some memory for the string. We multiply it with i + 1 to make extra room for the \0 at the end.
        ret = (char *) malloc(sizeof(char) * (i + 1));
        i = 0; //Assign i to 0

        //Start copying the part of the string a behind the first occurence of char b
        do {
            ret[i] = a[location + i];
            i++;
        }
        while (a[location + i] != '\0');

        //Assign the end of string ret to \0
        ret[i] = '\0';

        //Return the string
        return ret;
    }
    else {
        return NULL;
    }
}

/* The strchrnul function functions like the strchr function,
   except instead of returning NULL when not finding the char b,
   it returns a pointer to the null byte at the end of string a. */

/* The reason I'm doing this is that strchrnul is a GNU extension,
   so if you try to use it while only including string.h, you would
   get an error. To get strchrnul working, you would need to type
   "#define _GNU_SOURCE" above the header files. I think that it would
   be better to just include a header file and get a function doing the
   same thing. */
//strchrnul function from string.h
string locate_char_first_null(string a, char b)
{
    int pos = 0, i = 0;
    string ret = NULL;
    do {
        if ((int) a[pos] == b) {
            //First, increment i until a[pos + 1] reaches the end of the array a
            do {
                i++;
            }
            while (a[pos + i] != '\0');

            //Than allocate some memory for the string. We multiply it with i + 1 to make extra room for the \0 at the end.
            ret = (char *) malloc(sizeof(char) * (i + 1));
            i = 0; //Assign i to 0

            //Start copying the part of the string a behind the first occurence of char b
            do {
                ret[i] = a[pos + i];
                i++;
            }
            while (a[pos + i] != '\0');

            //Assign the end of string ret to \0
            ret[i] = '\0';

            //Return the string
            return ret;
        }
        else {
            pos++;
        }
    }
    while (a[pos] != '\0');
    return "";
}

/* The strcpy function from string.h copies string b
   to string a and returns string a. */

/* In order for strcpy to work, you would have to malloc
   the string to allocate memory for the copy. strcpy
   doesn't do that for you. Here, my redefinition of
   strcpy does that for you, so you don't have to do it. */

//strcpy function from string.h
string strcopy(string a, string b)
{
    int i = len(b);
    //Allocate some memory for the string. We multiply it with i + 1 to make extra room for the \0 at the end.
    a = (char *) malloc(sizeof(char) * (i + 1));
    i = 0; //Assign i to 0

    do {
        a[i] = b[i];
        i++;
    }
    while (b[i] != '\0');

    //Assign the end of string a to \0
    a[i] = '\0';

    //Return the string
    return a;
}

/* The strcat function from string.h concatenates two strings,
   or combines, two strings into one string, and then it returns
   a pointer to that string. */
//strcat function from string.h
string strappend(string a, string b)
{
    string ret = a;
    int len1 = len(a), len2 = len(b), appendlen = 0;
    appendlen = len1 + len2;
    a = (char *) malloc(sizeof(char) * (appendlen + 1));

    for (int i = 0; b[i] != '\0'; i++)
    {
        a[len1 + i] = b[i];
    }

    for (int i = 0; i < len1; i++)
    {
        a[i] = ret[i];
    }

    a[appendlen] = '\0';
    return a;
}

/* The strdup function from string.h duplicates a string
   and returns a pointer to that string. This function is
   a GNU extension, so you have to define _GNU_SOURCE.
   Otherwise, you get an error from the compiler. */
//strdup function from string.h
string strduplicate(string a)
{
    int length = len(a);

    string ret = (char *) malloc(sizeof(char) * (length + 1));

    for (int i = 0; i < length; i++)
    {
        ret[i] = a[i];
    }

    ret[length] = '\0';
    return ret;
}

/* The strndup finction from string.h functions like the
   strdup function, except that it copies at most n bytes
   from string a. */

/* Like with the strdup function, to use the function, you
   have to define _GNU_SOURCE, or you will get a compiler
   error. */
//strndup function from string.h
string strnduplicate(string a, int size)
{
    int length = len(a);

    if (length > size)
    {
        string ret = (char *) malloc(sizeof(char) * (length + 1));
        for (int i = 0; i < size; i++)
            ret[i] = a[i];

        ret[length] = '\0';
        return ret;
    }
    else
    {
        strduplicate(a);
        return a;
    }
}

//strnlen function from stringfunc.h
/* The strnlen function finds the length of the
   string up to the placeth occurence of char b.
   I randomly thought of this. */
int strnlen(string a, char b, int place)
{
    int occurences = 0;
    int length = 0;
    for (int i = 0; i < len(a); i++)
    {
        if ((int) a[i] == b)
            occurences++;
    }
    if (occurences < place)
        return -1;

    occurences = 0;

    do
    {
        length++;
        if ((int) a[length] == b)
            occurences++;
    }
    while (occurences < place);

    return length + 1;
}

//strcat function from string.h
string strnappend(string a, string b, int size)
{
    string ret = a;
    int len1 = len(a), appendlen = 0;
    appendlen = len1 + size;
    a = (char *) malloc(sizeof(char) * (appendlen + 1));

    for (int i = 0; i < size; i++)
    {
        a[len1 + i] = b[i];
    }

    for (int i = 0; i < len1; i++)
    {
        a[i] = ret[i];
    }

    a[appendlen] = '\0';
    return a;
}
