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

int createServer(const char *ip, int port);
int startServer(int serverFd);

int main(int argc, char *argv[]) {
    int serverFileDescriptor, clientFileDescriptor, i, port;
    long arrSize;
    pthread_t t[COM_NUM_REQUEST];
    char *serverIp;

    if (argc != 4) {
        fprintf(stderr,
                "usage: %s <Size of theArray_ on server> <server ip> "
                "<server port>\n",
                argv[0]);
        exit(1);
    }
    arrSize = strtol(argv[1], NULL, 10);
    serverIp = argv[2];
    port = strtol(argv[3], NULL, 10);

    if ((serverFileDescriptor = createServer(serverIp, port)) < 0) {
        printf("socket creation failed\n");
        return 1;
    }
    printf("socket has been created\n");
    initArr(arrSize);
    startServer(serverFileDescriptor);
    destroyArr();

    return 0;
}

/*
Creates a socket server
Arguments:
ip - the IP address of the server
port - the port to bind to
*/
int createServer(const char *ip, int port) {
    int serverFileDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in sock_var;
    sock_var.sin_addr.s_addr = inet_addr(ip);
    sock_var.sin_port = port;
    sock_var.sin_family = AF_INET;
    if (bind(serverFileDescriptor, (struct sockaddr *)&sock_var,
             sizeof(sock_var)) < 0)
        return -1;

    return serverFileDescriptor;
}

int startServer(int serverFd) {
    int clientFd, i;
    void *time;
    pthread_t t[COM_NUM_REQUEST];
    double times[COM_NUM_REQUEST];
    listen(serverFd, 2000);
    /* can support COM_NUM_REQUEST clients at a time */
    for (i = 0; i < COM_NUM_REQUEST; i++) {
        clientFd = accept(serverFd, NULL, NULL);
        if (COM_IS_VERBOSE) printf("Connected to client %d\n", clientFd);
        pthread_create(&t[i], NULL, HandleRequest, (void *)(long)clientFd);
    }

    for (i = 0; i < COM_NUM_REQUEST; i++) {
        pthread_join(t[i], &time);
        times[i] = *(double *)time;
        free(time);
    }
    saveTimes(times, COM_NUM_REQUEST);

    close(serverFd);
}