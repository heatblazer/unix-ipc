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
    remove(local.sun_path);

    len = strlen(local.sun_path + sizeof(local.sun_family));
    if (bind(s, (struct sockaddr*)&local, len) == -1 ) {
        perror("bind");
        exit(1);
    }

    if(listen(s, 5) == -1) {
        perror("listen");
        exit(1);
    }


    for(;;) {
        int done, n;
        printf("Waiting for connection...\n");
        t = sizeof(remote);
        if ((s2 = accept(s, (struct sockaddr*)&remote, &t))==-1) {
            perror("accept");
            exit(1);
        }
        printf("Connecetd!\n");

        done = 0;
        do {

            if ((n = recv(s2, str, sizeof(str)/sizeof(char), 0)) <= 0) {
                perror("recv");
                done = 1;
            }

            if (!done) {
                if (send(s2, str, n, 0) < 0) {
                    perror("send");
                    done = 1;
                }
            }
        } while (!done);
        close(s2);
    } // end forever

    return 0;
}
