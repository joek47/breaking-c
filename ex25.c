#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "dbg.h"

#define MAX_DATA 100
/*fgets reads 0 character
#define MAX_DATA 1
*/

void test_malloc_calloc(int a, int b)
{
    /* https://stackoverflow.com/questions/501839/is-calloc4-6-the-same-as-calloc6-4 
    People mostly use allocation routines to allocate space for a set number of items, 
    so calloc() allows that to be specified nicely. So, for example, if you want space 
    for 100 integers or 20 of your own structure: */
    
    char *p1 = calloc(a,b);
    char *p2 = calloc(b,a);
    char *p3 = calloc(1,1);
    printf("p1: %p\tp2: %p\tp3: %p\n", p1, p2, p3);
}

int read_string(char **out_string, int max_buffer)
{
    //parameter is **out_string 
    //need allocate memory
    *out_string = calloc(1, max_buffer + 1);
    check_mem(*out_string);

    char *result = fgets(*out_string, max_buffer, stdin);
    check(result !=NULL, "Input error.");

    return 0;

error:
    if (*out_string) free(*out_string);
    *out_string = NULL;
    return -1;
}

int read_int(int *out_int)
{
    char *input = NULL;
    int rc = read_string(&input, MAX_DATA);
    check(rc == 0, "Failed to read number.");

    *out_int = atoi(input);

    free(input);
    return 0;

error:
    if(input) free(input);
    return -1;
}

int read_scan(const char *fmt, ...)
{
    int i = 0;
    int rc = 0;
    int *out_int = NULL;
    char *out_char = NULL;
    char **out_string = NULL;
    int max_buffer = 0;

    va_list argp;
    va_start(argp, fmt);

    for (i = 0; fmt[i] != '\0'; i++) {
        if (fmt[i] == '%'){
            i++;
            switch (fmt[i]){
                case '\0':
                    sentinel("Invalid format, you ended with %%.");
                    break;

                case 'd':
                    out_int = va_arg(argp, int *);
                    rc = read_int(out_int);
                    check(rc == 0, "Failed to read int.");
                    break;

                case 'c':
                    out_char = va_arg(argp, char *);
                    *out_char = fgetc(stdin);
                    break;

                case 's':
                    max_buffer = va_arg(argp, int);
                    out_string = va_arg(argp, char **);
                    rc = read_string(out_string, max_buffer);
                    check(rc == 0, "Failed to read string.");
                    break;

                default:
                    sentinel("Invalid format.");
            }
        } else {
            fgetc(stdin);
        }

        // check if end of file and error are set
        check(!feof(stdin) && !ferror(stdin), "Input error.");
    }

    va_end(argp);
    return 0;

error:
    va_end(argp);
    return -1;
}

void test_percent_sign()
{
    printf("Double %% and Escape \%\n");
}
int main(int argc, char *argv[])
{
    test_malloc_calloc(6,4);
    test_malloc_calloc(3,4);

    test_percent_sign();

    char *first_name = NULL;
    char initial = ' ';
    char *last_name = NULL;
    int age = 0;

    // pass pointer reference
    printf("What's your first name? ");
    int rc = read_scan("%s", MAX_DATA, &first_name);
    check(rc == 0, "Failed first name.");
    
    printf("What's your initial? ");
    rc = read_scan("%c", &initial);
    check(rc == 0, "Failed initial.");

    printf("What's your last name? ");
    rc = read_scan("%s", MAX_DATA, &last_name);
    check(rc == 0, "Failed last name.");

    printf("How old are you? ");
    rc = read_scan("%d", &age);

    printf("---- RESULTS ----\n");
    printf("First Name: %s", first_name);
    printf("Initial: '%c'\n", initial);
    printf("Last Name: %s", last_name);
    printf("Age: %d\n", age);

    free(first_name);
    free(last_name);
    return 0;

error:
    return -1;

}

