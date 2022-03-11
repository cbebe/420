/**
 * @file solver.h
 * @author Patricia Zafra, Charles Ancheta
 * @brief Functions for eliminating variables in the A matrix
 * @version 0.1
 * @date 2022-03-10
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef _SRC_SOLVER_H_
#define _SRC_SOLVER_H_

extern double **A;
extern int *index_vec, size, thread_count;

/**
 * @brief Perform Jordan elimination on the A matrix
 */
void jordan();

/**
 * @brief Perform Gaussian elimination on the A matrix
 */
void gaussian();

#endif
