
#include "Lab3IO.h"
#include "timer.h"

#include <stdio.h>
#include <stdlib.h>

int main() {
    double **A, *x, start, end;
    int size;

    Lab3LoadInput(&A, &size);
    GET_TIME(start);

    x = malloc(sizeof(*x) * size);
    printf("Hello world!\n");

    GET_TIME(end);

    Lab3SaveOutput(x, size, end - start);
}
