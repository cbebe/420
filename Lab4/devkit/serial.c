/**
 * @file serial.c
 * @author Charles Ancheta, Patricia Zafra
 * @brief Entrypoint for Lab 4
 * @version 0.1
 * @date 2022-03-18
 *
 * @copyright Copyright (c) 2022
 *
 */
#define LAB4_EXTEND
#include "../src/Lab4_IO.h"

#include "../src/timer.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define DAMPING_FACTOR 0.85
#define EPSILON 0.00001

#define MAX_ITERATIONS 100

#define INIT_VEC(vec, size) vec = malloc(size * sizeof *vec);

int num_nodes, num_iterations;
double *R;
struct node *nodes;

void init_r() {
    int i;
    INIT_VEC(R, num_nodes);
    for (i = 0; i < num_nodes; i++)
        R[i] = 1 / num_nodes;
}

void page_rank(int chunksize, int my_rank) {
    int i, j;
    double *new_R, *contribution, damp_const;
    num_iterations = 0;
    INIT_VEC(new_R, num_nodes);
    INIT_VEC(contribution, num_nodes);

    for (i = 0; i < num_nodes; i++)
        contribution[i] = R[i] / nodes[i].num_out_links * DAMPING_FACTOR;

    damp_const = (1.0 - DAMPING_FACTOR) / num_nodes;

    while (num_iterations < MAX_ITERATIONS) {
        num_iterations++;
        for (i = 0; i < num_nodes; i++) {
            new_R[i] = 0;
            for (j = 0; j < nodes[i].num_in_links; j++)
                new_R[i] += contribution[nodes[i].inlinks[j]];
            new_R[i] += damp_const;
        }

        if (rel_error(new_R, R, num_nodes) < EPSILON) return;

        for (i = 0; i < num_nodes; i++) {
            contribution[i] = new_R[i] / nodes[i].num_out_links * DAMPING_FACTOR;
        }

        vec_cp(new_R, R, num_nodes);
    }

    fprintf(stderr, "Failed to converge after %d iterations.\n", num_iterations);
    exit(0);
}

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
    int chunksize, comm_sz, my_rank = 0;

    num_nodes = get_num_nodes();
    chunksize = num_nodes;

    // TODO: check if product of chunksize & comm_sz is equal to num_nodes

    GET_TIME(start);
    if (node_init(&nodes, 0, num_nodes)) return 254;
    GET_TIME(end);
    printf("Loading graph took %f seconds...\n", end - start);

    init_r();

    GET_TIME(start);
    page_rank(chunksize, my_rank);
    GET_TIME(end);

    if (my_rank == 0) {
        total = end - start;
        node_destroy(nodes, chunksize);
        printf("Elapsed time: %f, number of iterations: %d\n", total, num_iterations);
        Lab4_saveoutput(R, num_nodes, total);
        free(R);
    }

    return 0;
}
