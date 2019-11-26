#include <stdint.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
    printf("=====\n");
    printf("Type Sizes:\n");
    printf("int8_t size:%ld \tmax:%d \tmin:%d\n", sizeof(int8_t), INT8_MAX, INT8_MIN);
    printf("uint8_t size:%lu \tmax:%d \tmin:%d\n", sizeof(uint8_t), UINT8_MAX, 0);

    printf("int16 %lu\n", sizeof(int16_t));
    printf("uint16_t %lu\n", sizeof(uint16_t));
    printf("int32_t %ld\n", sizeof(int32_t));
    printf("uint32_t %lu\n", sizeof(uint32_t));

    printf("int64_t size:%ld \tmax:%ld \tmin:%ld\n", sizeof(int64_t), INT64_MAX, INT64_MIN);
    printf("\twhich is the same as INTMAX_MAX:%ld \tINTMAX_MIN:%ld\n", INTMAX_MAX, INTMAX_MIN);
    printf("uint64_t size:%ld \tmax:%lu \tmin:%d\n", sizeof(uint64_t), UINT64_MAX, 0);
    printf("\twhich is the same as UINTMAX_MAX:%lu \tor SIZE_MAX:%lu\n", UINTMAX_MAX, SIZE_MAX);

    printf("Signed integer large enough to hold a pointer:%lu\n",sizeof(intptr_t));
    printf("Max value of a intptr_t:%ld\n\tmin value:%ld\n",INTPTR_MAX, INTPTR_MIN);
    printf("Unsigned integer large enough to hold a pointer:%lu\n",sizeof(uintptr_t));
    printf("Max value of a uintptr_t:%lu\n\t",UINTPTR_MAX);
    printf("biggest type possible\tintmax_t:%lu \tuintmax_t:%lu\n",\
            sizeof(intmax_t), sizeof(uintmax_t));

    printf("=====\n");
    printf("Bit Operators:\n");
    printf("1 shift left by 1 bit:%d\n", 1 << 1);
    printf("1 shift right by 1 bit:%d\n", 1 >> 1);
    printf("0 shift left by 1 bit:%d\n", 0 << 1);
    printf("00 bitwise or 01:%d\n", 0|1);
    printf("10 bitwise xor 01:%d\n", 2^1);

    printf("=====\n");
    printf("Type Conversion:\n");
    printf("long double:%d \tdouble:%d \tfloat:%d \tint:%d \tlong:%d\n",\
            sizeof(long double), sizeof(double), sizeof(float),\
            sizeof(int), sizeof(long));
    return 0;
}
