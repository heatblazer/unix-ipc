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



int main(int argc, char *argv[])
{
    (void)argc;
    (void) argv;
    // daemonize it
    if (fork()){
        exit(0);
    }


    struct flock fl= {F_WRLCK,SEEK_SET,0,0,0};

    fl.l_pid = getpid(); // bridge`s pid

    int num, fdw, fdr;
    mkfifo(RPIPE_NAME, S_IFIFO|0666);
    mkfifo(WPIPE_NAME, S_IFIFO|0666);

    union ibuff {
        struct msg m;
        char c[sizeof(struct msg)];
    };
    union ibuff ib;

    fdr = open(RPIPE_NAME, O_RDONLY); // only read
    fdw = open(WPIPE_NAME, O_WRONLY); // only write

    printf("Waiting for requests from writers and readers ...\n");

    for (;;) {
        if ((num = read(fdr, ib.c, sizeof(struct msg)))==-1) {
            perror("read");

        } else {
            printf("request to work a data\n");
            lockFile(fdw, &fl);
            if ((num = write(fdw, ib.c, sizeof(struct msg))) == -1 ) {
                perror("write");
                unlockFile(fdw, &fl);
            } else {
                // what to do here
                //sendMsgToWriter((struct msg*)ibuff, 1, getpid());
            }
        }
    }

    close(fdr);
    close(fdw);

    return 0;
}
