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
    int byte_arr[128];
    void (*pmsg)(void*);
};



static void  pfoo(void* p)
{
}

int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv;

    struct test_call buff;
    strcpy(buff.msg, "sender message");
    int i =0;
    while (i < 128) {
        buff.byte_arr[i] = i;
        i++;
    }
    buff.pmsg = pfoo;

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

