// default message structure
#include "../defs/defs.h" // for the msg  struct

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

    struct msg buff;
    // set defaults to send
    strcpy(buff.message, "I am sending data");
    buff.result = 0;
    int num = 0, fd = 0;

    //mknod(FIFO_NAME, S_IFIFO|0666, 0);
    printf("waiting for readers..\n");
    fd = open(RPIPE_NAME, O_WRONLY);

    for (;;)  {
        char mbuff[256]= {0};

        while (fgets(mbuff, 256, stdin) >= 0) {
            strcpy(((struct msg*)&buff)->message, mbuff);
            if ((num = write(fd,
                             (struct msg*)&buff,
                            sizeof(struct msg))) == -1) {
                perror("write");
                break;
            } else {
                printf("sending %d data\n", num);
            }
        } // else - nothign
    } // forever

    return 0;
}

