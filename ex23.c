#define NDEBUG
#include <stdio.h>
#include <string.h>
#include "dbg.h"
#include <time.h>


int normal_copy(char *from, char *to, int count)
{
    int i = 0;

    for (i = 0; i < count; i++) {
        to[i] = from[i];
    }

    return i;
}

int duffs_device(char *from, char *to, int count)
{
    {
        int n = (count + 7) / 8;

        switch (count % 8) {
            case 0:
                do {
                    *to++ = *from++;
                    case 7:
                    *to++ = *from++;
                    case 6:
                    *to++ = *from++;
                    case 5:
                    *to++ = *from++;
                    case 4:
                    *to++ = *from++;
                    case 3:
                    *to++ = *from++;
                    case 2:
                    *to++ = *from++;
                    case 1:
                    *to++ = *from++;
                } while (--n > 0);
        }
    }

    return count;
}

int zeds_device(char *from, char *to, int count)
{
    {
        int n = (count + 7) / 8;
        debug("n starts: %d, count: %d, count%%8: %d", 
                n, count, count % 8);

        switch (count % 8) {
            case 0:
again:    *to++ = *from++;

            case 7:
          *to++ = *from++;
            case 6:
          *to++ = *from++;
            case 5:
          *to++ = *from++;
            case 4:
          *to++ = *from++;
            case 3:
          *to++ = *from++;
            case 2:
          *to++ = *from++;
            case 1:
          *to++ = *from++;
          debug("last case: n=%d", n);
          if (--n > 0) {
              debug("going again: n=%d", n);
              goto again;
          }
        }
    }

    return count;
}

int valid_copy(char *data, int count, char expects)
{
    int i = 0;
    for (i = 0; i < count; i++) {
        if (data[i] != expects) {
            log_err("[%d] %c != %c", i, data[i], expects);
            return 0;
        }
    }

    return 1;
}

int main(int argc, char *argv[])
{
    char from[1003] = { 'a' };
    char to[1003] = { 'c' };
    int rc = 0;
    clock_t time0, time1;

    // setup the from to have some stuff
    memset(from, 'x', 1003);
    // set it to a failure mode
    memset(to, 'y', 1003);
    check(valid_copy(to, 1003, 'y'), "Not initialized right.");

    printf("Clocks per sec: %lu.\n", CLOCKS_PER_SEC);
    // use normal copy to 
    /*        The value returned is the CPU time used so far as a clock_t; to get 
              the number of seconds used, divide by CLOCKS_PER_SEC.  If the pro‐ 
              cessor time used is not available or its value cannot be represented
              , the function returns the value (clock_t) -1. */
    time0 = clock();
    rc = normal_copy(from, to, 1003);
    time1 = clock();
    printf("Times %f and %f.\n", (double)time0, (double)time1);
    printf("Time taken for normal copy is %f.\n", (double)(time1 - time0) / CLOCKS_PER_SEC);
    check(rc == 1003, "Normal copy failed: %d", rc);
    check(valid_copy(to, 1003, 'x'), "Normal copy failed.");

    // reset
    time0 = clock();
    memset(to, 'y', 1003);
    time1 = clock();
    printf("Time taken for memset is %f.\n", (double)(time1 - time0) / CLOCKS_PER_SEC);

    // duffs version
    time0 = clock();
    rc = duffs_device(from, to, 1003);
    time1 = clock();
    printf("Time taken for duffs device is %f.\n", (double)(time1 - time0) / CLOCKS_PER_SEC);
    check(rc == 1003, "Duff's device failed: %d", rc);
    check(valid_copy(to, 1003, 'x'), "Duff's device failed copy.");

    // reset
    memset(to, 'y', 1003);

    // my version
    time0 = clock();
    rc = zeds_device(from, to, 1003);
    time1 = clock();
    printf("Time taken for zeds device is %f.\n", (double)(time1 - time0) / CLOCKS_PER_SEC);
    check(rc == 1003, "Zed's device failed: %d", rc);
    check(valid_copy(to, 1003, 'x'), "Zed's device failed copy.");

    return 0;
error:
    return 1;
}
