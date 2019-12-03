#include <stdio.h>
#include <stdlib.h>
#include "dbg.h"

#define MAX_DATA 20

typedef enum EyeColor {
    BLUE_EYES, GREEN_EYES, BROWN_EYES,
    BLACK_EYES, OTHER_EYES
} EyeColor;

const char *EYE_COLOR_NAMES[] = {
    "Blue", "Green", "Brown", "Black", "Other"
};

typedef struct Person {
    int age;
    char first_name[MAX_DATA];
    char last_name[MAX_DATA];
    EyeColor eyes;
    float income;
} Person;

int main(int argc, char *argv[])
{
    Person you = {.age = 0};
    int i = 0;
    char *in = NULL;
    char buf[MAX_DATA];

    // in = fgets(you.first_name, MAX_DATA - 1, stdin);
    // in = gets(you.first_name);
    // in = fscanf(stdin, "%50s", you.first_name);
    printf("What's your First Name? ");
    in = scanf("%s[^\n]", you.first_name);
    check(in !=NULL, "Failed to read first name.");
    
    /* char *fgets(char *s, int size, FILE *stream); 
     * fgets() reads  in  at most one less than size characters from 
     * stream and stores them into the buffer pointed to by s.  
     * Reading stops after an EOF or a newline.  If a newline is 
     * read, it is stored  into the buffer.  A terminating null 
     * byte ('\0') is stored after the last character in the buffer.

       gets() reads a line from stdin into the buffer pointed to by s until either a 
     * terminating new‐ line or EOF, which it replaces with a null byte ('\0').  No 
     * check for buffer overrun  is  per‐ formed (see BUGS below).  
     * Never  use  gets().   Because it is impossible to tell without knowing the data 
     * in advance how many characters gets() will read, and because gets() will continue to  
     * store  characters  past the  end  of the buffer, it is extremely dangerous to 
     * use.  It has been used to break computer security.  Use fgets() instead.  */

    // weird behaviour using fscanf to read string
    /* you.first_name is not an address
    (gdb) x &you
    0x7fffffffdfb0:	0x00000000
    (gdb) p you.first_name
    $3 = "a\n", '\000' <repeats 97 times>
    (gdb) x you.first_name
    0x7fffffffdfb4:	0x00000a61 */

    /* https://www.eecs.wsu.edu/~cs150/reading/scanf.htm 
     * Instead, you will want scanf to read only the visible characters, skipping white 
     * space (including the newline) as it does for numeric data. The secret to getting scanf 
     * to perform this way is to put a blank in the format string before the %c format specifier
     */

    /* There is no bounds checking in scanf() so it doesn't know where to stop and the 
     * program can abend with sigsegv so better to use fgets() for reading the input stream 
     * followed by using sscanf() for parsing it. 
     https://cboard.cprogramming.com/c-programming/109243-scanf-vs-fgets.html 
     >There is no bounds checking in scanf() Incorrect. There is bounds checking in 
     scanf, but it's not automagic as many seem to expect. The following will never overflow 
     the array: 

     char buf[256];
     scanf ( "%255s", buf ); 

    http://sekrit.de/webdocs/c/beginners-guide-away-from-scanf.html
    $ ./example1
    enter a number: 42
    You entered 42.

    Or does it?

    $ ./example1
    enter a number: abcdefgh
    You entered 38.

    Oops. Where does the value 38 come from?

    The answer is: This could be any value, or the program could just crash. A crashing program 
    in just two lines of code is quite easy to create in C. scanf() is asked to convert a 
    number, and the input doesn't contain any numbers, so scanf() converts nothing. 
    As a consequence, the variable a is never written to and using the value of an uninitialized 
    variable in C is undefined behavior. */

    // don't need newline
    /*
    in = fgets(you.last_name, MAX_DATA - 1, stdin);
    */

    printf("What's your Last Name? ");
    in = scanf("%s[^\n]", you.last_name);
    check(in !=NULL, "Failed to read last name."); 

    /* The scanf() function reads input from the standard input stream stdin,  fscanf()  
     * reads  input from the stream pointer stream, 
     * int scanf(const char *format, ...); 
     * int fscanf(FILE *stream, const char *format, ...);
       The scanf() function reads input from the standard input stream stdin,  fscanf
       ()  reads  input from the stream pointer stream, and sscanf() reads its input 
       from the character string pointed to by str.  The vfscanf() function is analogous 
       to vfprintf(3) and reads input  from  the  stream  pointer stream using a 
       variable argument list of pointers (see stdarg(3).  The vscanf() function scans 
       a variable argument list from the standard input and the vsscanf() function scans  
       it  from  a string; these are analogous to the vprintf(3) and vsprintf(
       3) functions respectively.  */

    /* fgets return 0 after scanf
     * As geekosaur said, you are not handling the newline left behind by scanf. You 
     * can modify your scanf format string to take it into account: 
    https://stackoverflow.com/questions/10156696/fgets-not-waiting-for-input */

    /* printf("How old are you? ");
    in = fgets(buf, MAX_DATA, stdin);
    check(in !=NULL, "Failed to read age.");
    you.age = atoi(buf); 
    int rc; */

    // int rc = fscanf(stdin, "%d", &you.age);
    int rc = scanf("%d", &you.age);
    check(rc > 0, "You have to enter a number.");
    printf("%d\n", you.age); 

    printf("BLUE_EYES has integer value of %d\n", BLUE_EYES);
    printf("OTHER_EYES has integer value of %d\n", OTHER_EYES);
    printf("What color are your eyes:\n");
    for(i = 0; i <= OTHER_EYES; i++){
        printf("%d) %s\n", i + 1, EYE_COLOR_NAMES[i]);
    }
    printf("> ");

    int eyes = -1;
    rc = fscanf(stdin, "%d", &eyes);
    check(rc > 0, "You have to enter a number."); 

    // Rewrite without using fscanf
    /* jin = fgets(buf, MAX_DATA, stdin);
    check(in !=NULL, "Failed to read eyes.");
    eyes = atoi(buf);
    printf("You entered %s %d:\n", buf, eyes);*/

    you.eyes = eyes - 1;
    // can read other memory without check
    check(you.eyes <= OTHER_EYES && you.eyes >=0,\
            "Do it right, that's not an option.");

    printf("How much do you make an hour? ");
    rc = fscanf(stdin, "%f", &you.income);
    check(rc > 0, "Enter a floating point number.");

    printf("-----RESULTS-----\n");

    printf("First Name: %s", you.first_name);
    printf("Last Name: %s", you.last_name);
    printf("Age: %d\n", you.age);
    printf("Eyes: %s\n", EYE_COLOR_NAMES[you.eyes]);
    printf("Income: %.2f\n", you.income);


    return 0;

error:
    return -1;
}

