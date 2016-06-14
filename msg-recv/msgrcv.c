// ANSI-C
#include <stdio.h>
#include <string.h>

// system v
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MSG_SIZE 256

static int p(void)
{
    printf("CALLED!!!\n");
}

typedef struct msgbuf {
    long mtype;
    struct {
        int (*pfoo)(void);
        char txt[MSG_SIZE];
    };
} msgbuff_t;



int main(void)
{
    int msgid = 0;
    key_t key;
    msgbuff_t rbuf;

    key = 1234;

    if ((msgid = msgget(key, 0666)) < 0) {
       perror("msgget");
       exit(1);
    }

    rbuf.pfoo = p;
    for(;;) {
        if (msgrcv(msgid, &rbuf, MSG_SIZE, 1, 0) < 0) {
        } else {
            printf("Answer: [%s]\n", rbuf.txt);
        }
    }

    exit(0);

    return 0;
}

