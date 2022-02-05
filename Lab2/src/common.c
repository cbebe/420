#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int ParseMsg(char *msg, ClientRequest *rqst) {
    char *token;
    token = strsep(&msg, "-");
    rqst->pos = atoi(token);
    token = strsep(&msg, "-");
    rqst->is_read = atoi(token);
    token = strsep(&msg, "-");
    memcpy(rqst->msg, token, strlen(token) + 1);
    return 0;
}

void setContent(char *src, int pos, char **theArray) {
    int i;
    char *dst = theArray[pos];
    int length = MIN(strlen(src) + 1, COM_BUFF_SIZE);
    usleep(ART_DELAY);
    for (i = 0; i < length; ++i) {
        dst[i] = src[i];
    }
}

void getContent(char *dst, int pos, char **theArray) {
    int i;
    char *src = theArray[pos];
    int length = MIN(strlen(src) + 1, COM_BUFF_SIZE);
    usleep(ART_DELAY);
    for (i = length - 1; i >= 0; --i) {
        dst[i] = src[i];
    }
}

/* Function to save the measured time */
/* Input: time: pointer to the array that store the time for each request */
/*        length: length of the time */
void saveTimes(double *time, int length, const char *fileName) {
    FILE *op;
    int i;
    double elapsed_time = 0;
    for (i = 0; i < length; ++i) {
        elapsed_time += time[i];
    }
    elapsed_time /= length;
    if ((op = fopen(fileName, "a+")) == NULL) {
        fprintf(stderr, "Error opening the output file: %s.\n", fileName);
        exit(1);
    }
    fprintf(op, "%e\n", elapsed_time);
    fclose(op);
}
