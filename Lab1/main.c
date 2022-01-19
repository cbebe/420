#include <math.h>
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

int n, thread_count, sqrt_p;
int **A, **B, **C;
double total;

void init_result_matrix();

void *multiply_thread(void *rank) {
    /*
    Multiplies the matrices A and B into matrix C
    📋 TODO: Implement using shared memory and pthreads
    */
    long my_rank;
    int i, j, r;
    int x, y;
    int first_i, last_i, first_j, last_j;
    my_rank = (long)rank;
    x = my_rank / sqrt_p;
    y = my_rank % sqrt_p;

    first_i = (n / sqrt_p) * x;
    last_i = (n / sqrt_p) * (x + 1) - 1;
    first_j = (n / sqrt_p) * y;
    last_j = (n / sqrt_p) * (y + 1) - 1;

    for (i = first_i; i <= last_i; i++)
        for (j = first_j; j <= last_j; j++) {
            C[i][j] = 0;
            for (r = 0; r <= n - 1; r++)
                C[i][j] += A[i][r] * B[r][j];
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
    if (Lab1_loadinput(&A, &B, &n) != 0) exit(1);

    if (n * n % thread_count != 0 || sqrt_p * sqrt_p != thread_count) {
        fprintf(stderr, "Not a valid p!");
        exit(1);
    }

    init_result_matrix();
    GET_TIME(start);

    thread_handles = malloc(thread_count * sizeof(pthread_t));

    for (thread = 0; thread < thread_count; ++thread)
        pthread_create(&thread_handles[thread], NULL, multiply_thread,
                       (void *)thread);

    for (thread = 0; thread < thread_count; ++thread)
        pthread_join(thread_handles[thread], NULL);

    GET_TIME(end);
    total = end - start;
    if (Lab1_saveoutput(C, &n, total) != 0) exit(1);
}

int main(int argc, const char **argv) {
    if (argc != 2) print_usage(argv[0]);
    thread_count = atoi(argv[1]);
    sqrt_p = sqrt(thread_count);

#ifdef DEV
    say_hello();
    log_str("Matrix Multiplication:\n", BLUE);
    do_experiment();
    print_result(n, total);
    say_goodbye();
#else
    do_experiment();
    printf("Total running time: %f seconds\n", total);
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
