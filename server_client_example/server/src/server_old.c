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
     int sockfd, newsockfd, portno = 12490;
     socklen_t clilen;
     char buffer[BUFFER_SIZE];
     struct sockaddr_in serv_addr, cli_addr;
     int n;

     // if (argc < 2) {
     //      fprintf(stderr, "ERROR, no port provided\n");
     //      exit(EXIT_SUCCESS);
     // }

     // create a socket 
     // socket(int domain_family, int type, int protocol=0) -> int
     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     // int option = 1;
     // setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &option, sizeof(option));
     if (sockfd < 0)
          error("ERROR opening socket\n");
     // clear struct sockaddr_in for SERVER
     memset(&serv_addr, 0, sizeof(serv_addr));
     
               // portno = atoi(argv[1]);
     
     // setup the host_addr structure for use in bind call.
     // server byte order.
     serv_addr.sin_family = AF_INET;  // IP4 protocol is used
     // automatically filled with the current host's IP address
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     // convert short value for port must be converted int network byte order.
     serv_addr.sin_port = htons(portno);
     // bind the socket to the current IP address on port(designated in portno)
     // bind(int fd, struct sockaddr* localsock, socklent_t length_of_struct_sockaddr) -> int
     if (bind(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0)
          error("ERROR on binding\n");
     // tells the socket to listen to the incoming connections.
     // this places all incoming connections into a backlog queue until
     // accept call really accepts the connection.
     // Here the maximum size for the backlog queue is set (= 5)
     listen(sockfd, 5);
     while (1) {
          // int local_error = 0;
          // socklen_t errlen = sizeof(local_error);
          clilen = sizeof(cli_addr);
          // write the connecting client's address info into
          // the address structure and the size of it
          // accept( ) returns a new socket file descriptor for the accepted connection.
          // so the original socket file descriptor can continue to be used for
          // listing to any other incoming connections
          // while the new socket fd is used for communication with the connected client.
          // accept(int listening_fd, struct sockaddr* localsock, socklen_t*) -> new socket
          const char msg_send[] = "Socket Programming with C (OK) --- from Server\n";

          newsockfd = accept(sockfd, (struct sockaddr*)&cli_addr, &clilen);
          if (newsockfd < 0)
               error("ERROR on accept\n");
          printf("server: got connection from %s, port no. %d\n",
               inet_ntoa(cli_addr.sin_addr), ntohs(cli_addr.sin_port));

          // sends the message through the new socket
          // if (getsockopt(newsockfd, SOL_SOCKET, SO_ERROR, &local_error, &errlen) != 0) {
          //      shutdown(newsockfd, SHUT_WR);
          //      close(newsockfd);
          //      break;
          // }
          // else {
               n = send(newsockfd, msg_send, sizeof(msg_send), 0);
               if (n < 0) {
                    shutdown(newsockfd, SHUT_WR);
                    close(newsockfd);
                    break;
               }
               memset(buffer, 0, BUFFER_SIZE);
          // }

          // read the message from the client came through the new socket
          // read(int fd, void* buf, ssize_t len, off_t offset) -> ssize_t
          // if (getsockopt(newsockfd, SOL_SOCKET, SO_ERROR, &local_error, &errlen) != 0) {
          //      shutdown(newsockfd, SHUT_WR);
          //      close(newsockfd);
          //      break;
          // }
          // else {
               n = read(newsockfd, buffer, BUFFER_SIZE);
               if (n < 0) {
                    shutdown(newsockfd, SHUT_WR);
                    close(newsockfd);
                    break;
               }
               // if (n < 0)
               //      error("ERROR reading from socket\n");
               printf("Message from client : %s", buffer);
               close(newsockfd);
          // }
     }
     close(sockfd);
     printf("server program ended\n");

     return 0;
}

