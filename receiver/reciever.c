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

#include "../defs/defs.h"

union s
{
    struct test_call tc;
    char c[sizeof(struct test_call)];
};

int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv;


    int num, fd;
    mknod(FIFO_NAME, S_IFIFO|0666, 0);
    printf("waiting for writers\n");
    fd = open(FIFO_NAME, O_RDONLY);

    printf("Got a writer!\n");
    union s ubuff;

    do {
        if ((num = read(fd, ubuff.c, sizeof(struct test_call)))==-1) {
            perror("read");
        } else {
            struct test_call *tc = (struct test_call*)&ubuff.tc;
            printf("[%s]\n", tc->msg);
            if (tc->pmsg) {
                tc->pmsg();
            }
        }

    } while (num > 0);

    return 0;
}
