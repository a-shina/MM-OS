#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


int main(int argc, char *argv[]) {

    int NUM_TASKS = 2;
    for (int x = 0; x < 3; x++) {

        FILE *fp[NUM_TASKS];

        time_t start, end;

        unsigned long receive[NUM_TASKS]; // array of received variables from tasks
        unsigned long sum = 0; // total sum from all received values from tasks
        unsigned long N = 10000000;

        unsigned long vals1[NUM_TASKS]; // array of first arguments to send to each task
        unsigned long vals2[NUM_TASKS]; // array of second arguments to send to each task

        int length1[NUM_TASKS]; // each argument is passed as a string, here we take the length of the first arguments as a string
        int length2[NUM_TASKS]; // length of the second arguments as a string

        char *str1[NUM_TASKS]; // array of pointers to first arguments as strings
        char *str2[NUM_TASKS]; // array of pointers to second arguments as strings

        for (int j = 0; j < 3; j++) {
            N = N * 10;
            sum = 0;
            for (int i = 0; i < NUM_TASKS; i++) {
                vals1[i] = i * N / NUM_TASKS; // creating first arguments
                vals2[i] = (i + 1) * N / NUM_TASKS; // creating second arguments

                length1[i] = snprintf(NULL, 0, "%lu ", vals1[i]); // getting lengths of first arguments
                length2[i] = snprintf(NULL, 0, "%lu", vals2[i]); // getting lengths of second arguments

                str1[i] = malloc(length1[i] + 1); // allocating memory for first arguments
                str2[i] = malloc(length2[i] + 1); // allocating memory for second arguments

                snprintf(str1[i], length1[i] + 1, "%lu ",
                         vals1[i]); // finally, we convert first arguments from long int to a string, and put them in str1
                snprintf(str2[i], length2[i] + 1, "%lu",
                         vals2[i]); // convert second arguments from long int to a string, and put them in str2

                strcat(str1[i], str2[i]); // concatenate both arguments into one string and store result in str1 array
            }

            time(&start);
            for (int i = 0; i < NUM_TASKS; i++) {
                char popen_exe[50] = "./popen_test ";
                strcat(popen_exe,
                       str1[i]); // creating popen() first argument e.g. "./popen_test 0 50000000" where 0 and 50000000 will be placed in char * argv[] in the tasks' main() argument
                fp[i] = popen(popen_exe, "r"); // create task
            }
            printf("\tMultitasking (%d tasks)\n", NUM_TASKS);
            printf("---------------------------------------\n");
            printf("N = %lu\n", N);
            for (int i = 0; i < NUM_TASKS; i++) {
                fscanf(fp[i], "%lu", &receive[i]); // receive the variables from tasks
                sum = sum + receive[i]; // sum the variables received
            }
            time(&end);

            double time_taken = (double) (end - start); // total time it took

            printf("Total sum = %lu\n", sum);

            printf("Total time taken = %f\n\n", time_taken);
        }
        NUM_TASKS = NUM_TASKS * 2;
    }

    return 0;
}

