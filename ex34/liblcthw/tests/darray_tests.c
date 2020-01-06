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
