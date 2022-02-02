#include "read_write_lock.h"
#include <pthread.h>

void rwlock_init(rwlock_t *l) {
    l->readers = l->writer = l->pending_writers = 0;
    pthread_mutex_init(&(l->read_write_lock), NULL);
    pthread_cond_init(&(l->readers_proceed), NULL);
    pthread_cond_init(&(l->writer_proceed), NULL);
}

void rwlock_rlock(rwlock_t *l) {
    /* if there is a write lock or pending writers,
       perform condition wait, else increment count
       of readers and grant read lock
    */

    pthread_mutex_lock(&(l->read_write_lock));
    while ((l->pending_writers > 0) || (l->writer > 0))
        pthread_cond_wait(&(l->readers_proceed), &(l->read_write_lock));
    l->readers++;
    pthread_mutex_unlock(&(l->read_write_lock));
}

void rwlock_wlock(rwlock_t *l) {
    /* if there are readers or writers, increment
       pending writers count and wait.
       on being woken, decrement pending writers
       count and increment writer count
    */

    pthread_mutex_lock(&(l->read_write_lock));
    while ((l->writer > 0) || (l->readers > 0)) {
        l->pending_writers++;
        pthread_cond_wait(&(l->writer_proceed), &(l->read_write_lock));
        l->pending_writers--;
    }
    l->writer++;
    pthread_mutex_unlock(&(l->read_write_lock));
}

void rwlock_unlock(rwlock_t *l) {
    /* if there is a write lock then unlock, else if
       there are read locks, decrement count of read
       locks. if the count is 0 and there is a pending
       writer, let it through, else if there are
       pending readers, let them all go through
    */

    pthread_mutex_lock(&(l->read_write_lock));
    if (l->writer > 0)
        l->writer = 0;
    else if (l->readers > 0)
        l->readers--;
    if (l->readers > 0)
        pthread_cond_broadcast(&(l->readers_proceed));
    else if ((l->readers == 0) && (l->pending_writers > 0))
        pthread_cond_signal(&(l->writer_proceed));
    else if ((l->readers == 0) && (l->pending_writers == 0))
        pthread_cond_broadcast(&(l->readers_proceed));
    pthread_mutex_unlock(&(l->read_write_lock));
}
