#ifndef _LAB2_OPERATE_H_
#define _LAB2_OPERATE_H_

#include "common.h"
#include <stdlib.h>

/* Welcome to object-oriented programming in C */

/**
 * @brief Initializes any mutexes needed by the implementation
 */
void init_locks(int size);

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
void initArr(int size);

/**
 * @brief Deallocates the string array
 */
void destroyArr();

/**
 * @brief Handles a single request
 *
 * @param args the client file descriptor (passed as int)
 * @return void* NULL
 */
void *HandleRequest(void *args);

#endif
