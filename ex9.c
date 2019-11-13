#include <stdio.h>

int main(int argc, char *argv[]){
    // int i=100;
    int i;

    while (i < 25){
        printf("%d", i);
        i++;
    }

    printf("\n");

    while (i >= 0){
        printf("%d", i);
        i--;
    }
    return 0;
}
