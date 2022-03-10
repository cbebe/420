/**
 * @file schemedd.c
 * @author Patricia Zafra, Charles Ancheta
 * @brief Dynamic Gaussian and Dynamic Jordan
 * @version 0.1
 * @date 2022-03-06
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "solver.h"
#include "util.h"
#include <omp.h>

int max = 0;

#define IDX_MAT(row, col) (A[index_vec[row]][col])
#define MAX_IDX(a, b, col) fabs(IDX_MAT(a, col)) > IDX_MAT(b, col)

void find_max(int k) {
    int local_max = k;
    int col = k;
    int id = omp_get_thread_num();
    int local_size = size / thread_count;

    for (k = local_size * id; k < (local_size + 1) * id; k++) {
        if (MAX_IDX(k, local_max, col)) local_max = k;
    }

#pragma omp critical
    if (MAX_IDX(local_max, max, col)) max = local_max;
}

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
            max = k;
        }
        find_max(k);
        #pragma omp single
        {
            swap(index_vec[k], index_vec[max]);
        }

        /* Elimination */
        /* Parallelize elimination steps */
        #pragma omp for schedule(dynamic)
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
        #pragma omp for schedule(dynamic)
        for (i = k - 1; i >= 0; i--) {
            A[index_vec[i]][size] -=
                A[index_vec[i]][k] / A[index_vec[k]][k] * A[index_vec[k]][size];
            A[index_vec[i]][k] = 0;
        }
    }
    /* clang-format on */
}
