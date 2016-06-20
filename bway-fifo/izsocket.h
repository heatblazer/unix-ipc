#ifndef IZSOCKET
#define IZSOCKET

int iz_server(const char* mysocket, void* (*cb)(void *), void *pargs);

int iz_client(const char* mysocket);


#endif // IZSOCKET

