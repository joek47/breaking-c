#include <stdio.h>

int main(int argc, char *argv[]){

    int i = 0;
    if (argc < 2){
        printf("Please enter arguments.\n");
        return 1;
    }

    for (i = 1; i < argc; i++){
    // for (i = 0; i < argc; i++){  // 0 is program name
        printf("Argument %d is %s.\n", i, argv[i]);
    }

    int num_states = 3;
    // int num_states = 4; // seg fault

    char *states[] = {"AMK", "TPY", "BT"};
    // char *states = {"AMK", "TPY", "BT"}; // error

    for (i=0; i< num_states; i++){
        printf("State %d is %s.\n", i, states[i]);
    }

    argv[-33] = "AMK-BIS";
    argv[-32] = "BIS-TPY";

    for (i=0; i< num_states; i++){
        printf("State %d is %s.\n", i, states[i]);
    }

    states[33] = "ex13";
    states[34] = "111";
    states[35] = "222";

    for (i = 1; i < argc; i++){
    // for (i = 0; i < argc; i++){  // 0 is program name
        printf("Argument %d is %s.\n", i, argv[i]);
    }

    return 0;

    /*
    One memory address is 8 bytes, 64 bits. 
    An array of addresses pointing to strings.

    (gdb) x/8w states
    0x7fffffffdd30: 0x00400780  0x00000000  0x00400784  0x00000000
    0x7fffffffdd40: 0x00400788  0x00000000  0xec03b000  0x674755a0

    // set num_states to more than maximum
    (gdb) p states[3]
    $10 = 0x674755a0ec03b000 <error: Cannot access memory at address 0x674755a0ec03b000>

    (gdb) p states[2]
    $11 = 0x400788 "BT"

    (gdb) p states[3]
    $12 = 0x674755a0ec03b000 <error: Cannot access memory at address 0x674755a0ec03b000>

    (gdb) p states[33]
    $38 = 0x7fffffffe1e3 "/home/lam/Documents/Projects/LCTHW/myEx/ex13"
    (gdb) p argv[-33]
    $39 = 0x400780 "AMK"

    */

}
