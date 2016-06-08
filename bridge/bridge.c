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


void doTask(struct test_call *tc)
{
    memset(tc->msg, 0, sizeof(tc->msg));
    strcpy(tc->msg, "bridge worked the data");
    tc->result = 0;
}

int main(int argc, char *argv[])
{
    (void)argc;
    (void) argv;

    int num, fd;
    mknod(FIFO_NAME, S_IFIFO|0666, 0);

    char ibuff[sizeof(struct test_call)]={0};

    fd = open(FIFO_NAME, O_RDWR); // read and write back

    printf("Waiting for requests from writers...\n");

    while (1) {

        if ((num = read(fd, ibuff, sizeof(ibuff)))==-1) {
            perror("read");
            continue;
        } else {
            printf("request to work a data\n");
            doTask((struct test_call*) ibuff);

            // afer that we want to write back to the expected reader
            num = write(fd, ibuff, sizeof(struct test_call));
                // cant write now to file

        }

    }



    return 0;
}
