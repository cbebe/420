#include "page_rank.h"
#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>

#define DAMPING_FACTOR 0.85
#define EPSILON 0.00001

#define MAX_ITERATIONS 100

#define INIT_VEC(vec, size) vec = malloc((size) * sizeof *vec);

void init_r() {
    int i;
    INIT_VEC(R, num_nodes + num_pad);
    for (i = 0; i < num_nodes; i++)
        R[i] = 1 / num_nodes;
    // Initialize padding
    for (i = num_nodes; i < num_nodes + num_pad; i++)
        R[i] = 0;
}

void page_rank(int chunksize, int my_rank) {
    int i, j, start, end;
    double *new_R, *contribution, *new_R_l, damp_const;

    num_iterations = 0;

    INIT_VEC(new_R_l, chunksize);
    INIT_VEC(new_R, num_nodes + num_pad);
    INIT_VEC(contribution, num_nodes + num_pad);

    start = chunksize * my_rank;
    end = start + chunksize;

    for (i = 0; i < num_nodes; i++)
        contribution[i] = R[i] / nodes[i].num_out_links * DAMPING_FACTOR;

    damp_const = (1.0 - DAMPING_FACTOR) / num_nodes;

    while (num_iterations < MAX_ITERATIONS) {
        num_iterations++;
        for (i = start; i < end; i++) {
            new_R_l[i - start] = 0;
            if (i >= num_nodes) continue; // Padding zero
            for (j = 0; j < nodes[i].num_in_links; j++)
                new_R_l[i - start] += contribution[nodes[i].inlinks[j]];
            new_R_l[i - start] += damp_const;
        }

        MPI_Allgather(new_R_l, chunksize, MPI_DOUBLE, new_R, chunksize, MPI_DOUBLE, MPI_COMM_WORLD);

        if (rel_error(new_R, R, num_nodes) < EPSILON) return;

        for (i = 0; i < num_nodes; i++) {
            contribution[i] = new_R[i] / nodes[i].num_out_links * DAMPING_FACTOR;
        }

        vec_cp(new_R, R, num_nodes);
    }

    fprintf(stderr, "Failed to converge after %d iterations.\n", num_iterations);
    exit(0);
}
