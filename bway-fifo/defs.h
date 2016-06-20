#pragma once
#ifndef DEFS
#define DEFS

// unused and deprecated //
#define IZ_SHARED_FIFO "/tmp/bwayfifo"

// ansi-c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* error */
#include <errno.h>

/* ipc */
#include <sys/types.h>
#include <sys/stat.h>

/* unix */
#include <fcntl.h>
#include <unistd.h>

/* message que */
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>



#include <sys/types.h>

// msg is passed trough files
#pragma pack(1)
struct msg {
    char message[512]; // enough for a short message
    int  result;       // result - usually bytes read form reader
    int  pid;          // process that sends the message
    struct {
        char fifo_read[64];    // where to read from
        char fifo_write[64];   // where to write to
    } fifo_files;
    char*    extra_msg; // unused for now, will be used for tests
};


struct sysmsg {
    long mtype;
    char mtext[128];
};





#endif // DEFS

