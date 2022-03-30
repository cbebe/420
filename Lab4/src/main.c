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

int num_nodes, num_iterations, num_pad = 0;
double *R;
struct node *nodes;

/**
 * @brief Get the number of nodes
 */
int get_num_nodes() {
    int num_nodes;
    FILE *fp = fopen("data_input_meta", "r");
    if (fp == NULL) {
        fprintf(stderr, "Error opening file\n");
        exit(1);
    }
    fscanf(fp, "%d\n", &num_nodes);
    fclose(fp);
    return num_nodes;
}

int main() {
    double start, end, total;
    int chunksize, comm_sz, my_rank, remainder;

    num_nodes = get_num_nodes();

    /* Initialize MPI */
    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    remainder = num_nodes % comm_sz;
    if (remainder != 0) num_pad = comm_sz - remainder;
    chunksize = (num_nodes + num_pad) / comm_sz;

    GET_TIME(start);
    if (node_init(&nodes, 0, num_nodes)) return 254;
    GET_TIME(end);
    printf("Loading graph took %f seconds...\n", end - start);

    init_r();

    GET_TIME(start);
    page_rank(chunksize, my_rank);
    GET_TIME(end);

    MPI_Finalize();

    /* Cleanup */
    if (my_rank == 0) {
        total = end - start;
        node_destroy(nodes, chunksize);
        printf("Elapsed time: %f, number of iterations: %d\n", total, num_iterations);
        Lab4_saveoutput(R, num_nodes, total);
        free(R);
    }

    return 0;
}
