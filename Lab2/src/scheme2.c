/**
 * @file scheme2.c
 * @author Charles Ancheta, Patricia Zafra (you@domain.com)
 * @brief Data Structure protection implementation 2
 * @version 0.1
 * @date 2022-01-31
 *
 * @copyright Copyright (c) 2022
 *
 * Uses multiple mutexes to protect each string in the array
 */
#include "common.h"
#include "operate.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

static pthread_mutex_t *arrayLocks;
static int arraySize;

void initLocks(int size) {
    int i;
    arraySize = size;
    arrayLocks = malloc(size * sizeof(*arrayLocks));
    for (i = 0; i < size; ++i)
        pthread_mutex_init(&arrayLocks[i], NULL);
    if (COM_IS_VERBOSE) printf("initialize %d mutexes for array of size %d\n", size, size);
}

void destroyLocks() {
    int i;
    for (i = 0; i < arraySize; ++i)
        pthread_mutex_destroy(&arrayLocks[i]);
    free(arrayLocks);
}

void readArr(char *dest, int index, char **strArray) {
    pthread_mutex_lock(&arrayLocks[index]);
    getContent(dest, index, strArray);
    pthread_mutex_unlock(&arrayLocks[index]);
}
void writeArr(char *src, int index, char **strArray) {
    pthread_mutex_lock(&arrayLocks[index]);
    setContent(src, index, strArray);
    pthread_mutex_unlock(&arrayLocks[index]);
}
