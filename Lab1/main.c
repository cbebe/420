#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lab1_IO.h"

#include <sys/time.h>

/* Extracted from timer.h in the Development kit */
#define GET_TIME(now)                                                          \
    {                                                                          \
        struct timeval t;                                                      \
        gettimeofday(&t, NULL);                                                \
        now = t.tv_sec + t.tv_usec / 1000000.0;                                \
    }

#ifdef DEV
#include "dev.h"
#endif

int n, thread_count;
int **A, **B, **C;
double total;

void init_result_matrix();

void *multiply_thread(void *rank) {
    /*
    Multiplies the matrices A and B into matrix C
    📋 TODO: Implement using shared memory and pthreads
    */
    long my_rank;
    int i, j, k;
    my_rank = (long)rank;
    /* serial implementation 🥴 */
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++) {
            C[i][j] = 0;
            for (k = 0; k < n; k++)
                C[i][j] += A[i][k] * B[k][j];
        }

    return NULL;
}

void print_usage(const char *prog_name) {
    fprintf(stderr, "USAGE: %s <thread_count>\n", prog_name);
    exit(1);
}

void do_experiment() {
    double start, end;
    long thread;
    pthread_t *thread_handles;
    Lab1_loadinput(&A, &B, &n);
    init_result_matrix();
    GET_TIME(start)

    thread_handles = malloc(thread_count * sizeof(pthread_t));

    for (thread = 0; thread < thread_count; ++thread)
        pthread_create(&thread_handles[thread], NULL, multiply_thread,
                       (void *)thread);

    for (thread = 0; thread < thread_count; ++thread)
        pthread_join(thread_handles[thread], NULL);

    GET_TIME(end)
    total = end - start;
    Lab1_saveoutput(C, &n, total);
}

int main(int argc, const char **argv) {
    if (argc != 2) print_usage(argv[0]);
    thread_count = atoi(argv[1]);

#ifdef DEV
    say_hello();
    log_str("Matrix Multiplication:\n", BLUE);
#endif

    do_experiment();

#ifdef DEV
    print_result(n, total);
    say_goodbye();
#endif

    return 0;
}

void init_result_matrix() {
    /*
    Allocate memory for the result matrix
    */
    int i;
    C = malloc(n * sizeof(int *));
    for (i = 0; i < n; i++)
        C[i] = malloc(n * sizeof(int));
}
