#ifndef IZLOCKFILE
#define IZLOCKFILE
#include "defs.h"


/** gets a filesize then rewidns the filepointer
 * @brief iz_get_file_size
 * @param fp
 * @return
 */
size_t iz_get_file_size(FILE* fp);


/** locks a file by a fdesc
 * @brief iz_lock_file
 * @param fd
 * @param fl
 */
void    iz_lock_file(int fd, struct flock* fl);

/** unlocks a file by a fdescr
 * @brief iz_unlock_file
 * @param fd
 * @param fl
 */
void    iz_unlock_file(int fd, struct flock* fl);


#endif // IZLOCKFILE

