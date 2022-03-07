#include "Lab3IO.h"
#include "solver.h"
#include "timer.h"

#include <stdio.h>
#include <stdlib.h>

#define USAGE(prog_name)                                                                           \
    do {                                                                                           \
        fprintf(stderr, "USAGE: %s <NUM_THREADS>\n", prog_name);                                   \
        exit(1);                                                                                   \
    } while (0)

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
void solve() {
    int i;

    /* Create answer vector and early return for basic case where size == 1 */
    X = CreateVec(size);
    if (size == 1) {
        X[0] = A[0][1] / A[0][0];
        return;
    }

    /* Create index vector */
    index_vec = malloc(size * sizeof(*index_vec));
    for (i = 0; i < size; ++i)
        index_vec[i] = i;

    gaussian();
    jordan();

    /* solution */
    for (i = 0; i < size; ++i)
        X[i] = A[index_vec[i]][size] / A[index_vec[i]][i];
}

int main(int argc, const char **argv) {
    double start, end;
    if (argc != 2) USAGE(argv[0]);

    num_threads = atoi(argv[1]);
    if (!num_threads) USAGE(argv[0]);

    Lab3LoadInput(&A, &size);
    GET_TIME(start);
    solve(A, size);
    GET_TIME(end);

    printf("Time taken: %e seconds\n", end - start);
    Lab3SaveOutput(X, size, end - start);
    DestroyVec(X);
    DestroyMat(A, size);

    return 0;
}
