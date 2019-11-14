#include <stdio.h>
#include <ctype.h>
#include <string.h>

// forward declaration
int can_print_it (char ch); 

void print_letters(char arg[])
{
    int i = 0;
    for (i = 0; arg[i] != '\0'; i++){
        char ch = arg[i];

        if (can_print_it(ch)) {
            printf("'%c' == %d ", ch, ch);
        }
    }

    printf("\n");
}

// with strlen argument
void print_letters2(char arg[], int len)
{
    int i = 0;
    for (i = 0; i < len; i++){
        char ch = arg[i];

        if (can_print_it(ch)) {
            printf("'%c' == %d ", ch, ch);
        }
    }

    printf("\n");
}

int can_print_it (char ch)
{
    return isdigit(ch) || isalpha(ch) || isblank(ch);
}

void print_arguments(int argc, char *argv[])
{
    int i = 0;

    for (i = 0; i < argc; i++){
        // print_letters(argv[i]);
        print_letters2(argv[i], strlen(argv[i]));
    }
}

int main(int argc, char *argv[])
{
    print_arguments(argc, argv);
    // print_arguments(argc + 1, argv);

    return 0;
}
