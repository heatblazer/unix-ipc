#ifndef DEFS
#define DEFS
#include <sys/types.h>

// deprecate these
#define RPIPE_NAME "/tmp/read_pipe"
#define WPIPE_NAME "/tmp/write_pipe"

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
    char*    extra_msg;
};


struct sysmsg {
    long mtype;
    char mtext[128];
};


#endif // DEFS

