---
title: ECE 420 Lab 1 Report
subtitle: Winter 2022
fontsize: 12pt
geometry: margin=0.75in
author: Charles Ancheta, Patricia Zafra
---

# Description of Implementation

The main program uses a multi-threaded implementation of a socket server, serving 1000 requests at a time before writing the average access time of those 1000 requests. The thread function `HandleRequest` parses the client message and depending on the request, makes calls to `readArr` and `writeArr` to modify the data array.  
`readArr` and `writeArr`, along with `initLocks` and `destroyLocks` are implemented differently based on the data protection scheme. These functions are then linked to the main program using the Makefile, letting us have "polymorphism" in C.

### Scheme 1: A Single Mutex Protecting the Entire Array

For this scheme, a mutex was used to protect the entire array using the POSIX built-in `pthread_mutex_t`. All calls to `getContent` and `setContent` (provided functions) were wrapped in calls to the `pthread_mutex_lock` and `pthread_mutex_unlock` functions.

### Scheme 2: Multiple Mutexes, Each Protecting a Different String

For this scheme, an array of `pthread_mutex_t` of size _n_ `arrayLocks` is allocated and initialized. The calls to `getContent` and `setContent` are still wrapped in the `pthread_mutex` calls, but use different `pthread_mutex_t`s accessed from `arrayLocks` using the string index.

### Scheme 3: A Single Read-Write Lock Protecting the Entire Array

For this scheme, a read-write lock was implemented as a struct which contains the necessary attributes:

- The number of readers, writers, and pending writers
- A single mutex, which acts as the lock
- Two conditions for either the reader or writer to proceed

The read lock does a condition wait if there is an active writer or pending writers. When it is done waiting, the number of readers is incremented, and it is granted access to read the content from the array. The write lock does a condition wait if there are active readers or an active writer, and the number of pending writers is incremented. When granted access to the lock, the number of pending writers is decremented, the number of writers is incremented, and it writes to the array.

The read-write lock is unlocked under the following conditions:

- If there is a write lock, then unlock and clear the number of writers
- If there are multiple active readers, then decrement the number of readers and let the pending readers proceed to flush all pending readers
- If there are no more pending or active readers and there is a pending writer, let the writer proceed
- If there are no pending writers, let any pending readers through

Upon the end of the string array, the lock is destroyed.

### Scheme 4: Multiple Read-Write Locks, Each Protecting a Different String

In this scheme, multiple read-write locks are initialized for each string in the array. In other words, we are maintaining an array of read-write locks of size _n_, the size of the array. This way, when a read or write to the _i_-th string of the array is performed, the _i_-th lock will protect it.

Upon the end of the string array, the array of locks is destroyed and memory allocated to the array of locks is freed.

# Performance Discussion

| n    | Scheme 1     | Scheme 2     | Scheme 3     | Scheme 4     |
| ---- | ------------ | ------------ | ------------ | ------------ |
| 10   | 9.365774e-03 | 2.077372e-04 | 4.095920e-03 | 1.785272e-04 |
| 100  | 9.379739e-03 | 1.538090e-04 | 4.108292e-03 | 1.517450e-04 |
| 1000 | 9.371457e-03 | 1.482282e-04 | 4.174168e-03 | 1.487824e-04 |

Processing times of different data protection schemes averaged over 100 runs (in seconds)

Our fastest access time was using scheme 4 and _n_ = 1000 which was 1.379058e-04 seconds.

The performance of scheme 1 and scheme 3 are not affected by the array size _n_ because these protect the whole array with a single lock or mutex. Scheme 3 is faster than scheme 1 because it allows multiple parallel readers, while scheme 1 locks the entire array regardless of whether it was a read or write operation.

The performance of scheme 2 and scheme 4 on the other hand scale with the array size because there are separate locks and mutexes for each string. Scheme 4 does better than scheme 2 on _n_ = 10 because it better handles parallel readers (same as the difference between scheme 1 and scheme 3). This advantage becomes negligible as _n_ grows and resource contention decreases.
