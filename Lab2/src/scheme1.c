/**
 * @file scheme1.c
 * @author Charles Ancheta, Patricia Zafra, Michelle Lee (you@domain.com)
 * @brief Data Structure protection implementation 1
 * @version 0.1
 * @date 2022-01-31
 *
 * @copyright Copyright (c) 2022
 *
 * Uses a single mutex to protect the entire array
 */
#include "common.h"
#include "operate.h"
#include <pthread.h>

static pthread_mutex_t arrayLock = PTHREAD_MUTEX_INITIALIZER;

void initLocks(int size) {
    if (COM_IS_VERBOSE) printf("initialize mutex for array of size %d\n", size);
}

void readArr(char *dest, int index, char **strArray) {
    pthread_mutex_lock(&arrayLock);
    getContent(dest, index, strArray);
    pthread_mutex_unlock(&arrayLock);
}

void writeArr(char *src, int index, char **strArray) {
    pthread_mutex_lock(&arrayLock);
    setContent(src, index, strArray);
    pthread_mutex_unlock(&arrayLock);
}