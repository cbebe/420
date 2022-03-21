#define _GNU_SOURCE // to use getline
#include <stdio.h>
#include <stdlib.h>

int main() {
    int iterations = 0;
    size_t bufsize = 16;
    double time, total = 0;
    char *buffer;

    buffer = malloc(bufsize * sizeof *buffer);
    while (getline(&buffer, &bufsize, stdin) != -1) {
        ++iterations;
        sscanf(buffer, "%lf\n", &time);
        total += time;
    }

    if (iterations) {
        printf("%f\n", total / iterations);
    }

    return 0;
}