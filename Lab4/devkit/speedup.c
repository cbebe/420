#include <stdio.h>
#include <stdlib.h>

#ifdef NO_COLOR

#define RESTORE ""
#define RED ""
#define GREEN ""
#define YELLOW ""

#else

#define RESTORE "\033[0m"
#define RED "\033[01;31m"
#define GREEN "\033[01;32m"
#define YELLOW "\033[01;33m"

#endif

#define GET_COLOUR(speedup) (speedup < 0.95 ? RED : speedup > 2 ? GREEN : YELLOW)

int main(int argc, const char **argv) {
    int num;
    double serial, parallel, speedup;
    if (argc != 4) {
        fprintf(stderr, "USAGE: %s <NUM_NODES> <SERIAL_TIME> <PARALLEL_TIME>\n", argv[0]);
        exit(1);
    }
    sscanf(argv[1], "%d", &num);
    sscanf(argv[2], "%lf", &serial);
    sscanf(argv[3], "%lf", &parallel);

    speedup = serial / parallel;

    printf("| %5d | %02.4f |   %02.4f |  %s%02.4f%s |\n", num, serial, parallel,
           GET_COLOUR(speedup), speedup, RESTORE);
    return 0;
}