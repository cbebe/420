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

int n;
int **A, **B, **C;
double total;

int main(int argc, const char **argv) {
    int i, j, r;
    double start, end;
    if (Lab1_loadinput(&A, &B, &n) != 0) exit(1);

    C = malloc(n * sizeof(int *));
    for (i = 0; i < n; i++)
        C[i] = malloc(n * sizeof(int));
    GET_TIME(start);

    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++) {
            C[i][j] = 0;
            for (r = 0; r <= n - 1; r++)
                C[i][j] += A[i][r] * B[r][j];
        }

    GET_TIME(end);
    total = end - start;
    printf("Total running time: %f seconds\n", total);
    if (Lab1_saveoutput(C, &n, total) != 0) exit(1);
    return 0;
}
