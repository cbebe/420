/**
 * @file schemess.c
 * @author Patricia Zafra, Charles Ancheta
 * @brief Static Gaussian and Static Jordan
 * @version 0.1
 * @date 2022-03-06
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "solver.h"
#include <omp.h>

#define SWAP(a, b)                                                                                 \
    do {                                                                                           \
        int temp = a;                                                                              \
        a = b;                                                                                     \
        b = temp;                                                                                  \
    } while (0)

/* Gaussian elimination */
void gaussian() {
    double temp;
    int i, j, k;

    for (k = 0; k < size - 1; ++k) {
        /* Pivoting */
        temp = j = 0;
#pragma omp parallel for num_threads(thread_count) schedule(static)
        for (i = k; i < size; ++i)
            if (temp < A[index_vec[i]][k] * A[index_vec[i]][k]) {
                temp = A[index_vec[i]][k] * A[index_vec[i]][k];
                j = i;
            }

        if (j != k) SWAP(index_vec[j], index_vec[k]);

            /* calculating */
#pragma omp parallel for num_threads(thread_count) schedule(static)
        for (i = k + 1; i < size; ++i) {
            temp = A[index_vec[i]][k] / A[index_vec[k]][k];
            for (j = k; j < size + 1; ++j)
                A[index_vec[i]][j] -= A[index_vec[k]][j] * temp;
        }
    }
}

/* Jordan elimination */
void jordan() {
    int i, k;
    double temp;
    for (k = size - 1; k > 0; --k) {
#pragma omp parallel for num_threads(thread_count) schedule(static)
        for (i = k - 1; i >= 0; --i) {
            temp = A[index_vec[i]][k] / A[index_vec[k]][k];
            A[index_vec[i]][k] -= temp * A[index_vec[k]][k];
            A[index_vec[i]][size] -= temp * A[index_vec[k]][size];
        }
    }
}
