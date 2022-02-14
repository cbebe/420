/**
 * @file mean.c
 * @author Charles Ancheta, Patricia Zafra
 * @brief Reads a file of doubles line by line and outputs the mean
 * @version 0.1
 * @date 2022-02-02
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Since the files should only contain doubles,
 * the lines shouldn't really exceed ~16 characters.
 * But of course we're trying to be safe */
#define MAX_LEN 256
/* Maximum number of entries in the file */
#define NUM_ENTRIES 100

int main(int argc, const char **argv) {
    double time, *times, total = 0;
    char buf[MAX_LEN];
    int numTimes = 0, i;
    FILE *infile;

    if (argc != 2) {
        fprintf(stderr, "usage: %s <filename>\n", argv[0]);
        return 1;
    }

    if ((infile = fopen(argv[1], "r")) == NULL) {
        fprintf(stderr, "cannot open file %s\n", argv[1]);
        return 1;
    }

    times = malloc(NUM_ENTRIES * sizeof(*times));
    while (fgets(buf, MAX_LEN, infile) && numTimes <= NUM_ENTRIES) {
        sscanf(buf, "%lf", &time);
        times[numTimes++] = time;
    }

    for (i = 0; i < numTimes; ++i)
        total += times[i];

    total /= numTimes;
    printf("%e\n", total);
    free(times);
    fclose(infile);

    return 0;
}
