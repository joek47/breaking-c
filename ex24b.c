#include <stdio.h>
#include <stdlib.h>
#include "dbg.h"

#define MAX_DATA 10
int main(int argc, char *argv[])
{

    char first[MAX_DATA];
    char last[MAX_DATA];

    printf("Enter first name: ");
    scanf("%[^\n]s ", first);
    // scanf("%s[^\n]", first);

    printf("Enter last name: ");
    // both doesn't work?
    // scanf("%[^\n]s", last);
    // scanf("%s[^\n]", last);
    scanf("%s", last);

    printf("Full name is %s %s\n", first, last);
}

/* Instead, you will want scanf to read only the visible characters, skipping white space 
 * (including the newline) as it does for numeric data. The secret to getting scanf to 
 * perform this way is to put a blank in the format string before the %c format specifier. 
 */
