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
    int result;
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
    char ubuff[sizeof(struct test_call)] = {0};

    do {
        if ((num = read(fd, ubuff, sizeof(struct test_call)))==-1) {
            perror("read");
        } else {
            struct test_call* tc = (struct test_call*) ubuff;
            printf("[%s][%d]\n", tc->msg, tc->result);
        }

    } while (1);

    return 0;
}
