#include "operate.h"
#include "common.h"
#include "timer.h"
#include <stdio.h>
#include <unistd.h>

static char **strArray;
static double times[COM_NUM_REQUEST];
static int arrSize;

void *HandleRequest(void *args) {
    double start, end, *result;
    int clientFd = (long)args;
    char str[128];
    ClientRequest req;

    read(clientFd, str, 128);
    if (COM_IS_VERBOSE) printf("reading from client:%s\n", str);

    /* Not sure if message parsing is included in the performance time. I'm
     * thinking it shouldn't be */
    ParseMsg(str, &req);

    if (COM_IS_VERBOSE)
        printf("idx: %d\tread: %c\tmsg: %s", req.pos, req.is_read ? 'y' : 'n',
               req.msg);

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

void initArr(int size) {
    int i;
    arrSize = size;
    strArray = malloc(sizeof(*strArray) * arrSize);
    init();
    for (i = 0; i < arrSize; ++i) {
        strArray[i] = malloc(sizeof(*strArray[i]) * COM_BUFF_SIZE);
        sprintf(strArray[i], "String %d: the initial string", i);
    }
}

void destroyArr() {
    int i;
    for (i = 0; i < arrSize; ++i)
        free(strArray[i]);
    free(strArray);
}