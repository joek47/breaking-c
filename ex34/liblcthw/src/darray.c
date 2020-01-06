#include <lcthw/darray.h>
#include <assert.h>

DArray *DArray_create(size_t element_size, size_t initial_max)
{
    DArray *array = malloc(sizeof(DArray)); 
    check_mem(array);
    array->max = initial_max;
    check(array->max != 0, "You must set initial max > 0.");

    array->contents = calloc(initial_max, sizeof(void *));
    check_mem(array->contents);

    array->end = 0;
    array->element_size = element_size;
    array->expand_rate = DEFAULT_EXPAND_RATE;

    return array;

error:
    if (array)
        free(array);
    return NULL;
}

void DArray_clear(Darray * array)
{
    int i = 0;

    if (array->element_size > 0){
        for(i = 0; i< array->max; i++){
            if(array->contents[i] != NULL){
                free(array->contents[i]);
            }
        }
    }
}

static inline int DArray_resize(DArray * array, size_t newsize)
{
    array->max = newsize;
    check(array->max > 0, "The newsize must be 0.");

    // check realloc doesn't harm the original
    void *contents = realloc(array->max, array->max * sizeof(void *));
    check_mem(contents);

    array->contents = contents;

    return 0;

error:
    return -1;
}

int DArray_expand(DArray * array)
{
    return 0;
error:
    return -1;
}
