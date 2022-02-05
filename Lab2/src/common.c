/**
 * @file common.c
 * @brief Instructor-provided common functionality needed by the server
 *
 * This needed to be declared in an actual source file instead of being a header-only library to
 * avoid conflicting includes
 */
#include "common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int ParseMsg(char *msg, ClientRequest *req) {
    char *token;
    token = strsep(&msg, "-");
    req->pos = atoi(token);
    token = strsep(&msg, "-");
    req->is_read = atoi(token);
    token = strsep(&msg, "-");
    memcpy(req->msg, token, strlen(token) + 1);
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

void saveTimes(double *time, int length, const char *fileName) {
    FILE *op;
    int i;
    double elapsedTime = 0;
    for (i = 0; i < length; ++i) {
        elapsedTime += time[i];
    }
    elapsedTime /= length;
    if ((op = fopen(fileName, "a+")) == NULL) {
        fprintf(stderr, "Error opening the output file: %s.\n", fileName);
        exit(1);
    }
    fprintf(op, "%e\n", elapsedTime);
    fclose(op);
}
