#include <errno.h>
#include <stdio.h>
#include <string.h>

int main() {
    FILE *times;
    const int len = 16;
    char buffer[len], *time_str, *name;
    double baseline, time;
    times = fopen("latest_times.tsv", "r");
    if (times == NULL) {
        perror("Error opening times file");
        return errno;
    }

    while (fgets(buffer, len, times)) {
        if (strncmp(buffer, "\n", 1) == 0) break;
        name = strtok(buffer, "\t");
        time_str = strtok(NULL, "\t");
        if (strncmp(name, "00", 2) == 0) {
            sscanf(time_str, "%f\n", &baseline);
            printf("Baseline: %f seconds\n", baseline);
        } else {
            printf("%s: %fx speedup\n", name, baseline / time);
        }
    }
}