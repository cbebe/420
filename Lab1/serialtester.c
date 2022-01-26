/*
Test the result stored in the "data_output" by a serial version of calculation

-----
Compiling:
    "lab1_IO.c" should be included, like
    > gcc serialtester.c lab1_IO.c -o serialtester


*/

#include "lab1_IO.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

#ifdef DEV
#include "dev.h"
#endif

/* Extracted from timer.h in the Development kit */
#define GET_TIME(now)                                                          \
    {                                                                          \
        struct timeval t;                                                      \
        gettimeofday(&t, NULL);                                                \
        now = t.tv_sec + t.tv_usec / 1000000.0;                                \
    }

int main(int argc, char *argv[]) {

    int n;
    int i, j, k;
    FILE *fp;
    int temp, flag = 1;
    int **A;
    int **B;
    int **C;
    double start, end, p_time;

    Lab1_loadinput(&A, &B, &n);

#ifdef DEV
    say_hello();
    log_str("Matrix Multiplication Testing...\n", PURPLE);
#endif
    C = malloc(n * sizeof(int *));
    for (i = 0; i < n; i++)
        C[i] = malloc(n * sizeof(int));

    GET_TIME(start);
    /*Calculating*/
    for (i = 0; i < n; i++)
        for (j = 0; j < n; j++) {
            C[i][j] = 0;
            for (k = 0; k < n; k++)
                C[i][j] += A[i][k] * B[k][j];
        }
    GET_TIME(end);
    /*Testing*/
    if ((fp = fopen("data_output", "r")) == NULL) {
        printf("Fail to load the output data.\n");
        return 1;
    }
    fscanf(fp, "%d\n\n", &temp);
    if (temp != n) {
        printf("Error, the output dimension did not match the input.\n");
        return 2;
    }
    for (i = 0; i < n && flag == 1; i++)
        for (j = 0; j < n && flag == 1; j++) {
            fscanf(fp, "%d", &temp);
            if (temp != C[i][j]) flag = 0;
        }
    if (flag == 1) {
#ifdef DEV
        log_str("The result is correct!\n", GREEN);
        happy_pepe();
#else
        printf("The result is correct!\n");
#endif
        fscanf(fp, "\n%lf\n", &p_time);
        printf("Serial: %f, Parallel: %f, Speedup: %f\n", end - start, p_time,
               (end - start) / p_time);
    } else {
#ifdef DEV
        log_str("The result is wrong.\n", RED);
        sad_pepe();
#else
        printf("The result is wrong.\n");
#endif
    }

    for (i = 0; i < n; i++) {
        free(A[i]);
        free(B[i]);
        free(C[i]);
    }
    free(A);
    free(B);
    free(C);

#ifdef DEV
    say_goodbye();
#endif
    return !flag;
}
