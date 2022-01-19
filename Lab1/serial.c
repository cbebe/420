#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>

#include "lab1_IO.h"

int main(int argc, const char **argv) {
    int n;
    int **A, **B, **C;
    int i, j, r;

    struct timeval t;
    double start, end, total;

    if (Lab1_loadinput(&A, &B, &n) != 0) exit(1);

    C = malloc(n * sizeof(int *));
    for (i = 0; i < n; i++)
        C[i] = malloc(n * sizeof(int));

    gettimeofday(&t, NULL);
    start = t.tv_sec + t.tv_usec / 1000000.0;
    /* Start timed section */
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++) {
            C[i][j] = 0;
            for (r = 0; r < n; r++)
                C[i][j] += A[i][r] * B[r][j];
        }
    /* End timed section */
    gettimeofday(&t, NULL);
    end = t.tv_sec + t.tv_usec / 1000000.0;

    total = end - start;

    printf("Total running time: %f seconds\n", total);
    if (Lab1_saveoutput(C, &n, total) != 0) exit(1);
    return 0;
}
