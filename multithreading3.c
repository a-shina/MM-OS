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

    struct arg_struct args1;
    struct arg_struct args2;
    struct arg_struct args3;
    struct arg_struct args4;
    struct arg_struct args5;
    struct arg_struct args6;
    struct arg_struct args7;
    struct arg_struct args8;

    unsigned long* receive1 = NULL;
    unsigned long* receive2 = NULL;
    unsigned long* receive3 = NULL;
    unsigned long* receive4 = NULL;
    unsigned long* receive5 = NULL;
    unsigned long* receive6 = NULL;
    unsigned long* receive7 = NULL;
    unsigned long* receive8 = NULL;

    for (int i = 0; i < 3; i++) {
        N = N * 10;

        args1.arg1 = 0;
        args1.arg2 = N/8;

        args2.arg1 = N/8;
        args2.arg2 = N/4;

        args3.arg1 = N/4;
        args3.arg2 = 3*N/8;

        args4.arg1 = 3*N/8;
        args4.arg2 = N/2;

        args5.arg1 = N/2;
        args5.arg2 = 5*N/8;

        args6.arg1 = 5*N/8;
        args6.arg2 = 6*N/8;

        args7.arg1 = 6*N/8;
        args7.arg2 = 7*N/8;

        args8.arg1 = 7*N/8;
        args8.arg2 = N;

        receive1 = NULL;
        receive2 = NULL;
        receive3 = NULL;
        receive4 = NULL;
        receive5 = NULL;
        receive6 = NULL;
        receive7 = NULL;
        receive8 = NULL;

        pthread_t thread_id1, thread_id2, thread_id3, thread_id4, thread_id5, thread_id6, thread_id7, thread_id8;

        time(&start);

        pthread_create(&thread_id1, NULL, ChildThread, (void *) &args1);
        pthread_create(&thread_id2, NULL, ChildThread, (void *) &args2);
        pthread_create(&thread_id3, NULL, ChildThread, (void *) &args3);
        pthread_create(&thread_id4, NULL, ChildThread, (void *) &args4);
        pthread_create(&thread_id5, NULL, ChildThread, (void *) &args5);
        pthread_create(&thread_id6, NULL, ChildThread, (void *) &args6);
        pthread_create(&thread_id7, NULL, ChildThread, (void *) &args7);
        pthread_create(&thread_id8, NULL, ChildThread, (void *) &args8);

        pthread_join(thread_id1, (void **) &receive1);
        pthread_join(thread_id2, (void **) &receive2);
        pthread_join(thread_id3, (void **) &receive3);
        pthread_join(thread_id4, (void **) &receive4);
        pthread_join(thread_id5, (void **) &receive5);
        pthread_join(thread_id6, (void **) &receive6);
        pthread_join(thread_id7, (void **) &receive7);
        pthread_join(thread_id8, (void **) &receive8);

        time(&end);

        double totalTime = (double) (end - start);

        sum = *receive1 + *receive2 + *receive3 + *receive4 + *receive5 + *receive6 + *receive7 + *receive8;

        printf("Sum: %lu\n", sum);
        printf("Total time: %f\n", totalTime);
    }

    return 0;
}
