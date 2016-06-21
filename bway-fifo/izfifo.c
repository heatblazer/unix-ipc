#include "izfifo.h"

char*   iz_get_my_rwfifo()
{
    static char b[64]={0};
    static int rcnt = 0;
    pid_t cpid = getpid();
    sprintf(b, "/tmp/%dRW%d", cpid, rcnt++);
    return b;
}

char*   iz_get_my_rfifo()
{
    static char b[64]={0};
    static int rcnt = 0;
    pid_t cpid = getpid();
    sprintf(b, "/tmp/%dR%d", cpid, rcnt++);
    return b;
}


char* iz_get_my_wfifo()
{
    static char b[64]={0};
    static int rcnt = 0;
    pid_t cpid = getpid();
    sprintf(b, "/tmp/%dW%d", cpid, rcnt++);
    return b;
}


struct msg* iz_msg_generate(const char* mess, struct msg* pret)
{
    if (!mess || !pret) {
        return 0;
    }

    strcpy(pret->message, mess);
    return pret;

}


int iz_send_msg(const char* fifo, struct msg *data)
{
    if(!data || !fifo) {
        return -1;
    }
    int fd;
    if ((fd= open(fifo, O_WRONLY|O_NONBLOCK)) < 0) {
        return -1;
    }

    if (write(fd, (struct msg*)data,
              sizeof(struct msg)) < 0) {
        perror("write");
        return -1;
    }
    return fd; // the handle to the opened file strm
}



int iz_get_msg(const char* fifo, struct msg *data)
{
    if(!data || !fifo) {
        return -1;
    }
    int fd;
    if((fd=open(fifo, O_RDWR|O_NONBLOCK)) < 0) {
        return -1;
    }
    char c[sizeof(struct msg)]={0};
    if(read(fd, c, sizeof(struct msg))<0){
        perror("read");
        return -1;
    }
    memset(data, c, sizeof(struct msg));
    return fd;
}



int iz_open_read_from(struct msg *m)
{
    if(mkfifo(m->message, 0666)==0) {
        int fd = open(m->message, O_RDWR|O_NONBLOCK);
        return fd;
    }
}


int iz_open_write_to(struct msg *m)
{
    if(mkfifo(m->fifo_files.fifo_write, 0666)==0) {
        int fd = open(m->fifo_files.fifo_write, O_WRONLY|O_NONBLOCK);
        return fd;
    }
}

