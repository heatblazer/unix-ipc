TEMPLATE = subdirs

#info from: http://www.tutorialspoint.com/perl/perl_socket_programming.htm

SUBDIRS += \
    sender \
    receiver \
    bridge \
    defs \
    msg-send \
    msg-recv


DESTDIR = ipc


