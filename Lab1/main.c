#include <math.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#include "lab1_IO.h"

/* Extracted from timer.h in the Development kit */
#define GET_TIME(now)                                                          \
    {                                                                          \
        struct timeval t;                                                      \
        gettimeofday(&t, NULL);                                                \
        now = t.tv_sec + t.tv_usec / 1000000.0;                                \
    }

int **A, **B, **C, n, thread_count, sqrt_p;

void *multiply_thread(void *rank) {
    int i, j, r, x, y, block;
    x = (int)floor((long)rank / sqrt_p);
    y = (long)rank % sqrt_p;
    block = (n / sqrt_p);

    for (i = block * x; i < block * (x + 1); i++)
        for (j = block * y; j < block * (y + 1); j++)
            for (r = 0; r < n; r++)
                C[i][j] += A[i][r] * B[r][j];

    return NULL;
}

double do_experiment() {
    double start, end;
    long i, j;
    pthread_t *thread_handles;

    C = malloc(n * sizeof(*C));
    for (i = 0; i < n; i++) {
        C[i] = malloc(n * sizeof(*C[i]));
        for (j = 0; j < n; j++)
            C[i][j] = 0;
    }

    GET_TIME(start);
    thread_handles = malloc(thread_count * sizeof(*thread_handles));
    for (i = 0; i < thread_count; ++i)
        pthread_create(&thread_handles[i], NULL, multiply_thread, (void *)i);
    for (i = 0; i < thread_count; ++i)
        pthread_join(thread_handles[i], NULL);
    free(thread_handles);
    GET_TIME(end);

    return end - start;
}

void usage(const char *prog_name) {
    fprintf(stderr,
            "USAGE: %s p\np is the thread count which must be >=1, "
            "a perfect square, and a factor of matrix size ^ 2\n",
            prog_name);
    exit(1);
}

int main(int argc, const char **argv) {
    double sqrt_p_double, total;

    if (argc != 2) usage(argv[0]);
    thread_count = atoi(argv[1]);
    if (thread_count == 0) usage(argv[0]);

    sqrt_p_double = sqrt(thread_count);
    if (sqrt_p_double != (int)sqrt_p_double) usage(argv[0]);
    sqrt_p = sqrt_p_double;

    if (Lab1_loadinput(&A, &B, &n) != 0) return 1;
    if ((n * n) % thread_count != 0) usage(argv[0]);

    total = do_experiment();
    printf("Total running time: %f seconds\n", total);
    if (Lab1_saveoutput(C, &n, total) != 0) return 1;
    return 0;
}
