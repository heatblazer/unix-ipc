#define FIFO_NAME "virusfifo"
// message struct
#include "../defs/defs.h"

// ansi-c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// error
#include <errno.h>

// ipc
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <sys/msg.h>

// unix
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv;

    int num, fd;
    //mknod(FIFO_NAME, S_IFIFO|0666, 0);
    printf("waiting for writers\n");
    fd = open(FIFO_NAME, O_RDONLY);
    printf("Got a writer!\n");
    char ubuff[sizeof(struct msg)] = {0};

    for(;;) {
        if ((num = read(fd, (struct msg*)ubuff, sizeof(struct msg)))==-1) {
            perror("read");
        } else {
            struct msg* tc = (struct msg*) ubuff;

            // i`ve read the buffer now I must see the msg form bridge
            // then send back a return message

        }
    }

    return 0;
}
