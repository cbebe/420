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

#define BUF_LEN 32

/* for setting the baseline to compare against */
double baseline = 1;

/* holds the split tokens */
char *time_str, *thread_str, *name;

/* store best scheme and thread count */
char max_name[3] = {0, 0, 0};
int best_threads = 1;
double max_speedup = 1, min_time = 1000;

void split_line(char *buffer);
void set_baseline(int *first);
void print_best();
void process_scheme();

int main() {
    FILE *times;
    int len = BUF_LEN, first = 1;
    char buffer[BUF_LEN];
    times = fopen("latest_times.tsv", "r");
    if (times == NULL) {
        perror("Error opening times file");
        return errno;
    }

    while (fgets(buffer, len, times)) {
        if (strncmp(buffer, "\n", 1) == 0) break;
        split_line(buffer);

        if (strncmp(name, "00", 2) == 0)
            set_baseline(&first);
        else
            process_scheme();
    }

    print_best();

    return 0;
}

void set_baseline(int *first) {
    if (!*first) return;
    sscanf(time_str, "%lf\n", &baseline);
    printf("Baseline: %f seconds\n", baseline);
    *first = 0;
}

void split_line(char *buffer) {
    name = strtok(buffer, "\t");
    time_str = strtok(NULL, "\t");
    thread_str = strtok(NULL, "\t");
}

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

void print_best() {
    printf("\nMax speedup: %s Gaussian and %s Jordan\n", get_sched(max_name[0]),
           get_sched(max_name[1]));
    printf("%.2fx speedup (%f seconds with %d threads)\n", max_speedup, min_time, best_threads);
}

void process_scheme() {
    int num_threads;
    double time, speedup;
    sscanf(time_str, "%lf\n", &time);
    sscanf(thread_str, "%d\n", &num_threads);
    speedup = baseline / time;
    printf("%s - %d thread(s): %.2fx speedup (%f seconds)\n", name, num_threads, speedup, time);
    if (speedup > max_speedup) {
        max_speedup = speedup;
        min_time = time;
        best_threads = num_threads;
        strncpy(max_name, name, 2);
    }
}
