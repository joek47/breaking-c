#include <stdio.h>

int main(int argc, char *argv[])
{
    int ages[] = {23, 43, 12, 89, 2};
    char *names[] = {
        "Alan", "Fran", "Mars", "Jon", "Lisa"
    };

    int count = sizeof(ages)/sizeof(int);
    int i = 0;

    // ages is an address. ages[i] = *(ages + i) = give the value of (ages + i)
    for (i = 0; i < count; i++){
        printf("%s (%p) has %d (%p) years to live.\n", names[i], names[i], ages[i], &ages[i]);
        printf("%s (%p) has %d (%p) years to live.\n", *(names + i),*(names + i), *(ages + i), (ages + i));
    }

    printf("---\n");

    // int *cur_age = ages;
    int *cur_age = (int *) names;
    char **cur_name = names;

    for (i = 0; i < count; i++){
        printf("%s is %d years old.\n", *(cur_name + i), *(cur_age + i));
        printf("%s is %d years old.\n", cur_name[i], cur_age[i]);
    }

    printf("---\n");

    // pointer arithmetic. name+1 increments by 8 bytes, ages+1 increments by 4 bytes.
    /*
    (gdb) x/4w cur_name
    0x7fffffffdd30: 0x004008a4  0x00000000  0x004008a9  0x00000000
    (gdb) x/4w cur_name+1
    0x7fffffffdd38: 0x004008a9  0x00000000  0x004008ae  0x00000000
    (gdb) x/4w names+1
    0x7fffffffdd38: 0x004008a9  0x00000000  0x004008ae  0x00000000

    (gdb) x/4w cur_age
    0x7fffffffdd10: 0x00000017  0x0000002b  0x0000000c  0x00000059
    (gdb) x/4w cur_age+1
    0x7fffffffdd14: 0x0000002b  0x0000000c  0x00000059  0x00000002
       */

    for (cur_name = names, cur_age = ages;
        cur_name - names < count; 
        // cur_age - ages < count;
        cur_name++, cur_age++){
        printf("cur_name - names = %d, ", cur_name - names);
        printf("address of cur_name %p, ", *cur_name);
        printf("address of cur_age %p,\n", cur_age);
// 
        printf("%s is %d years old.\n", *cur_name, *cur_age);
        printf("%s is %d years old.\n", *cur_name, *cur_name);
    };


    return 0;
}
