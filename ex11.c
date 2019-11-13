#include <stdio.h>

int main(int argc, char *argv[]){

    int numbers[4] = {0};
    // char name[4] = {'a'};
    char name[4] = {'a', 'a', 'a', 'a'};
    // char *name = "aaaa";    //seg fault at line 26. Can't perform array index set values on pointers?
    //shortcut in C
    printf("numbers %d %d %d %d\n", numbers[0], numbers[1], numbers[2], numbers[3]);
    // does not display \0  in name[1-3]
    printf("name each %c %c %c %c\n", name[0], name[1], name[2], name[3]);
    printf("name: %s\n", name);

    //set up
    numbers[0] = 1;
    numbers[1] = 2;
    numbers[2] = 3;
    numbers[3] = 4;
    name[0] = 'S';
    name[1] = 'u';
    name[2] = 'n';
    // name[3] = '\0';
    name[3] = 'S';

    /*
    // reverse
    numbers[0] = 'S';
    numbers[1] = 'u';
    numbers[2] = 'n';
    numbers[3] = '\0';  //int 0 is the same as character '\0'
    name[0] = 97;
    name[1] = 98;
    name[2] = 99;
    // name[3] = '\0';
    name[3] = 0;
    */
 
    printf("numbers %d %d %d %d\n", numbers[0], numbers[1], numbers[2], numbers[3]);
    printf("name each %c %c %c %c\n", name[0], name[1], name[2], name[3]);
    printf("name: %s\n", name);

    // * is like []. another points to an address
    char *another = "Sun";  //seg fault if use single quotes ''
    printf("another: %s\n", another);
    printf("another each %c %c %c %c\n", another[0], another[1], another[2], another[3]);

    return 0;

}
