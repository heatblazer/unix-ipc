#pragma once
#pragma pack(1)
struct msg
{
    char message[256];
    int  result;
    int m_pid;
    char univ[1];
};

