/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#define BUFFER_SIZE 256

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char* argv[])
{
     int sockfd, newsockfd;
     static int portno = 12490;
     socklen_t clilen;
     char buffer[BUFFER_SIZE];
     struct sockaddr_in serv_addr, cli_addr;
     int n;

     // if (argc < 2) {
     //      fprintf(stderr, "ERROR, no port provided\n");
     //      exit(EXIT_SUCCESS);
     // }

     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     // int option = 1;
     // setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));
     if (sockfd < 0)
          error("ERROR opening socket\n");
     memset(&serv_addr, 0, sizeof(serv_addr));
     
     // portno = atoi(argv[1]);

     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);
     
     if (bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
          error("ERROR on binding\n");

     listen(sockfd, 5);
     
     int pid;
     fflush(stdout);
     while (1) {
          newsockfd = accept(sockfd, (struct sockaddr*)&cli_addr, &clilen);
          uint16_t portno_fork = ntohs(cli_addr.sin_port);
          const char msg_send[] = "Socket Programming with C (OK) --- from Server\n";
          if (newsockfd < 0) {
               error("ERROR on accept\n");
               close(sockfd);
               break;
          }
          else {
               pid = fork();
               if (pid > 0) {
                    continue;
               }
               else {
                    clilen = sizeof(cli_addr);
                    printf("server: got connection from %s, port no. %d\n",
                         inet_ntoa(cli_addr.sin_addr), portno_fork);
                    n = send(newsockfd, msg_send, sizeof(msg_send), 0);
                    if (n < 0) {
                         shutdown(newsockfd, SHUT_WR);
                         close(newsockfd);
                         // break;
                    }
                    memset(buffer, 0, BUFFER_SIZE);

                    n = read(newsockfd, buffer, BUFFER_SIZE);
                    if (n < 0)
                         error("ERROR reading from socket\n");
                    printf("Message from client : %s", buffer);
                    close(newsockfd);
                    close(sockfd);
                    return 0;
               }
          }
     }
     close(sockfd);
     printf("server program ended\n");

     return 0;
}

