#include "common.h"
#include "operate.h"
#include <pthread.h>

pthread_mutex_t arrayLock;

void init() { pthread_mutex_init(&arrayLock, NULL); }

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
