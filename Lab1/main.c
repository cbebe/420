#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lab1_IO.h"

#include <sys/time.h>

/* Extracted from timer.h in the Development kit */
#define GET_TIME(now)                       \
  {                                         \
    struct timeval t;                       \
    gettimeofday(&t, NULL);                 \
    now = t.tv_sec + t.tv_usec / 1000000.0; \
  }

#ifdef DEV
#include "dev.h"
#endif

int **A;
int **B;
int n;
int **C;

void init_result_matrix();

void multiply()
{
  /*
  Multiplies the matrices A and B into matrix C
  📋 TODO: Implement using shared memory and pthreads
  */
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

int main(int argc, const char **argv)
{
  double start, end, total;
#ifdef DEV
  say_hello();
#endif
  Lab1_loadinput(&A, &B, &n);
  init_result_matrix();
  GET_TIME(start)
  multiply();
  GET_TIME(end)
  total = end - start;
#ifdef DEV
  print_total_time(total);
  say_goodbye();
#endif
  Lab1_saveoutput(C, &n, total);

  return 0;
}

void init_result_matrix()
{
  /*
  Allocate memory for the result matrix
  */
  int i;
  C = malloc(n * sizeof(int *));
  for (i = 0; i < n; i++)
    C[i] = malloc(n * sizeof(int));
}
