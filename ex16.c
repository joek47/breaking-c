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
struct Person *Person_create(char *name, int age, int height, int weight)
{
    /*make sure malloc returns a valid pointer. The malloc() function allocates 
      size bytes and returns a pointer to the allocated memory.  The memory is not 
      initialized. If size is 0, then malloc() returns either NULL, or a unique 
      pointer value that can later be successfully passed to free().  */

    struct Person *who = malloc(sizeof(struct Person));
    assert(who !=NULL);

    /* The strdup() function returns a pointer to a new string which is a 
       duplicate of the string s.  Memory for the new string is obtained with 
       malloc(3), and can be freed with free(3).  
       The strdup actually is like malloc, and it also copies the original string 
       into the memory it creates.  */
    who->name = strdup(name);
    who->age = age;
    who->height = height;
    who->weight = weight;

    return who;
}

/* use assert to make sure I’m not getting bad input. Then I use the function 
   free to return the memory I got with malloc and strdup. If you don’t do 
   this, you get a memory leak.  */
void Person_destroy(struct Person *who)
{
    assert(who != NULL);

    free(who->name);
    free(who);
}

void Person_print(struct Person *who)
{
    printf("Name: %s\n", who->name);
    printf("\tAge: %d\n", who->age);
    printf("\theight %d\n", who->height);
    printf("\tweight: %d\n", who->weight);
}

int main(int argc, char *argv[])
{
    struct Person *joe = Person_create("Joe A", 35, 170, 60);
    struct Person *liam = Person_create("Liam C", 1, 70, 10);

    printf("Joe is at memory address %p.\n", joe);
    printf("Joe->name is at memory address %p.\n", joe->name);
    Person_print(joe);

    printf("Liam is at memory address %p.\n", liam);
    Person_print(liam);

    joe->age += 20;
    Person_print(joe);

    liam->age += 20;
    Person_print(liam);

    /*
    joe->name points to 0x602030
    (gdb) x/10w joe
    0x602010:   0x00602030  0x00000000  0x00000037  0x000000aa
    0x602020:   0x0000003c  0x00000000  0x00000021  0x00000000
    0x602030:   0x20656f4a  0x00000041

    value of joe->name and address of joe->name
    (gdb) p joe->name
    $4 = 0x602030 "Joe A"
    (gdb) p &joe->name
    $5 = (char **) 0x602010
    `
    (gdb) p joe->age
    $3 = 55
    (gdb) p &joe->age
    $6 = (int *) 0x602018
    */ 

    //destroy. valgrind --leak-check=full ./ex16

    // Person_destroy(NULL);
    Person_destroy(joe);
    Person_destroy(liam);

    return 0;
}
