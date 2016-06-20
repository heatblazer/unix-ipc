// ansi-c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* error */
#include <errno.h>

/* ipc */
#include <sys/types.h>
#include <sys/stat.h>

/* unix */
#include <fcntl.h>
#include <unistd.h>

/* message que */
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#include <sys/types.h>
// unix sockets
#include <sys/socket.h>
#include <sys/un.h>

int main(void)
{
    struct sockaddr_un sockaddr;
    int fd, cl, rc;

    if ((fd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
        perror("server: socket");
        exit(-1);
    }

    memset(&sockaddr, 0, sizeof(sockaddr));
    char *sad = "/tmp/1.1.1.1";
    sockaddr.sun_family = AF_UNIX;
    strncpy(sockaddr.sun_path, sad, strlen(sad));

    if (connect(fd, (struct sockaddr*)&sockaddr,
                sizeof(sockaddr)) < 0) {
        perror("connct");
        exit(1);
    }
    char buff[128]={0};
    while ((rc = read(STDIN_FILENO, buff, sizeof(buff))) >0) {
        if (write(fd, buff, rc) != rc) {
            if (rc > 0) {
                fprintf(stderr, "Partial write\n");
            } else {
                perror("write error");
                exit(1);
            }
        }
    }
    return 0;
}

