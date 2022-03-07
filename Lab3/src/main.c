#include "Lab3IO.h"
#include "solver.h"
#include "timer.h"

#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

void usage(const char *prog_name) {
    fprintf(stderr, "USAGE: %s <NUM_THREADS>\n", prog_name);
    exit(1);
}

double **A, *X;
/* My compiler complains about redefining the built-in function index as a non-function so we had to
 * rename this */
int *index_vec, size, num_threads;

/* WARNING: the code that follows will make you cry;
 *          a safety pig is provided below for your benefit
 *                           _
 *   _._ _..._ .-',     _.._(`))
 *  '-. `     '  /-._.-'    ',/
 *     )         \            '.
 *    / _    _    |             \
 *   |  a    a    /              |
 *   \   .-.                     ;
 *    '-('' ).-'       ,'       ;
 *       '-;           |      .'
 *          \           \    /
 *          | 7  .__  _.-\   \
 *          | |  |  ``/  /`  /
 *         /,_|  |   /,_/   /
 *            /,_/      '`-'
 */
double solve() {
    int i;
    double start, end;

    GET_TIME(start);
    /* Create answer vector and early return for basic case where size == 1 */
    X = CreateVec(size);
    if (size == 1) {
        X[0] = A[0][1] / A[0][0];
        GET_TIME(end);
        return end - start;
    }

    /* Create index vector */
    index_vec = malloc(size * sizeof(*index_vec));
#pragma omp parallel for num_threads(num_threads)
    for (i = 0; i < size; ++i)
        index_vec[i] = i;

    gaussian();
    jordan();

/* solution */
#pragma omp parallel for num_threads(num_threads)
    for (i = 0; i < size; ++i)
        X[i] = A[index_vec[i]][size] / A[index_vec[i]][i];
    GET_TIME(end);

    return end - start;
}

int main(int argc, const char **argv) {
    double time;

    if (argc != 2) usage(argv[0]);
    num_threads = atoi(argv[1]);
    if (!num_threads) usage(argv[0]);

    Lab3LoadInput(&A, &size);
    time = solve();
    printf("Time taken: %e seconds\n", time);
    Lab3SaveOutput(X, size, time);
    DestroyVec(X);
    DestroyMat(A, size);

    return 0;
}
