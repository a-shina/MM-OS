#include <stdio.h>
#include <time.h>

unsigned long sum0toN (unsigned long N) {
    unsigned long sum = 0;

    for (unsigned long i = 0; i < N; i++) {
        sum = sum + i;
    }
    return sum;
}

int main() {

    unsigned long N1 = 100000000;
    unsigned long N2 = 1000000000;
    unsigned long N3 = 10000000000;
    unsigned long sum = 0;
    time_t start, end;
    double totalTime = 0;

    time(&start);

    sum = sum0toN(N1);

    time(&end);

    totalTime = (double) (end - start);

    printf("Baseline Case N = %lu\n", N1);
    printf("Sum: %lu\n", sum);
    printf("Total time: %f\n", totalTime);

    time(&start);

    sum = sum0toN(N2);

    time(&end);

    totalTime = (double) (end - start);

    printf("Baseline Case N = %lu\n", N2);
    printf("Sum: %lu\n", sum);
    printf("Total time: %f\n", totalTime);

    time(&start);

    sum = sum0toN(N3);

    time(&end);

    totalTime = (double) (end - start);

    printf("Baseline Case N = %lu\n", N3);
    printf("Sum: %lu\n", sum);
    printf("Total time: %f\n", totalTime);

    return 0;
}

