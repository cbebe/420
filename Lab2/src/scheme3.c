/**
 * @file scheme3.c
 * @author Charles Ancheta, Patricia Zafra, Michelle Lee (you@domain.com)
 * @brief Data Structure protection implementation 3
 * @version 0.1
 * @date 2022-01-31
 *
 * @copyright Copyright (c) 2022
 *
 * Uses a single read/write lock to protect the entire array
 */
#include "common.h"
#include "operate.h"
#include "read_write_lock.h"
#include <pthread.h>

static RWLock_t arrayLock;

void initLocks(int size) {
    RWLockInit(&arrayLock);
    if (COM_IS_VERBOSE) printf("initialize read-write lock for array of size %d\n", size);
}

void destroyLocks() { RWLockDestroy(&arrayLock); }

void readArr(char *dest, int index, char **strArray) {
    RWLockRLock(&arrayLock);
    getContent(dest, index, strArray);
    RWLockUnlock(&arrayLock);
}

void writeArr(char *src, int index, char **strArray) {
    RWLockWLock(&arrayLock);
    setContent(src, index, strArray);
    RWLockUnlock(&arrayLock);
}
