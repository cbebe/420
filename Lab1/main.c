#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

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

int n, thread_count;
int **A, **B, **C;

void init_result_matrix();

void *multiply_thread(void* rank)
{
  /*
  Multiplies the matrices A and B into matrix C
  📋 TODO: Implement using shared memory and pthreads
  */
  long my_rank;
  int i, j, k;
  my_rank = (long) rank;
  /* serial implementation 🥴 */
  for (i = 0; i < n; i++)
    for (j = 0; j < n; j++)
    {
      C[i][j] = 0;
      for (k = 0; k < n; k++)
        C[i][j] += A[i][k] * B[k][j];
    }

  return NULL;
}

void multiply()
{
  /*
  Splits the task between `thread_count` threads
  */
  long thread;
  pthread_t* thread_handles;

  thread_handles = malloc(thread_count*sizeof(pthread_t));

  for (thread = 0; thread < thread_count; ++thread)
    pthread_create(&thread_handles[thread], NULL, multiply_thread, (void*) thread);

  for (thread = 0; thread < thread_count; ++thread)
    pthread_join(thread_handles[thread], NULL);
}

void print_usage(const char* prog_name)
{
   fprintf(stderr, "USAGE: %s <thread_count>\n", prog_name);
   exit(1);
}

int main(int argc, const char **argv)
{
  double start, end, total;

  if (argc != 2) print_usage(argv[0]);
  thread_count = atoi(argv[1]);

#ifdef DEV
  say_hello();
  log_str("Matrix Multiplication:\n", BLUE);
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

