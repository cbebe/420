#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lab1_IO.h"
#include "timer.h"

#define RESTORE "\033[0m"
#define RED "\033[01;31m"
#define GREEN "\033[01;32m"
#define YELLOW "\033[01;33m"
#define BLUE "\033[01;34m"
#define MAGENTA "\033[00;35m"
#define PURPLE "\033[01;35m"

#define log_str(str, colour) printf("%s%s%s", colour, str, RESTORE)
#define log_int(num, colour) printf("%s%d%s", colour, num, RESTORE)

int **A;
int **B;
int n;
int **C;

void say_hello()
{
    log_str("Hello ", RED);
    log_str("ECE ", YELLOW);
    log_int(420, GREEN);
    log_str(" ", RESTORE);
    log_str("world\n", BLUE);
}

void init_result_matrix()
{
    int i;
    C = malloc(n * sizeof(int *));
    for (i = 0; i < n; i++)
        C[i] = malloc(n * sizeof(int));
}

void multiply()
{
    int i, j, k;
    /* serial implementation 🥴 */
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++)
        {
            C[i][j] = 0;
            for (k = 0; k < n; k++)
                C[i][j] += A[i][k] * B[k][j];
        }
}

int main()
{
    double start, end;
    say_hello();
    Lab1_loadinput(&A, &B, &n);
    init_result_matrix();
    GET_TIME(start)
    multiply();
    GET_TIME(end)
    Lab1_saveoutput(C, &n, end - start);

    return 0;
}
