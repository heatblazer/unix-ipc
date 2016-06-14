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
    int msgid=0;
    int msgflag = IPC_CREAT | 0666;
//
    key_t key = 1234;
    msgbuff_t sbuf;
    size_t buf_len;
    fprintf(stderr, "\nmssgget: Calling msgget(%#lx,\
    %#o)\n", key, msgflag);
    if ((msgid = msgget(key, msgflag)) < 0) {
        perror("msgget");
        exit(1);
    }
    sbuf.mtype = 1;
   // buf_len = strlen(sbuf.mtext) + 1;
    /*
     * send the message
     */

    while(fgets(sbuf.txt, 256, stdin) >= 0) {

        if (msgsnd(msgid, &sbuf, strlen(sbuf.txt), IPC_NOWAIT) < 0) {
            printf("%d, %d, %s, %d\n", msgid, sbuf.mtype, sbuf.txt, buf_len);
            perror("msgsnd");
            exit(1);
        } else {
            printf("Message: [%s] Sent\n", sbuf.txt);
        }
    }
    exit(0);
}

