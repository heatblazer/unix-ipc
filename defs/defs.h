#pragma once

// TODO - move it to the /tmp 
#define RPIPE_NAME "/home/ilian/rpipe"
#define WPIPE_NAME "/home/ilian/wpipe"

#pragma pack(1)
struct msg
{
    char message[256];
    int  result;
    int m_pid;
    char univ[1];
};

