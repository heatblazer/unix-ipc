#ifndef DEFS
#define DEFS

#define RPIPE_NAME "/tmp/read_pipe"
#define WPIPE_NAME "/tmp/write_pipe"


#pragma pack(1)
struct msg {
    char message[256];
    int  result;
    int  pid;
    void* univ;
};


#endif // DEFS

