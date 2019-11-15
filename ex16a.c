#include <stdio.h>
#include <assert.h>
#include <stdlib.h>     //malloc, free
#include <string.h>     //strdup

struct Person{
    char *name;
    int age;
    int height;
    int weight;
};

// return pointer to struct
struct Person Person_create(char *name, int age, int height, int weight)
{
    struct Person who; 

    /* The strdup() function returns a pointer to a new string which is a 
       duplicate of the string s.  Memory for the new string is obtained with 
       malloc(3), and can be freed with free(3).  
       The strdup actually is like malloc, and it also copies the original string 
       into the memory it creates.  */
    who.name = strdup(name);
    who.age = age;
    who.height = height;
    who.weight = weight;

    return who;
}

/* use assert to make sure I’m not getting bad input. Then I use the function 
   free to return the memory I got with malloc and strdup. If you don’t do 
   this, you get a memory leak.  */
void Person_destroy(struct Person who)
{
    free(who.name);
    // free(who);
}

void Person_print(struct Person who)
{
    printf("Name: %s\n", who.name);
    printf("\tAge: %d\n", who.age);
    printf("\theight %d\n", who.height);
    printf("\tweight: %d\n", who.weight);
}

int main(int argc, char *argv[])
{
    struct Person joe = Person_create("Joe A", 35, 170, 60);
    struct Person liam = Person_create("Liam C", 1, 70, 10);

    printf("Joe is at memory address %p.\n", &joe);
    Person_print(joe);

    printf("Liam is at memory address %p.\n", &liam);
    Person_print(liam);

    joe.age += 20;
    Person_print(joe);

    liam.age += 20;
    Person_print(liam);

    //destroy. valgrind --leak-check=full ./ex16
    /*
        Joe is at memory address 0x7fffffffdd20.
        Name: Joe A
        Age: 35
        height 170
        weight: 60
        Liam is at memory address 0x7fffffffdd40.
        Name: Liam C
        Age: 1
        height 70
        weight: 10

        (gdb) x/20wx &joe
        0x7fffffffdd20: 0x00602010  0x00000000  0x00000037  0x000000aa
        0x7fffffffdd30: 0x0000003c  0x00000000  0x00000000  0x00000000
        0x7fffffffdd40: 0x00602030  0x00000000  0x00000015  0x00000046
        0x7fffffffdd50: 0x0000000a  0x00000000  0x5765f100  0x0f7d9524

        (gdb) x/20wd &joe
        0x7fffffffdd20: 6299664 0   55  170
        0x7fffffffdd30: 60  0   0   0
        0x7fffffffdd40: 6299696 0   21  70
        0x7fffffffdd50: 10  0   1466298624  259888420

       */

    // Person_destroy(NULL);
    Person_destroy(joe);
    Person_destroy(liam);

    return 0;
}
