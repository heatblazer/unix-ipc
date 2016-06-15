// defs for the msg
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


void lockFile(int fd, struct flock* fl)
{
    printf("locking file...\n");

    fl->l_type = F_RDLCK | F_WRLCK;
    fl->l_start = SEEK_SET;

    if (fcntl(fd, F_SETLKW, fl) == -1) {
        perror("fcntl");
        exit(1);
    }

    printf("locked!\n");
}


void unlockFile(int fd, struct flock* fl)
{
    printf("unlocking file...\n");
    fl->l_type = F_UNLCK;
    fl->l_start = SEEK_END;

    if (fcntl(fd, F_SETLK, fl) == -1) {
        perror("fcntl");
        exit(1);
    }
    printf("unlocked!\n");
}

void doTask(struct msg *tc, int res, pid_t t)
{
    memset(tc->message, 0, sizeof(tc->message));
    strcpy(tc->message, "bridge worked the data");
    tc->result = res;
    tc->pid = (pid_t)t;
}


static int eXec()
{

}

int main(int argc, char *argv[])
{
    (void)argc;
    (void) argv;
    if (fork()){
        exit(0);
    }

    struct flock fl= {F_WRLCK,SEEK_SET,0,0,0};

    fl.l_pid = getpid(); // bridge`s pid

    int num, fdw, fdr;
    mkfifo(RPIPE_NAME, S_IFIFO|0666);
    mkfifo(WPIPE_NAME, S_IFIFO|0666);


    char ibuff[sizeof(struct msg)]={0};

    fdr = open(RPIPE_NAME, O_RDONLY); // only read
    fdw = open(WPIPE_NAME, O_WRONLY); // only write

    printf("Waiting for requests from writers and readers ...\n");

    for (;;) {
        if ((num = read(fdr, ibuff, sizeof(ibuff)))==-1) {
            perror("read");

        } else {
            printf("request to work a data\n");
//            doTask((struct msg*)ibuff, 1200, getpid());
            // afer that we want to write back to the expected reader
            lockFile(fdw, &fl);
            if ((num = write(fdw, ibuff, sizeof(struct msg))) == -1 ) {
                perror("write");
                unlockFile(fdw, &fl);
            } else {
                // what to do here
            }
        }
    }

    close(fdr);
    close(fdw);

    return 0;
}
