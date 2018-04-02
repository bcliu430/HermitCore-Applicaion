#include <sys/socket.h>
#include <netinet/in.h>
//#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include "headers/handler.h"
#include <time.h>
//#include "headers/config.h"

#define IPv4 AF_INET
#define CLIENT_QUEUE 2
#define CONFIG_LEN 1
char ROOT_PATH[] = "/home/beichen/test";
char ROOT_FILE[] = "index.html";
int PORT = 8080;

int main(int argc, char** argv){
    
    int listenfd = 0, conn = 0;
    struct sockaddr_in serv_addr, clie_addr;
    unsigned int length;

    //sockstream tcp data binding
    listenfd = socket(IPv4, SOCK_STREAM, 0);

    //initiate our important server socket struct with nice little 0's
    memset(&serv_addr, '0', sizeof(serv_addr));

    //grab some config data
    char* path = ROOT_PATH;
    char* entry = ROOT_FILE;
    char * delimiter = (char *) malloc(sizeof(char));
    strcpy(delimiter, "/");
    entry = strcat(delimiter, entry);
    path = strcat(path, entry);
    //free(path);

    serv_addr.sin_family = IPv4;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY); //accept connections to all ips of machine
    serv_addr.sin_port = htons(PORT);

    if(bind(listenfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr))){
        perror("Bind failed!\n");
        exit(1);
    }

    if(listen(listenfd, CLIENT_QUEUE)){
        perror("Listen failed!\n");
        exit(1);
    }


    printf("Serverlight started, listening on port %d...\n", PORT);

    while(1){
        printf("start a new conn\n"); 
        length = sizeof(clie_addr);
        //return new socket descriptor when a client connects
        conn = accept(listenfd, (struct sockaddr *) &clie_addr, &length);
        printf("conn %d\n", conn);
        handler_args* hargs;
        hargs = (handler_args *) malloc(sizeof(handler_args));
        hargs->conn = conn;
        hargs->path = path;
        printf("%s\n", path);
        pthread_t threadId;
        int err = pthread_create(&threadId, NULL, &threadHandler, hargs);

        if(err != 0){
            printf("Error could not delegate client to thread");
            return -1;
        }

//        sleep(1);

    }

    return 0;

}
