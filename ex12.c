#include <stdio.h>

int main(int argc, char *argv[]){
    
    int areas[] = {10, 12, 13, 14, 20};
    char full_name[] = {
        'H', 'e', 'l', 'l', ' ', 
        'H', 'e', 'l', 'l', ' ', 
        'W', '.', 'o', 'r', 'l', 'd'
        // '\0'
    };

    char name[] = "Hello";
    areas[0] = 100;
    name[0] = 'A';
    full_name[0] = 'A';

    printf("The size of an int: %ld\n", sizeof(int));
    // printf("The size of an int: %u\n", sizeof(int));     // no difference
    printf("The size of areas (int[]): %ld\n", sizeof(areas));
    printf("The number of ints in areas: %ld \n", sizeof(areas)/sizeof(int));
    // printf("The first area is %d, the 2nd %d.\n", areas[0], areas[1]);
    printf("The first area is %d, the 2nd %d.\n", areas[0], areas[10]);     // integers not little endian

    printf("The size of char: %ld\n", sizeof(char));
    printf("The size of name (char[]): %ld\n", sizeof(name));
    printf("The number of chars: %ld \n", sizeof(name)/sizeof(char));

    printf("The size of full name (char[]): %ld\n", sizeof(full_name));
    printf("The number of chars: %ld \n", sizeof(full_name)/sizeof(char));

    printf("The name is \"%s\" and the full name is \"%s\"\n", name, full_name);    // stored in big endian

    return 0;

}
