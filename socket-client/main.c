#define SOCK_PATH "echo_path1"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <errno.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/un.h>



int main(int argc, char *argv[])
{
    int s, s2, t, len;
    struct sockaddr_un local, remote;
    char str[256] = {0};

    if ((s=socket(AF_UNIX, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    local.sun_family = AF_UNIX;
    strcpy(local.sun_path, SOCK_PATH);

    len = strlen(local.sun_path + sizeof(local.sun_family));

    if (connect(s, (struct sockaddr*)&remote, len) == -1) {
        perror("connect");
        exit(1);
    }

    printf("Connected!\n");

    while(printf(">"), fgets(str, sizeof(str)/sizeof(char), stdin), !feof(stdin)) {
        if (send(s, str, strlen(str), 0) == -1) {
            perror("send");
            exit(1);
        }

        if ((t=recv(s, str, 256, 0)) > 0) {
            str[t] = 0; // cut newline
            printf("echo> %s\n", str);
        } else {
            if ( t < 0) {
                perror("recv");
            } else {
                printf("Server closed connection \n");
                exit(1);
            }
        }
    }

    close(s);

    return 0;
}
