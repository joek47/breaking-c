#include "ex22.h"
#include "dbg.h"

const char *MY_NAME = "T - 800";

void scope_demo(int count)
{
    log_info("count is: %d", count);

    if (count > 10){
        // count is only valid in this block
        int count = 100;

        log_info("count in this scope is %d", count);
    }

    log_info("count is at exit: %d", count);

    count = 3000;

    log_info("count after assign: %d", count);

    //extra, causes stack overflow
    // scope_demo(count);
}

void scope_demo2(int *count)
{
    log_info("count is: %d", *count);

    if (*count > 10){
        // count is only valid in this block
        int count = 100;

        log_info("count in this scope is %d", count);
    }

    log_info("count is at exit: %d", *count);

    *count = 3000;

    log_info("count after assign: %d", *count);

    //extra, causes stack overflow
    // scope_demo(count);
}

int main(int argc, char *argv[])
{
    log_info("My name: %s, age: %d", MY_NAME, get_age());

    set_age(100);

    log_info("My age is now: %d", get_age());

    log_info("THE_SIZE is:%d", THE_SIZE);
    print_size();

    THE_SIZE = 9;

    log_info("THE_SIZE is:%d", THE_SIZE);
    print_size();

    log_info("Ratio at first: %f", update_ratio(2.0));
    log_info("Ratio again: %f", update_ratio(10.0));
    log_info("Ratio once more: %f", update_ratio(300.0));

    // pass by value
    printf("Pass by value:\n");
    int count = 4;
    scope_demo(count);
    scope_demo(count *20);

    // passing count into function does not change it unless pass pointer
    log_info("count after calling scope demo: %d", count);

    // pass by reference
    printf("Pass by reference:\n");
    scope_demo2(&count);
    log_info("count after calling scope demo: %d", count);

    return 0;
}
