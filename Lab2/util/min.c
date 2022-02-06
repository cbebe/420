/**
 * @file mean.c
 * @author Charles Ancheta, Patricia Zafra, Michelle Lee
 * @brief Reads a file of doubles line by line and outputs the minimum
 * @version 0.1
 * @date 2022-02-02
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Since the files should only contain doubles,
 * the lines shouldn't really exceed ~16 characters.
 * But of course we're trying to be safe */
#define MAX_LEN 256

int main(int argc, const char **argv) {
    double time, minimum = INFINITY;
    char buf[MAX_LEN];
    FILE *infile;

    if (argc != 2) {
        fprintf(stderr, "usage: %s <filename>\n", argv[0]);
        return 1;
    }

    if ((infile = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "cannot open file %s\n", argv[1]);
        return 1;
    }

    while (fgets(buf, MAX_LEN, infile)) {
        sscanf(buf, "%lf", &time);
        if (time < minimum) minimum = time;
    }

    printf("%e\n", minimum);
    fclose(infile);

    return 0;
}
