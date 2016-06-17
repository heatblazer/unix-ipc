#ifndef DEFS
#define DEFS
#include <sys/types.h> // key_t

#define RPIPE_NAME "/tmp/read_pipe"
#define WPIPE_NAME "/tmp/write_pipe"


#pragma pack(1)
struct msg {
    char message[256];
    int  result;
    int  pid;
    key_t key;
    struct {
        long mtype;
        char txt[256];
    } m_resp[2];    // 0 sender, 1 receiver
};


#endif // DEFS

