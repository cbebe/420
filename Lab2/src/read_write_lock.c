/**
 * @file read_write_lock.c
 * @author Charles Ancheta, Patricia Zafra
 * @brief Read-write lock used for protecting the data structure
 * @version 0.1
 * @date 2022-02-05
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "read_write_lock.h"
#include <pthread.h>

void RWLockInit(RWLock_t *lock) {
    lock->readers = lock->writer = lock->pending_writers = 0;
    pthread_mutex_init(&(lock->read_write_lock), NULL);
    pthread_cond_init(&(lock->readers_proceed), NULL);
    pthread_cond_init(&(lock->writer_proceed), NULL);
}

void RWLockDestroy(RWLock_t *lock) {
    pthread_mutex_destroy(&(lock->read_write_lock));
    pthread_cond_destroy(&(lock->readers_proceed));
    pthread_cond_destroy(&(lock->writer_proceed));
}

void RWLockRLock(RWLock_t *lock) {
    /* if there is a write lock or pending writers, perform condition wait,
       else increment count of readers and grant read lock */

    pthread_mutex_lock(&(lock->read_write_lock));
    while ((lock->pending_writers > 0) || (lock->writer > 0))
        pthread_cond_wait(&(lock->readers_proceed), &(lock->read_write_lock));
    lock->readers++;
    pthread_mutex_unlock(&(lock->read_write_lock));
}

void RWLockWLock(RWLock_t *lock) {
    /* if there are readers or writers, increment pending writers count and wait.
       on being woken, decrement pending writers count and increment writer count */

    pthread_mutex_lock(&(lock->read_write_lock));
    while ((lock->writer > 0) || (lock->readers > 0)) {
        lock->pending_writers++;
        pthread_cond_wait(&(lock->writer_proceed), &(lock->read_write_lock));
        lock->pending_writers--;
    }
    lock->writer++;
    pthread_mutex_unlock(&(lock->read_write_lock));
}

void RWLockUnlock(RWLock_t *lock) {
    /* if there is a write lock then unlock, else if there are read locks, decrement
       count of read locks. if the read count is 0 and there is a pending writer, let
       the writer through, else if there are pending readers, let them all go through */

    pthread_mutex_lock(&(lock->read_write_lock));
    if (lock->writer > 0)
        lock->writer = 0;
    else if (lock->readers > 0)
        lock->readers--;
    if (lock->readers > 0)
        pthread_cond_broadcast(&(lock->readers_proceed));
    else if ((lock->readers == 0) && (lock->pending_writers > 0))
        pthread_cond_signal(&(lock->writer_proceed));
    else if ((lock->readers == 0) && (lock->pending_writers == 0))
        pthread_cond_broadcast(&(lock->readers_proceed));
    pthread_mutex_unlock(&(lock->read_write_lock));
}
