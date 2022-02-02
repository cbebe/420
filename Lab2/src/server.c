#include "common.h"
#include "operate.h"
#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    int serverFd = socket(AF_INET, SOCK_STREAM, 0);
    long arrSize;
    int i, clientFd;
    pthread_t t[COM_NUM_REQUEST];
    double times[COM_NUM_REQUEST];
    void *time;
    struct sockaddr_in sock_var;
    sock_var.sin_addr.s_addr = inet_addr(argv[2]);
    sock_var.sin_port = strtol(argv[3], NULL, 10);
    sock_var.sin_family = AF_INET;

    if (argc != 4) {
        fprintf(stderr,
                "usage: %s <Size of theArray_ on server> <server ip> "
                "<server port>\n",
                argv[0]);
        return 1;
    }

    arrSize = strtol(argv[1], NULL, 10);

    if (bind(serverFd, (struct sockaddr *)&sock_var, sizeof(sock_var)) >= 0) {
        printf("socket has been created\n");
        initArr(arrSize);
        listen(serverFd, 20000);
        while (1) {
            /* can support COM_NUM_REQUEST clients at a time */
            for (i = 0; i < COM_NUM_REQUEST; i++) {
                clientFd = accept(serverFd, NULL, NULL);
                pthread_create(&t[i], NULL, HandleRequest,
                               (void *)(long)clientFd);
            }

            for (i = 0; i < COM_NUM_REQUEST; i++) {
                pthread_join(t[i], &time);
                times[i] = *(double *)time;
                free(time);
            }
            saveTimes(times, COM_NUM_REQUEST);
        }
        close(serverFd);
        destroyArr();
    } else {
        fprintf(stderr, "socket creation failed\n");
        return 1;
    }

    return 0;
}
