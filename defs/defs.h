#pragma once


#define RPIPE_NAME "/tmp/rpipe"
#define WPIPE_NAME "/tmp/wpipe"

#pragma pack(1)
struct msg
{
    char message[256];
    int  result;
    int m_pid;
    char univ[1];
};

