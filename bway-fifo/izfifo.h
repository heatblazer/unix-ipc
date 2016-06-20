#ifndef IZFIFO
#define IZFIFO
#include "defs.h"

/** generates a message to be written to the FIFO
 * @brief iz_msg_generate
 * @param mess
 * @return
 */
struct msg* iz_msg_generate(const char* mess, struct msg *pret);

/** open a fifo and read the contents
 * @brief iz_open_read_from
 * @param m
 * @return
 */
int     iz_open_read_from(struct msg* m);


/** open a FIFO and write to it
 * @brief iz_open_write_to
 * @param m
 * @return
 */
int     iz_open_write_to(struct msg* m);

// send and recieve messages
/** send a message to the  FIFO
 * @brief iz_send_msg
 * @param name of the fifo opened
 * @param data
 * @return
 */
int     iz_send_msg(const char* fifo, struct msg* data);

/** read a message from a FIFO
 * @brief iz_get_msg
 * @param fifo opened
 * @param data
 * @return
 */
int     iz_get_msg(const char* fifo, struct msg* data);

/** connect read fifo and write fifo
 * @brief iz_connect_fifo
 * @param sender
 * @param receiver
 * @return
 */
int     iz_connect_fifo(const char* sender, const char* receiver);


char*   iz_get_my_rfifo(void);
char*   iz_get_my_wfifo(void);
char*   iz_get_my_rwfifo(void);



#endif // IZFIFO

