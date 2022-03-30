#include "page_rank.h"
#include <mpi.h>
#include <stdlib.h>

#define DAMPING_FACTOR 0.85
#define EPSILON 0.00001

#define INIT_VEC(vec, size) vec = malloc(size * sizeof *vec);

void init_r() {
    int i;
    INIT_VEC(R, num_nodes);
    for (i = 0; i < num_nodes; i++)
        R[i] = 1 / num_nodes;
}

void page_rank(int chunksize, int my_rank) {
    int i, j, start, end;
    double *new_R, *contribution, damp_const;
    num_iterations = 0;
    INIT_VEC(new_R, num_nodes);
    INIT_VEC(contribution, num_nodes);
    start = chunksize * my_rank;
    end = start + chunksize;

    for (i = start; i < end; i++)
        contribution[i] = R[i] / nodes[i].num_out_links * DAMPING_FACTOR;

    damp_const = (1.0 - DAMPING_FACTOR) / num_nodes;

    while (1) {
        num_iterations++;
        for (i = start; i < end; ++i) {
            new_R[i] = 0;
            for (j = 0; j < nodes[i].num_in_links; ++j)
                new_R[i] += contribution[nodes[i].inlinks[j]];
            new_R[i] += damp_const;
        }

        MPI_Allgather(new_R + start, chunksize, MPI_DOUBLE, new_R, chunksize, MPI_DOUBLE,
                      MPI_COMM_WORLD);

        if (rel_error(new_R, R, num_nodes) < EPSILON) break;

        for (i = 0; i < num_nodes; ++i) {
            contribution[i] = new_R[i] / nodes[i].num_out_links * DAMPING_FACTOR;
        }

        vec_cp(new_R, R, chunksize);
    }
}
