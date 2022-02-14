/**
 * @file scheme4.c
 * @author Charles Ancheta, Patricia Zafra
 * @brief Data Structure protection implementation 4
 * @version 0.1
 * @date 2022-01-31
 *
 * @copyright Copyright (c) 2022
 *
 * Uses multiple read/write locks to protect each string in the array
 *
 * TODO: Implement using multiple read/write locks
 */
#include "common.h"
#include "operate.h"
#include "read_write_lock.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

static RWLock_t *arrayLocks;
static int arraySize;

void initLocks(int size) {
    int i;
    arraySize = size;
    arrayLocks = malloc(size * sizeof(*arrayLocks));
    for (i = 0; i < size; ++i)
        RWLockInit(&arrayLocks[i]);
    if (COM_IS_VERBOSE) printf("initialize %d read-write locks for array of size %d\n", size, size);
}

void destroyLocks() {
    int i;
    for (i = 0; i < arraySize; ++i)
        RWLockDestroy(&arrayLocks[i]);
    free(arrayLocks);
}

void readArr(char *dest, int index, char **strArray) {
    RWLockRLock(&arrayLocks[index]);
    getContent(dest, index, strArray);
    RWLockUnlock(&arrayLocks[index]);
}
void writeArr(char *src, int index, char **strArray) {
    RWLockWLock(&arrayLocks[index]);
    setContent(src, index, strArray);
    RWLockUnlock(&arrayLocks[index]);
}
