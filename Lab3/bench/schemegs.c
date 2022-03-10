/**
 * @file schemegs.c
 * @author Patricia Zafra, Charles Ancheta
 * @brief Guided Gaussian and Static Jordan
 * @version 0.1
 * @date 2022-03-06
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "solver.h"
#include "util.h"
#include <omp.h>

/* Gaussian elimination */
void gaussian() {
    double temp;
    int i, j, k;
    int max = 0;

    /* clang-format off */
    for (k = 0; k < size - 1; k++) {
        /* Pivoting */
        /* Use single thread when finding max and swapping */
        #pragma omp single
        {
            max = pivot(k);
            swap(index_vec[k], index_vec[max]);
        }

        /* Elimination */
        /* Parallelize elimination steps */
        #pragma omp for schedule(guided)
        for (i = k + 1; i < size; i++) {
            temp = A[index_vec[i]][k] / A[index_vec[k]][k];
            for (j = k; j < size + 1; j++)
                A[index_vec[i]][j] -= A[index_vec[k]][j] * temp;
        }
    }
    /* clang-format on */
}

/* Jordan elimination */
void jordan() {
    int i, k;

    /* clang-format off */
    for (k = size - 1; k > 0; k--) {
        #pragma omp for schedule(static)
        for (i = k - 1; i >= 0; i--) {
            A[index_vec[i]][size] -=
                A[index_vec[i]][k] / A[index_vec[k]][k] * A[index_vec[k]][size];
            A[index_vec[i]][k] = 0;
        }
    }
    /* clang-format on */
}