/* NAME
       malloc, free, calloc, realloc - allocate and free dynamic memory

SYNOPSIS
       #include <stdlib.h>

       void *malloc(size_t size);
       void free(void *ptr);
       void *calloc(size_t nmemb, size_t size);
       void *realloc(void *ptr, size_t size);

DESCRIPTION
       The malloc() function allocates size bytes and returns a pointer to the allocated memory 
       .  The memory is not initialized.  If size is 0, then malloc()  returns  either  NULL 
       ,  or  a  unique pointer value that can later be successfully passed to free().

       The free() function frees the memory space pointed to by ptr, which must have been 
       returned by a previous call to malloc(), calloc(), or realloc().  Otherwise, 
       or if free(ptr)  has  already been called before, undefined behavior occurs.  
       If ptr is NULL, no operation is performed.

       The  calloc()  function allocates memory for an array of nmemb elements of size 
       bytes each and returns a pointer to the allocated memory.  The memory is set to 
       zero.  If nmemb or size is 0, then  calloc()  returns  either NULL, or a unique pointer 
       value that can later be successfully passed to free().

       The realloc() function changes the size of the memory block pointed to by ptr 
       to  size  bytes.  The  contents will be unchanged in the range from the start of 
       the region up to the minimum of the old and new sizes.  If the new size is larger 
       than the old size, the added memory will not be  initialized.   If ptr is NULL
       , then the call is equivalent to malloc(size), for all values of size; if size 
       is equal to zero, and ptr is  not  NULL,  then  the  call  is  equivalent  to 
       free(ptr).   Unless  ptr  is  NULL, it must have been returned by an earlier call 
       to malloc(), calloc() or realloc().  If the area pointed to was moved, a free(
       ptr) is done.

RETURN VALUE
       The malloc() and calloc() functions return a pointer to the allocated memory, 
       which  is  suit‐ ably  aligned for any built-in type.  On error, these functions return 
       NULL.  NULL may also be returned by a successful call to malloc() with a size of 
       zero, or by a successful call to cal‐ loc() with nmemb or size equal to zero.

       The free() function returns no value.

       The  realloc()  function  returns  a  pointer to the newly allocated memory, 
       which is suitably aligned for any built-in type and may be different from ptr
       , or NULL if the request fails.  If size was equal to 0, either NULL or a pointer 
       suitable to be passed to free() is returned.  If realloc() fails, the original block 
       is left untouched; it is not freed or moved.
*/

/* NAME
       stdarg, va_start, va_arg, va_end, va_copy - variable argument lists

SYNOPSIS
       #include <stdarg.h>

       void va_start(va_list ap, last);
       type va_arg(va_list ap, type);
       void va_end(va_list ap);
       void va_copy(va_list dest, va_list src);

DESCRIPTION
       A  function  may  be  called with a varying number of arguments of varying types
       .  The include file <stdarg.h> declares a type va_list and defines three macros for 
       stepping through  a  list of arguments whose number and types are not known to 
       the called function.  The  called  function  must  declare  an  object  of  type 
       va_list which is used by the macros va_start(), va_arg(), and va_end().

       va_start()
       The va_start() macro initializes ap for subsequent use by va_arg() and va_end(), 
       and  must  be called first.  The argument last is the name of the last argument before 
       the variable argument list, that is, the last argument of which the calling function 
       knows the type.  Because the address of this argument may be used in the va_start() 
       macro,  it  should  not  be declared as a register variable, or as a function or 
       an array type.

   va_arg()
       The  va_arg()  macro expands to an expression that has the type and value of 
       the next argument in the call.  The argument ap is the va_list ap  initialized  by  
       va_start().   Each  call  to va_arg()  modifies ap so that the next call returns the 
       next argument.  The argument type is a type name specified so that the type of 
       a pointer to an object that has the specified type can be obtained simply by 
       adding a * to type.  The  first  use  of the va_arg() macro after that of the 
       va_start() macro returns the argument after last.  Successive invocations return 
       the values of the remaining arguments.  If there is no next argument, or if type 
       is not compatible with the type of  the  actual  next argument (as promoted according 
       to the default argument promotions), random errors will occur.  If  ap  is  passed  
       to a function that uses va_arg(ap,type), then the value of ap is undefined after 
       the return of that function.  

   va_end()
       Each invocation of va_start() must be matched by a corresponding invocation of 
       va_end() in the same  function.   After the call va_end(ap) the variable ap is 
       undefined.  Multiple traversals of the list, each bracketed by va_start() and 
       va_end() are possible.  va_end() may be a  macro or a function.
*/

/* NAME
       clearerr, feof, ferror, fileno - check and reset stream status

SYNOPSIS
       #include <stdio.h>

       void clearerr(FILE *stream);

       int feof(FILE *stream);

       int ferror(FILE *stream);

       int fileno(FILE *stream);

   Feature Test Macro Requirements for glibc (see feature_test_macros(7)):

       fileno(): _POSIX_C_SOURCE

DESCRIPTION
       The  function clearerr() clears the end-of-file and error indicators for the stream 
       pointed to by stream.  
       
       The function feof() tests the end-of-file indicator for  the  stream  pointed  to  
       by  stream, returning nonzero if it is set.  The end -of-file indicator can be 
       cleared only by the function clearerr().  
       
       The function ferror () tests the error indicator for the stream pointed to by 
       stream, returning nonzero if it is set.  The error indicator can be reset only 
       by the clearerr() function.  
 */
