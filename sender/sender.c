#define FIFO_NAME "virusfifo"
// default message structure
#include "../defs/defs.h" // for the msg  struct

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


static size_t get_file_size(FILE* fp)
{
    fseek(fp, 0L, SEEK_END);
    size_t sz = ftell(fp);
    fseek(fp, 0L, SEEK_SET); // or rewind
    return sz;
}


struct elf {
    int e_ident[4];
    int e_iclass;
    int e_data;
    int e_identver;
    int e_eiosabi;
    int e_abiversion;
    char e_pad[7];
    int e_type[2];
    int e_mchine[2];
    int version[4];
    int entry[8];
    int phoff[8];
    int shoff[8];
    int flags;
    int size;
    int size2;
    int phnum;
    int shentsize;
    int shnum;
    int shrndx;
};



int main(int argc, char *argv[])
{
    (void) argc;
    (void) argv;

    struct msg buff;
    // set defaults to send
    strcpy(buff.message, "I am sending data");
    buff.result = 0;
    int num = 0, fd = 0;

    //mknod(FIFO_NAME, S_IFIFO|0666, 0);
    printf("waiting for readers..\n");
    fd = open(FIFO_NAME, O_WRONLY);

    FILE* fp = fopen("virus", "rb");
    if (!fp) {
        exit(1);
    }
    size_t sz = get_file_size(fp);
    buff.extra_msg = (char*) malloc(sizeof(char)* sz);
    rewind(fp);

    while(fgets(buff.extra_msg, 64, fp), feof(fp)) {

    }
    struct elf* lf = (struct elf*)buff.extra_msg;

    for (;;)  {
        char mbuff[256]= {0};

        while (fgets(mbuff, 256, stdin) >= 0) {
            strcpy(((struct msg*)&buff)->message, mbuff);
            if ((num = write(fd,
                             (struct msg*)&buff,
                            sizeof(struct msg))) == -1) {
                perror("write");
                break;
            } else {
                printf("sending %d data\n", num);
            }
        } // else - nothign
    } // forever

    return 0;
}

