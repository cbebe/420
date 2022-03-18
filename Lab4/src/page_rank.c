#include "page_rank.h"
#include <stdlib.h>

#define DAMPING_FACTOR 0.85
#define EPSILON 0.00001

#define INIT_VEC(vec) vec = malloc(num_nodes * sizeof *vec);

void init_r() {
    int i;
    INIT_VEC(R);
    for (i = 0; i < num_nodes; i++)
        R[i] = 1 / num_nodes;
}

void page_rank() {
    int i, j, done = 0;
    double *new_R, *contribution, damp_const;
    num_iterations = 0;
    INIT_VEC(new_R);
    INIT_VEC(contribution);

    for (i = 0; i < num_nodes; i++)
        contribution[i] = R[i] / nodes[i].num_out_links * DAMPING_FACTOR;

    damp_const = (1.0 - DAMPING_FACTOR) / num_nodes;

    while (!done) {
        num_iterations++;
        for (i = 0; i < num_nodes; ++i) {
            new_R[i] = 0;
            for (j = 0; j < nodes[i].num_in_links; ++j)
                new_R[i] += contribution[nodes[i].inlinks[j]];
            new_R[i] += damp_const;
        }
        for (i = 0; i < num_nodes; ++i) {
            contribution[i] = new_R[i] / nodes[i].num_out_links * DAMPING_FACTOR;
        }

        if (rel_error(new_R, R, num_nodes) < EPSILON) done = 1;
        vec_cp(new_R, R, num_nodes);
    }
}