#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    while (fgets(buf, MAX_LEN, infile)) {
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
