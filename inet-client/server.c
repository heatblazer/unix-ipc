// ANSI-C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


// inet
#include <netdb.h>
#include <netinet/in.h>


void doprocessing(int sock);

int main(int argc, char** argv)
{
    int socket_fd, newsocket_fd, port_no, cli_len;
    char buffer[256]= {0};
    struct sockaddr_in serv_addr, cli_addr;
    int n, pid;

    /*  first create the socket */
    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        perror("socket");
        exit(1);
    }


    /* init sock structure */
    bzero((char*)&serv_addr, sizeof(serv_addr));
    port_no = 5001;

    serv_addr.sin_family = AF_INET; // ipv4
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port_no);

    /* now we bind the socket */
    if(bind(socket_fd, (struct sockaddr*)&serv_addr,
            sizeof(serv_addr)) < 0) {
        perror("error handling");
        exit(1);
    }

    listen(socket_fd, 5);
    cli_len = sizeof(cli_addr);

    for(;;) {
        newsocket_fd = accept(socket_fd, (struct sockaddr*)&cli_addr, &cli_len);
        if (newsocket_fd < 0) {
            perror("error on accept");
            exit(1);
        }

        /* create child proc */
        if ((pid = fork()) < 0) {
            perror("error on fork()");
            exit(1);
        } else if (pid==0) {
            /* this is the cli process */
            close(socket_fd);
            doprocessing(newsocket_fd);
        } else {
            close(newsocket_fd);
        }
    }

    return 0;
}

void doprocessing(int sock)
{
    int n;
   char buffer[256];
   bzero(buffer,256);
   n = read(sock,buffer,255);

   if (n < 0) {
      perror("ERROR reading from socket");
      exit(1);
   }

   printf("Here is the message: %s\n",buffer);
   n = write(sock,"I got your message",18);

   if (n < 0) {
      perror("ERROR writing to socket");
      exit(1);
   }
}
