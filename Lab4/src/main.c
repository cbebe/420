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

#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#define DAMPING_FACTOR 0.85
#define EPSILON 1E-5

#define GET_TIME(now)                                                                              \
    {                                                                                              \
        struct timeval t;                                                                          \
        gettimeofday(&t, NULL);                                                                    \
        now = t.tv_sec + t.tv_usec / 1000000.0;                                                    \
    }

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
    int num_nodes, i;
    struct node *nodes;
    double start, end, *R;
    num_nodes = get_num_nodes();
    node_init(&nodes, 0, num_nodes);

    R = malloc(num_nodes * sizeof *R);
    for (i = 0; i < num_nodes; i++)
        R[i] = 0;

    GET_TIME(start);

    // Do something with nodes here

    GET_TIME(end);
    node_destroy(nodes, num_nodes);
    Lab4_saveoutput(R, num_nodes, end - start);
    return 0;
}