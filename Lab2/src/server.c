/**
 * @file server.c
 * @author Charles Ancheta, Patricia Zafra, Michelle Lee
 * @brief Functions containing the main server functionality
 * @version 0.1
 * @date 2022-02-03
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "common.h"
#include "operate.h"
#include <arpa/inet.h>
#include <errno.h>
#include <netinet/in.h>
#include <pthread.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int serverFd;

/**
 * @brief Prints usage
 * @param progName the name of the program, available as argv[0]
 */
static void usage(const char *progName) {
    fprintf(stderr, "usage: %s <Size of theArray_ on server> <server ip> <server port>\n",
            progName);
    exit(1);
}

static void sigtermHandler(int sig) {
    close(serverFd);
    exit(0);
}

int main(int argc, char *argv[]) {
    int clientFd, i;
    long arrSize;
    pthread_t t[COM_NUM_REQUEST];
    double times[COM_NUM_REQUEST];
    void *time;
    struct sockaddr_in sock_var;
    char fileName[COM_BUFF_SIZE];

    if (argc != 4) usage(argv[0]);

    sock_var.sin_addr.s_addr = inet_addr(argv[2]);
    sock_var.sin_port = strtol(argv[3], NULL, 10);
    sock_var.sin_family = AF_INET;

    if (sock_var.sin_port <= 0) usage(argv[0]);

    arrSize = strtol(argv[1], NULL, 10);

    if (arrSize <= 0) usage(argv[0]);

    sprintf(fileName, "output-scheme%c-%ld", argv[0][strlen(argv[0]) - 1], arrSize);
    /* if we're starting this out, we don't want to append to an existing file */
    remove(fileName);

    serverFd = socket(AF_INET, SOCK_STREAM, 0);
    signal(SIGTERM, sigtermHandler);

    if (bind(serverFd, (struct sockaddr *)&sock_var, sizeof(sock_var)) >= 0) {
        if (COM_IS_VERBOSE) printf("socket has been created\n");
        InitArr(arrSize);
        listen(serverFd, 2000);
        while (1) {
            /* can support COM_NUM_REQUEST clients at a time */
            for (i = 0; i < COM_NUM_REQUEST; i++) {
                clientFd = accept(serverFd, NULL, NULL);
                pthread_create(&t[i], NULL, HandleRequest, (void *)(long)clientFd);
            }

            for (i = 0; i < COM_NUM_REQUEST; i++) {
                pthread_join(t[i], &time);
                times[i] = *(double *)time;
                free(time);
            }
            saveTimes(times, COM_NUM_REQUEST, fileName);
            if (COM_IS_VERBOSE) printf("Saved times to file %s\n", fileName);
        }
        close(serverFd);
        DestroyArr();
    } else {
        perror("bind");
        return 98;
    }

    return 0;
}
