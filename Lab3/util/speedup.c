/**
 * @file speedup.c
 * @author Patricia Zafra, Charles Ancheta
 * @brief Measures the speedup between each parallel implementation
 * @version 0.1
 * @date 2022-03-10
 *
 * @copyright Copyright (c) 2022
 *
 */
#include <errno.h>
#include <stdio.h>
#include <string.h>

#define BUF_LEN 16

inline const char *get_sched(char s) {
    switch (s) {
    case 's':
        return "Static";
    case 'd':
        return "Dynamic";
    case 'g':
        return "Guided";
    default:
        return "Unknown";
    }
}

int main() {
    FILE *times;
    const int len = BUF_LEN;
    char buffer[BUF_LEN], *time_str, *name, max_name[3] = {0, 0, 0};
    double baseline, time, speedup, max = 1;
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
            sscanf(time_str, "%lf\n", &baseline);
            printf("Baseline: %f seconds\n", baseline);
        } else {
            sscanf(time_str, "%lf\n", &time);
            speedup = baseline / time;
            printf("%s: %.2fx speedup (%f seconds)\n", name, speedup, time);
            if (speedup > max) {
                max = speedup;
                strncpy(max_name, name, 2);
            }
        }
    }

    printf("Max speedup: %s Gaussian and %s Jordan\n", get_sched(max_name[0]),
           get_sched(max_name[1]));

    return 0;
}