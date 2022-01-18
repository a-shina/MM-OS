#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

struct arg_struct {
    unsigned long arg1;
    unsigned long arg2;
};

void* ChildThread(void* arguments) {

    unsigned long *sum = (unsigned long*) malloc(sizeof(long));

    struct arg_struct *args = arguments;

    for (unsigned long i = args->arg1; i < args->arg2; i++) {
        *sum += i;
    }
    pthread_exit((void*)sum);
}

int main() {

    unsigned long N = 10000000;
    unsigned long sum = 0;

    time_t start, end;

    struct arg_struct args;
    struct arg_struct args2;

    unsigned long* receive = NULL;
    unsigned long* receive2 = NULL;

    for (int i = 0; i < 3; i++) {
        N = N * 10;

        args.arg1 = 0;
        args.arg2 = N/2;

        args2.arg1 = N/2;
        args2.arg2 = N;

        receive = NULL;
        receive2 = NULL;

        pthread_t thread_id1, thread_id2;

        time(&start);

        pthread_create(&thread_id1, NULL, ChildThread, (void *) &args);
        pthread_create(&thread_id2, NULL, ChildThread, (void *) &args2);

        pthread_join(thread_id1, (void **) &receive);
        pthread_join(thread_id2, (void **) &receive2);

        time(&end);

        double totalTime = (double) (end - start);

        sum = *receive + *receive2;

        printf("Sum: %lu\n", sum);
        printf("Total time: %f\n", totalTime);
    }

    return 0;
}
