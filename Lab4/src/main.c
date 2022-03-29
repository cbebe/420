/**
 * @file main.c
 * @author Charles Ancheta, Patricia Zafra
 * @brief Entrypoint for Lab 4
 * @version 0.1
 * @date 2022-03-18
 *
 * @copyright Copyright (c) 2022
 *
 */
#define LAB4_EXTEND
#include "Lab4_IO.h"

#include "page_rank.h"
#include "timer.h"

#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int num_nodes, num_iterations;
double *R;
struct node *nodes;

/**
 * @brief Get the number of nodes
 */
int get_num_nodes() {
    int num_nodes;
    FILE *fp = fopen("data_input_meta", "r");
    fscanf(fp, "%d\n", &num_nodes);
    fclose(fp);
    return num_nodes;
}

int main() {
    double start, end, total;
    int chunksize, lower, upper;
    int comm_sz, my_rank;

    /* Initialize MPI */
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    /* Divide the work and get upper and lower bounds */
    chunksize = num_nodes / comm_sz;
    if (comm_sz * chunksize != num_nodes) chunksize += 1; /* Account for non-divisible case */
    lower = my_rank * chunksize;
    upper = lower + chunksize;

    num_nodes = get_num_nodes();

    GET_TIME(start);
    if (node_init(&nodes, lower, upper)) return 254;
    GET_TIME(end);
    printf("Loading graph took %f seconds...\n", end - start);

    init_r();

    GET_TIME(start);
    page_rank(chunksize);
    GET_TIME(end);

    MPI_Finalize();

    if (my_rank == 0) {
        total = end - start;
        node_destroy(nodes, chunksize);
        printf("Elapsed time: %f, number of iterations: %d\n", total, num_iterations);
        Lab4_saveoutput(R, num_nodes, total);
        free(R);
    }

    return 0;
}
