
#ifndef _UTIL_H_
#define _UTIL_H_

#include <math.h>

extern double **A;
extern int *index_vec, size, thread_count;

/**
 * @brief Find the row that has the maximum absolute value of the element in the kth column
 *
 * @param k the row k in matrix A
 * @return index of the row with maximum
 */
int pivot(int k) {
    int col = k;
    int max = k;

    for (k = 0; k < size; k++) {
        if (fabs(A[index_vec[k]][col]) > A[index_vec[max]][col]) max = k;
    }
    return max;
}

/**
 * @brief Swap two indicies
 *
 * @param index_1
 * @param index_2
 */
void swap(int index_1, int index_2) {
    int temp = index_1;
    index_1 = index_2;
    index_2 = temp;
}

#endif
