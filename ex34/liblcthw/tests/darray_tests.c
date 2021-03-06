#include "minunit.h"
#include <lcthw/darray.h>
#include <assert.h>

static DArray *array = NULL;
int *val1 = NULL;
int *val2 = NULL;
int *val3 = NULL;

char *test_create()
{
    array = DArray_create(sizeof(int), 100);
    mu_assert(array != NULL, "Failed to create array.");
    mu_assert(array->contents != NULL, "contents are wrong in darray.");
    mu_assert(array->end == 0, "end isn't at the right spot.");
    mu_assert(array->element_size == sizeof(int), "wrong element size.");
    mu_assert(array->max == 100, "wrong max length on initial size.");

    return NULL;
}

char *test_destroy()
{
    DArray_destroy(array);

    return NULL;
}

char *test_new()
{
    val1 = DArray_new(array);
    mu_assert(val1 != NULL, "Failed to make a new element.");

    val2 = DArray_new(array);
    mu_assert(val2 != NULL, "Failed to make a new element.");

    return NULL;
}

char *test_set()
{
    DArray_set(array, 0, val1);
    DArray_set(array, 1, val2);

    return NULL;
}

char *test_get()
{
    mu_assert(DArray_get(array, 0) == val1, "wrong first value.");
    mu_assert(DArray_get(array, 1) == val2, "wrong second value.");

    return NULL;
}

char *test_remove()
{
    int *val_check = DArray_remove(array, 0);
    mu_assert(val_check != NULL, "should not get NULL");
    mu_assert(val_check == val1, "should get val1");
    mu_assert(DArray_get(array, 0) == NULL, "first element should be gone");
    DArray_free(val_check);

    val_check = DArray_remove(array, 1);
    mu_assert(val_check != NULL, "should not get NULL");
    mu_assert(val_check == val2 "should get val1");
    mu_assert(DArray_get(array, 1) == NULL, "second element should be gone");
    DArray_free(val_check);

    return NULL;
}

char *test_expand_contract()
{
    int old_max = array->max;
    DArray_expand(array);
    mu_assert((array->expand_rate + old_max) == array->max, "Wrong size after expansion.");

    DArray_contract(array);
    mu_assert(array->max == array->expand_rate + 1, "should stay at expand rate.");

    // minimum contraction
    DArray_contract(array);
    mu_assert(array->max == array->expand_rate + 1, "should stay at expand rate.");

    return NULL;
}

char *test_push_pop()
{
    int i = 0;

    for(i = 0; i < 1000; i++){
        int *val = DArray_new(array);
        *val = i * 333;
        DArray_push(array, val);
    }

    mu_assert(array->max = 1201, "Wrong max size.");

    for (i = 999; i >= 0; i--){
        int *val = DArray_pop(array);
        mu_assert(val != NULL, "Shouldn't get a NULL.");
        mu_assert(val == i*333, "Wrong value.");
        DArray_free(val);
    }

    return NULL;
}

char *all_tests()
{
    mu_suite_start();

    mu_run_test(test_create);
    mu_run_test(test_destroy);
    mu_run_test(test_new);
    mu_run_test(test_set);
    mu_run_test(test_get);
    mu_run_test(test_remove);
    mu_run_test(test_expand_contract);
    mu_run_test(test_push_pop);

    return NULL;
}

RUN_TESTS(all_tests);
