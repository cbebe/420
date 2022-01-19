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

void *multiply_thread(void *rank) {
    long my_rank;
    int i, j, r, x, y;
    int first_i, last_i, first_j, last_j, last_r;

    my_rank = (long)rank;
    x = my_rank / sqrt_p;
    y = my_rank % sqrt_p;

    first_i = (n / sqrt_p) * x;
    last_i = (n / sqrt_p) * (x + 1) - 1;
    first_j = (n / sqrt_p) * y;
    last_j = (n / sqrt_p) * (y + 1) - 1;
    last_r = n - 1;

    for (i = first_i; i <= last_i; i++)
        for (j = first_j; j <= last_j; j++) {
            C[i][j] = 0;
            for (r = 0; r <= last_r; r++)
                C[i][j] += A[i][r] * B[r][j];
        }

    return NULL;
}

void do_experiment() {
    double start, end;
    long i;
    pthread_t *thread_handles;
    if (Lab1_loadinput(&A, &B, &n) != 0) exit(1);

    if ((n * n) % thread_count != 0) {
        fprintf(stderr, "Thread count is not a factor of (matrix size)^2!\n");
        exit(1);
    }

    C = malloc(n * sizeof(int *));
    for (i = 0; i < n; i++)
        C[i] = malloc(n * sizeof(int));

    GET_TIME(start);
    thread_handles = malloc(thread_count * sizeof(pthread_t));
    for (i = 0; i < thread_count; ++i)
        pthread_create(&thread_handles[i], NULL, multiply_thread, (void *)i);
    for (i = 0; i < thread_count; ++i)
        pthread_join(thread_handles[i], NULL);
    GET_TIME(end);

    total = end - start;
    free(thread_handles);
    if (Lab1_saveoutput(C, &n, total) != 0) exit(1);
}

int main(int argc, const char **argv) {
    double sqrt_p_double;
    if (argc != 2) {
        fprintf(stderr, "USAGE: %s <thread_count>\n", argv[0]);
        exit(1);
    };
    thread_count = atoi(argv[1]);
    sqrt_p_double = sqrt(thread_count);
    if (sqrt_p_double != (int)sqrt_p_double) {
        fprintf(stderr, "Thread count is not a square!\n");
        exit(1);
    }
    sqrt_p = sqrt_p_double;

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
