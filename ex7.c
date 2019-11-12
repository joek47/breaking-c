#include <stdio.h>

int main(int argc, char *argv[]){

    int distance = 100;
    float power = 2.345f;
    double super_power = 5678.4321;

    char initial = 'A';

    char first_name[] = "Jjj";
    char last_name[] = "Lll";

    printf("You are %d km away.\n", distance);
    printf("You are %f levels of power.\n", power);
    printf("You are %f awesome superpowers.\n", super_power);
    printf("My initial is %c.\n", initial);
    printf("My first name is %s.\n", first_name);
    printf("My first name is %s.\n", last_name);
    printf("My full name is %s %c. %s.\n", first_name, initial, last_name);

    int bugs = 100;
    double bug_rate = 1.2;

    printf("You have %d bugs at rate of %f.\n", bugs, bug_rate);

    // long universe_of_defects = 1L * 1024L * 1024L * 1024L;
    long universe_of_defects = 1L * 1024L ^ 1024L ^ 1024L ^ 1000000024L;
    // printf("The entire universe has %ld bugs.\n", universe_of_defects);
    printf("The entire universe has %lu bugs.\n", universe_of_defects);

    double expected_bugs = bugs * bug_rate;
    printf("You are expected to have %f bugs.\n", expected_bugs);

    double part_of_universe = expected_bugs / universe_of_defects;
    printf("That's only a %e portion of the universe.\n", part_of_universe);

    //makes no sense
    char nul_byte = '\0';
    printf("Null byte is %s %c. \n", nul_byte, nul_byte);
    // https://stackoverflow.com/questions/33279071/passsing-null-byte-via-format-specifier-in-printf/33279219
    // Null byte is (null) . 
    //  warning: format ‘%s’ expects argument of type ‘char *’, but argument 2 has type ‘int’ [-Wformat=]

    int care_percentage = bugs * nul_byte;
    printf("Which means you should care %d%%.\n", care_percentage);

    return 0;

}
