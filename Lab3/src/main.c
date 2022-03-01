#include "Lab3IO.h"
#include "timer.h"

#include <stdio.h>
#include <stdlib.h>

#define USAGE(prog_name)                                                                           \
    do {                                                                                           \
        fprintf(stderr, "USAGE: %s <NUM_THREADS>", prog_name);                                     \
        exit(1);                                                                                   \
    } while (0)

void solve(double **A, int size, double **ans) {
    double *X, temp;
    int i, j, k, *index;

    X = CreateVec(size);
    *ans = X;
    if (size == 1) {
        X[0] = A[0][1] / A[0][0];
        return;
    }

    index = malloc(size * sizeof(*index));
    for (i = 0; i < size; ++i)
        index[i] = i;

    /*Gaussian elimination*/
    for (k = 0; k < size - 1; ++k) {
        /*Pivoting*/
        temp = 0;
        for (i = k, j = 0; i < size; ++i)
            if (temp < A[index[i]][k] * A[index[i]][k]) {
                temp = A[index[i]][k] * A[index[i]][k];
                j = i;
            }
        if (j != k) /*swap*/ {
            i = index[j];
            index[j] = index[k];
            index[k] = i;
        }
        /*calculating*/
        for (i = k + 1; i < size; ++i) {
            temp = A[index[i]][k] / A[index[k]][k];
            for (j = k; j < size + 1; ++j)
                A[index[i]][j] -= A[index[k]][j] * temp;
        }
    }
    /*Jordan elimination*/
    for (k = size - 1; k > 0; --k) {
        for (i = k - 1; i >= 0; --i) {
            temp = A[index[i]][k] / A[index[k]][k];
            A[index[i]][k] -= temp * A[index[k]][k];
            A[index[i]][size] -= temp * A[index[k]][size];
        }
    }
    /*solution*/
    for (k = 0; k < size; ++k)
        X[k] = A[index[k]][size] / A[index[k]][k];
}

int main(int argc, const char **argv) {
    double **A, *X, start, end;
    int size, num_threads;
    if (argc != 2) USAGE(argv[0]);

    num_threads = atoi(argv[1]);
    if (!num_threads) USAGE(argv[0]);

    Lab3LoadInput(&A, &size);
    GET_TIME(start);
    solve(A, size, &X);
    GET_TIME(end);

    printf("Time taken: %e seconds\n", end - start);
    Lab3SaveOutput(X, size, end - start);
}
