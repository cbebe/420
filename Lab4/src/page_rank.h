#ifndef _SRC_PAGE_RANK_H_
#define _SRC_PAGE_RANK_H_

#define LAB4_EXTEND
#include "Lab4_IO.h"

extern int num_nodes, num_iterations, num_pad;
extern struct node *nodes;
extern double *R;

/**
 * @brief Initializes the R vector with the initial probability
 *
 * Global inputs:
 *   num_nodes - total number of nodes
 *
 * Global outputs:
 *   R - vector of initial probabilities
 */
void init_r();

/**
 * @brief Executes the PageRank algorithm on `nodes`
 *
 * @param chunksize
 * @param my_rank
 *
 * Global inputs:
 *   nodes - vector of nodes
 *   num_nodes - total number of nodes
 *
 * Global outputs:
 *   R - vector of final probabilities
 *   num_iterations - number of iterations before converging
 */
void page_rank(int chunksize, int my_rank);

#endif
