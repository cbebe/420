#ifndef _SRC_SOLVER_H_
#define _SRC_SOLVER_H_

extern double **A;
extern int *index_vec, size, num_threads;

/**
 * @brief Perform Jordan elimination on the A matrix
 */
void jordan();

/**
 * @brief Perform Gaussian elimination on the A matrix
 */
void gaussian();

#endif
