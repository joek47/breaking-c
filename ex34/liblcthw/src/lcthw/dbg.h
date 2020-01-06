#ifndef __dbg_h__
#define __dbg_h__

/* The C preprocessor is a macro preprocessor (allows you to define macros) that 
 * transforms your program before it is compiled. These transformations can be the 
 * inclusion of header file, macro expansions etc.  All preprocessing directives 
 * begin with a # symbol.  
 * https://www.programiz.com/c-programming/c-preprocessor-macros */

#include <stdio.h>
#include <errno.h>
#include <string.h>

#ifdef NDEBUG
#define debug(M, ...)
#else
#define debug(M, ...) fprintf(stderr, "DEBUG %s:%d: " M "\n",\
        __FILE__, __LINE__, ##__VA_ARGS__)
#endif

/* The  strerror() function returns a pointer to a string that describes the error 
 * code passed in the argument errnum, possibly using the LC_MESSAGES part of the 
 * current locale to  select  the appropriate  language.   (For  example,  if errnum 
 * is EINVAL, the returned description will be "Invalid argument".) */

#define clean_errno() (errno == 0 ? "None" : strerror(errno))

#define log_err(M, ...) fprintf(stderr,\
        "[ERROR] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__,\
        clean_errno(), ##__VA_ARGS__)

#define log_warn(M, ...) fprintf(stderr,\
        "[WARN] (%s:%d: errno: %s) " M "\n", __FILE__, __LINE__,\
        clean_errno(), ##__VA_ARGS__)

#define log_info(M, ...) fprintf(stderr,\
        "[INFO] (%s:%d) " M "\n", __FILE__, __LINE__, ##__VA_ARGS__)

#define check(A, M, ...) if(!(A)) {\
    log_err(M, ##__VA_ARGS__); errno=0; goto error;}

#define sentinel(M, ...) {log_err(M, ##__VA_ARGS__);\
    errno=0; goto error;}

#define check_mem(A) check((A), "Out of memory.")

#define check_debug(A, M, ...) if(!(A)) {\
    debug(M, ##__VA_ARGS__); errno=0; goto error;}

#endif
