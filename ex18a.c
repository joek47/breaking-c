#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    int *index = malloc(sizeof(int));
    printf("Address %p contains %d\n", index, *index);
    printf("Address %p contains string %s\n", index, index);
    *index = 1;
    printf("Address %p contains %d\n", index, *index);

    int index2 = 1;
    printf("Address %p contains %d\n", &index2, index2);

    char *add = (char *) index;
    printf("%p\n", add);

    /* (gdb) p index
        $1 = (int *) 0x602010
        (gdb) x index
        0x602010:   0x00000001
        (gdb) p &index
        $3 = (int **) 0x7fffffffdd40 

        (gdb) p index2
        $2 = 1
       (gdb) x index2
        0x1:    Cannot access memory at address 0x1
        (gdb) x &index2
        0x7fffffffdd3c: 0x00000001 */ 
}
