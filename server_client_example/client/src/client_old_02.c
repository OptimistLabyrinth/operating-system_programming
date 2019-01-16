#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <unistd.h>
#define BUFFER_SIZE 256

void error(const char *msg)
{
    perror(msg);
    exit(0);
}

int main(int argc, char *argv[])
{
    const char* myhostname = "127.0.0.1";
    int sockfd, portno = 12490;
    struct sockaddr_in serv_addr;
    struct hostent* server;
    char buffer[BUFFER_SIZE];
    int n;

    // if (argc < 3) {
    //     fprintf(stderr, "usage %s hostname port\n", argv[0]);
    //     exit(EXIT_SUCCESS);
    // }
            // portno = atoi(argv[2]);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0)
        error("ERROR opening socket\n");
    server = gethostbyname(myhostname);
    if (server == NULL) {
        fprintf(stderr, "ERROR, no such host\n");
        exit(EXIT_SUCCESS);
    }
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    memcpy(&server->h_name, &serv_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(portno);

    if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
        error("ERROR connecting\n");

    while (1) {
        printf("Enter Message : ");
        memset(buffer, 0, BUFFER_SIZE);
        fgets(buffer, BUFFER_SIZE, stdin);
        if (strncmp(buffer, ":exit", 5) == 0 || strncmp(buffer, ":quit", 5) == 0) {
            n = write(sockfd, buffer, BUFFER_SIZE);
            if (n < 0)
                error("ERROR writing \":exit\" to socket");
            break;
        }

        n = write(sockfd, buffer, BUFFER_SIZE);
        if (n < 0)
            error("ERROR writing to socket\n");
        memset(buffer, 0, BUFFER_SIZE);
        n = read(sockfd, buffer, BUFFER_SIZE);
        if (n < 0)
            error("ERROR reading from socket\n");
        printf("%s", buffer);
    }
    shutdown(sockfd, SHUT_RD);
    close(sockfd);

    return 0;
}

