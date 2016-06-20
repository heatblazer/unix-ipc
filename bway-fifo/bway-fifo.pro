TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    izfifo.c \
    izlockfile.c \
    izipcmsg.c \
    main.c \
    defs.c \
    izsocket.c

HEADERS += \
    izfifo.h \
    defs.h \
    izlockfile.h \
    izipcmsg.h \
    izsocket.h