/*        #include <stdio.h> 
          The fopen() function opens the file whose name is the string pointed to by 
          path and associates a stream with it.
       
       FILE *fopen(const char *path, const char *mode);
       FILE *fdopen(int fd, const char *mode);
       FILE *freopen(const char *path, const char *mode, FILE *stream);

        The  fdopen() function associates a stream with the existing file descriptor, 
        fd.  The mode of the stream (one of the values "r", "r+", "w", "w+", "a", "
        a+") must  be  compatible  with  the mode  of  the  file  descriptor.  The file 
        position indicator of the new stream is set to that belonging to fd, and the 
        error and end-of-file indicators are cleared.  Modes "w" or  "w+"  do not  cause 
        truncation of the file.  The file descriptor is not dup'ed, and will be closed when 
        the stream created by fdopen() is closed.  The result of applying fdopen() to 
        a shared  memory object is undefined.  

        The  freopen()  function  opens the file whose name is the string pointed to 
        by path and asso‐ ciates the stream pointed to 
        by stream with it.  The original stream (if it exists) is closed.  The  mode  argument 
        is used just as in the fopen() function.  The primary use of the freopen() function 
        is to change the file associated with a standard text stream (stderr, stdin, or  std‐ out).

    https://www.unix.com/programming/9230-difference-between-fdopen-freopen.html
 * fropen is the same thing as an fclose followed by an fopen. You might use it if you 
 * had a list of list to loop through. To go the the next file, you would just freopen() 
 * it. That would close the current file and open the new file. It's ok to use freopen() 
 * even on the first file.  
 *
 * fdopen takes a file opened by a system call and wraps a 
 * FILE structure around it. The file stays opened, but now it looks like fopen() opened 
 * it. So now all of the standard c library stuff like fprintf() can be used on it.  */

