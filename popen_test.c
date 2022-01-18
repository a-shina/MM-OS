#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

    unsigned long var1 = 0;
    unsigned long var2 = 0;
    unsigned long sum = 0;

    sscanf(argv[1], "%lu", &var1); //store first argument as long int in var1
    sscanf(argv[2], "%lu", &var2); //store second argument as long int in var2

    for (unsigned long i = var1; i < var2; i++) {
        sum = sum + i;
    }

    printf("%lu\n", sum);

    return 0;
}

