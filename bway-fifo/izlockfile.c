#include "izlockfile.h"


size_t iz_get_file_size(FILE *fp)
{
    if (!fp) {
        return 0;
    }
    fseek(fp, 0L, SEEK_END);
    size_t sz = ftell(fp);
    fseek(fp, 0L, SEEK_SET); // rewind it
    return sz;
}


void iz_lock_file(int fd, struct flock* fl)
{
    printf("locking file...\n");

    fl->l_type = F_RDLCK | F_WRLCK;
    fl->l_start = SEEK_SET;

    if (fcntl(fd, F_SETLKW, fl) == -1) {
        perror("fcntl");
        exit(1);
    }

    printf("locked!\n");
}


void iz_unlock_file(int fd, struct flock* fl)
{
    printf("unlocking file...\n");
    fl->l_type = F_UNLCK;
    fl->l_start = SEEK_END;

    if (fcntl(fd, F_SETLK, fl) == -1) {
        perror("fcntl");
        exit(1);
    }
    printf("unlocked!\n");
}

