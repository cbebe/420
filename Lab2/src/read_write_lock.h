
#ifndef _READ_WRITE_LOCK_H_
#define _READ_WRITE_LOCK_H_

#include <pthread.h>

/**
 * @brief Define a struct that holds the attributes of a read-write lock
 */
typedef struct {
    int readers;
    int writer;
    pthread_cond_t readers_proceed;
    pthread_cond_t writer_proceed;
    int pending_writers;
    pthread_mutex_t read_write_lock;
} RWLock_t;

/**
 * @brief Initialize the read-write lock
 *
 * @param lock the read-write lock
 */
void RWLockInit(RWLock_t *lock);

/**
 * @brief A lock on reads
 *        Perform a wait if there is a write lock or pending writers
 *
 * @param lock the read-write lock
 */
void RWLockRLock(RWLock_t *lock);

/**
 * @brief A lock on writes
 *        Perform a wait if there are readers or writers
 *
 * @param lock the read-write lock
 */
void RWLockWLock(RWLock_t *lock);

/**
 * @brief Unlocks the read-write lock
 *
 * @param lock the read-write lock
 */
void RWLockUnlock(RWLock_t *lock);

#endif