/*     fclose - close a stream 
 *
 *     SYNOPSIS
       #include <stdio.h>
       int fclose(FILE *stream); 
       The  fclose()  function  flushes  the stream pointed to by stream (writing any 
       buffered output data using fflush(3)) and closes the underlying file descriptor.   

       fcloseall - close all open streams */

/* SYNOPSIS
       #include <stdio.h>

       int fseek(FILE *stream, long offset, int whence);

       long ftell(FILE *stream);

       void rewind(FILE *stream);

       int fgetpos(FILE *stream, fpos_t *pos);
       int fsetpos(FILE *stream, const fpos_t *pos);

DESCRIPTION
       The  fseek()  function  sets  the file position indicator for the stream pointed to 
       by stream.  The new position, measured in bytes, is obtained by adding offset bytes 
       to the position speci‐ fied  by  whence.  If whence is set to SEEK_SET, SEEK_CUR, 
       or SEEK_END, the offset is relative to the start of the file, the current position 
       indicator,  or  end-of-file,  respectively.   A successful  call  to  the fseek
       () function clears the end-of-file indicator for the stream and undoes any effects 
       of the ungetc(3) function on the same stream.  
       
       The ftell() function obtains the current value of the file position indicator for  
       the  stream pointed to by stream .  
       
       The  rewind() function sets the file position indicator for the stream pointed 
       to by stream to the beginning of the file.  It is equivalent to: (void) fseek(
       stream, 0L, SEEK_SET) except that the error indicator for the stream is also cleared 
       (see clearerr(3)).  
       
       The fgetpos() and fsetpos() functions are  alternate  interfaces  
       equivalent  to  ftell()  and fseek()  (with whence set to SEEK_SET), setting and 
       storing the current value of the file off‐ set into or from the object referenced by 
       pos.  On some non-UNIX systems, an fpos_t object may be  a  complex  object  and  
       these  routines may be the only way to portably reposition a text stream.  
       
       https://stackoverflow.com/questions/47954500/is-fgetpos-fsetpos-any-faster-than-fseek?rq=1
       For general file positioning, fseek()/ftell() are limited to files sizes about LONG_MAX
       . fsetpos()/fgetpos() are designed to handle the file system's file sizes.  For 
       large files, fseek()/ftell() are not an option. @Thomas Padron-McCarthy When coding 
       C99 onward, robust code uses fsetpos()/fgetpos() in lieu of a minor optimization that 
       may of may not be present using the more limited fseek()/ftell().  */

/* SYNOPSIS
       #include <stdio.h>

       int printf(const char *format, ...);
       int fprintf(FILE *stream, const char *format, ...);
       int dprintf(int fd, const char *format, ...);
       int sprintf(char *str, const char *format, ...);
       int snprintf(char *str, size_t size, const char *format, ...);

       #include <stdarg.h>

       int vprintf(const char *format, va_list ap);
       int vfprintf(FILE *stream, const char *format, va_list ap);
       int vdprintf(int fd, const char *format, va_list ap);
       int vsprintf(char *str, const char *format, va_list ap);
       int vsnprintf(char *str, size_t size, const char *format, va_list ap);

  DESCRIPTION
       The functions in the printf() family produce output according to a format as 
       described  below.  The  functions  printf()  and  vprintf()  write  output to 
       stdout, the standard output stream; fprintf() and vfprintf() write output to  
       the  given  output  stream;  sprintf(),  snprintf(), vsprintf() and vsnprintf() 
       write to the character string str.  */ 

/* NAME
       fread, fwrite - binary stream input/output

SYNOPSIS
       #include <stdio.h>

       size_t fread(void *ptr, size_t size, size_t nmemb, FILE *stream);

       size_t fwrite(const void *ptr, size_t size, size_t nmemb,
                     FILE *stream);

DESCRIPTION
       The  function fread() reads nmemb items of data, each size bytes long, from the 
       stream pointed to by stream, storing them at the location given by ptr.  The function 
       fwrite() writes nmemb items of data, each size bytes long, to the stream  pointed 
       to by stream, obtaining them from the location given by ptr.  */
