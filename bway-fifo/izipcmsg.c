#include "izipcmsg.h"



int iz_send_sys_msg(struct sysmsg *smg)
{
    int msgqid;
    key_t key = 1234;
    smg->mtype = 1;
    if ((msgqid = msgget(key, 0666|IPC_CREAT)) < 0) {
        perror("msgget");
        return -1;
    }
    char b[128]={0};
    sprintf(b, "/tmp/%dw0", getpid());
    strcpy(smg->mtext, b);
    int blen = strlen(smg->mtext)+1;
    if(msgsnd(msgqid, smg, blen, IPC_NOWAIT) < 0) {
        perror("msgsnd");
        return -1;
    }

    printf("Message [%s] sent\n", smg->mtext);
    return 0;
}


int iz_get_sys_msg(struct sysmsg *smg)
{
    int msgqid;
    key_t key = 1234;
    if ((msgqid = msgget(key, 0666)) < 0) {
        perror("msgget");
        return -1;
    }

    if(msgrcv(msgqid, (struct sysmsg*)smg, 128, 1, 0) < 0) {
        perror("msgsnd");
        return -1;
    }
    printf("Message [%s] got\n", smg->mtext);
    return 0;
}

