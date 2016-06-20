#include "izsocket.h"

#include "defs.h"

int iz_server(const char *mysocket, void*(*cb)(void*), void* pargs)
{
    (void)cb; (void) pargs; // unused for now
    // detach the child for now with fork, later with a thread
    if (fork()) {
        exit(0);
    }

    struct sockaddr_un sockaddr;
    int fd, cl, rc;
    if ((fd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0) {
        perror("server: socket");
        exit(-1);
    }

    memset(&sockaddr, 0, sizeof(sockaddr));
    sockaddr.sun_family = AF_UNIX;
    strncpy(sockaddr.sun_path, mysocket, strlen(mysocket));
    unlink(mysocket);


    if(bind(fd, (struct sockaddr*)&sockaddr, sizeof(sockaddr)) < 0){
        perror("server: bind");
        exit(-1);
    }

    if (listen(fd, 5) < 0) {
        perror("server: listen");
        exit(-1);
    }

    for(;;) {
        if ((cl = accept(fd, 0, 0)) <  0) {
            perror("server: accept");
            exit(-1);
        } else {
            char b[128]={0};
            while ((rc = read(cl, b, sizeof(b))) > 0) {
                printf("Read %d bytes: %s\n", rc, b);
            }
            if (rc < 0) {
                exit(1);
            }
            if (rc==0) {
                close(cl);
            }
        }
    }

    return 0;
}

