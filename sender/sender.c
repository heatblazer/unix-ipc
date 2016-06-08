#define FIFO_NAME "/home/ilian/msgpipe"
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

struct test_call
{
    char msg[64];
    int  result;
};



int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv;

    struct test_call buff;
    // set defaults to send
    strcpy(buff.msg, "I am sending data");
    buff.result = 0;


    int num = 0, fd = 0;

    mknod(FIFO_NAME, S_IFIFO|0666, 0);
    printf("waiting for readers..\n");
    fd = open(FIFO_NAME, O_WRONLY);

    while (1)  {
        sleep(2);
        if ((num = write(fd,
                         (struct test_call*)&buff,
                        sizeof(struct test_call))) == -1) {
            perror("write");
        } else {
            printf("sending %d data\n", num);
        }
    }

    return 0;
}

