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

int main(int argc, const char **argv) {
    int **A, **B, **C, n, i, j, r;
    double start, end;

    if (Lab1_loadinput(&A, &B, &n) != 0) return 1;
    C = malloc(n * sizeof(int *));
    for (i = 0; i < n; i++) {
        C[i] = malloc(n * sizeof(int));
        for (j = 0; j < n; j++)
            C[i][j] = 0;
    }

    GET_TIME(start);
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
            for (r = 0; r < n; r++)
                C[i][j] += A[i][r] * B[r][j];
    GET_TIME(end);

    printf("Total running time: %f seconds\n", end - start);
    if (Lab1_saveoutput(C, &n, end - start) != 0) return 1;
    return 0;
}
