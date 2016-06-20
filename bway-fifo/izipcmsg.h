#ifndef IZIPCMSG
#define IZIPCMSG
#include "defs.h"

/** sends a message to te queue, usually the FIFO which will be written to
 * @brief iz_send_sys_msg
 * @param smg
 * @return
 */
int     iz_send_sys_msg(struct sysmsg* smg);

/** gets a sus message from a queue, usually a FIFO to read from
 * @brief iz_get_sys_msg
 * @param smg
 * @return
 */
int     iz_get_sys_msg(struct sysmsg* smg);

#endif // IZIPCMSG

