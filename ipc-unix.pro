TEMPLATE = subdirs

#info from: http://www.tutorialspoint.com/perl/perl_socket_programming.htm

SUBDIRS += \
    bridge \
    defs \
    bway-fifo \
    receiver \
    sender \
    unix-socket-test


DESTDIR = ipc


