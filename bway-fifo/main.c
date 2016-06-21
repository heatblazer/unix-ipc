/* definitions and includes */
#include "defs.h"

#include "izfifo.h"
#include "izipcmsg.h"
#include "izlockfile.h"
#include "izsocket.h"

int     testExec(int argc, char **argv);

int main(int argc, char** argv)
{
    return testExec(argc, argv);
}


int testExec(int argc, char** argv)
{
    // this is the first msg exchange for the proc id
    (void) argc; (void)argv;
//    iz_server("/tmp/1.1.1.1", 0, 0);

    struct sysmsg m; // message to write to
    if (argc < 2) {
        fprintf(stderr, "Error usage: use progname <s> or <r>\n");
        exit(1);
    } else {
        // S-send
        if(*argv[1]=='s'|| *argv[1]=='S') {
            printf("Sending a message...\n");
            char* rfifo = iz_get_my_rwfifo();
            if(iz_send_sys_msg(rfifo, &m)==0) {
                // i`ve sent a message, when received I`ll get a ready fifo
                // to write to so this can be acceptable loop
                printf("OK, I`ve sent a message to the reader...\n");
                // when I send I am opening the fifo
                mkfifo(m.mtext, 0666);
                int fdw = open(m.mtext, O_RDWR|O_NONBLOCK);
                while(1) {
                    struct msg m1;
                    iz_msg_generate("hello IPC world", &m1);
                    if(write(fdw, &m1, sizeof(m1)) < 0) {
                        perror("write error!");
                        exit(1);
                    }
                    sleep(1);
                }
            }
        }

        /* now if there is a message in the queue it must be the
         * message to the readable fifo
         * */
        // R-receive
        if (*argv[1]=='r'|| *argv[1]=='R') {
            printf("Receiving a message...\n");
            if(iz_get_sys_msg(&m)==0) {
                struct msg  m1;
                iz_msg_generate(m.mtext, &m1);
                mkfifo(m.mtext, 0666);
                int fdr = open(m.mtext, O_RDWR|O_NONBLOCK);
                if(fdr < 0) {
                    perror("iz_open_read");
                    exit(1);
                } /* else */
                printf("OK, got and opened a fifo!\n");
                // start connection and listening to new data ...
                char rbuff[sizeof(struct msg)]={0};
                while(1) {
                    if (read(fdr, rbuff, sizeof(struct msg)) > 0) {
                        printf("Read...\n");
                        struct msg* p = (struct msg*) rbuff;
                        printf("OK, I got a message form the writer!\n");
                        printf("The message:\n"
                               "[msg:%s][rf:%s][wf:%s]"
                               "[pid:%d][ret:%d]", p->message,
                               p->fifo_files.fifo_read,
                               p->fifo_files.fifo_write,
                               p->pid,
                               p->result);
                    }
                }
            }
        }
    }
    // test the simple functions first
    // 1. we`ve succeeded to send and receive messages from different progs
    // now we must open the FIFOs to R/W to


#if 0
    struct msg* pm = msg_generate("hello IPC world!!!");


    if(fdr < 0 || fdw < 0) {
        exit(1);
    }
    // the first message to be send is the name of the sender aka my IP
    //struct msg* precv = msg_generate(pm->fifo_files.fifo_read);
    //send_msg(fdr, precv);
    // enter the test loop - self talking ...
    for(;;) {
        // send messages and read them back...
        char rbuff[sizeof(struct msg)]= {0};
        char wbuff[sizeof(struct msg)] = {0};

        if (read(fdr, rbuff, sizeof(struct msg)) > 0) {
            printf("Read...\n");
            struct msg* p = (struct msg*) rbuff;
            char pmessage[512]={0};
            sprintf(pmessage, "[message: %s][came from %d][ret: %d]\n",
                   p->message, p->pid, p->result);
            puts(pmessage);

        }
        char m[256]={0};
        if(fgets(m, 256, stdin) != -1) {

            struct msg* pm = msg_generate(m);
            memcpy(wbuff, pm, sizeof(struct msg));
            if (write(fdr, wbuff, sizeof(struct msg)) == -1) {
                perror("Could not write to fifo...");
            }
        } else {
            break;
        }
    }

    struct msg* pm2 = msg_generate("bye");
    unlink(pm2->fifo_files.fifo_read);
    unlink(pm2->fifo_files.fifo_write);
    return 0; // or err code
#endif
    return 0;

}
