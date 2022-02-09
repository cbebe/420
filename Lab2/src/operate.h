#ifndef _LAB2_OPERATE_H_
#define _LAB2_OPERATE_H_

#include "common.h"

/* Welcome to object-oriented programming in C */

/**
 * @brief Initializes any mutexes needed by the implementation
 */
void initLocks(int size);

/**
 * @brief Destroys any mutexes used by the implementation
 */
void destroyLocks();

/**
 * @brief Wraps getContent in a critical section
 *
 * @param dest the destination string
 * @param index the index of the string to retrieve
 * @param strArray the string array
 */
void readArr(char *dest, int index, char **strArray);

/**
 * @brief Wraps setContent in a critical section
 *
 * @param src the source string
 * @param index the index of the string to write
 * @param strArray the string array
 */
void writeArr(char *src, int index, char **strArray);

/**
 * @brief Allocates memory for the string array
 *
 * @param size the size of the string array
 */
void InitArr(int size);

/**
 * @brief Deallocates the string array
 */
void DestroyArr();

/**
 * @brief Handles a single request
 *
 * @param args the client file descriptor (passed as int)
 * @return double* pointer to the access time of the request (must be deallocated later)
 */
void *HandleRequest(void *args);

#endif
