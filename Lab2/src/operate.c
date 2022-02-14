/**
 * @file operate.c
 * @author Charles Ancheta, Patricia Zafra
 * @brief Provides an interface for the server to operate on the protected data structure
 * @version 0.1
 * @date 2022-02-02
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "operate.h"
#include "common.h"
#include "timer.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

static char **strArray;
static int arrSize;

void *HandleRequest(void *args) {
    double start, end, *result;
    int clientFd = (long)args;
    char str[128];
    ClientRequest req;

    read(clientFd, str, 128);
    /* Not sure if message parsing is included in the performance time.
     * I think it shouldn't be */
    ParseMsg(str, &req);

    GET_TIME(start);
    if (!req.is_read) writeArr(req.msg, req.pos, strArray);

    readArr(str, req.pos, strArray);
    GET_TIME(end);
    write(clientFd, str, COM_BUFF_SIZE);
    close(clientFd);

    result = malloc(sizeof(*result));
    *result = end - start;
    return result;
}

void InitArr(int size) {
    int i;
    arrSize = size;
    strArray = malloc(sizeof(*strArray) * arrSize);
    initLocks(size);
    for (i = 0; i < arrSize; ++i) {
        strArray[i] = malloc(sizeof(*strArray[i]) * COM_BUFF_SIZE);
        sprintf(strArray[i], "String %d: the initial string", i);
    }
}

void DestroyArr() {
    int i;
    destroyLocks();
    for (i = 0; i < arrSize; ++i)
        free(strArray[i]);
    free(strArray);
}
