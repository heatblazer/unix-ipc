#pragma once

struct test_call
{
    char msg[64];
    int byte_arr[128];
    void (*pmsg)(void);
};

