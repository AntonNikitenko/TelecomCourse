TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c

DISTFILES += \
    ../build-e-shop-Desktop_Qt_5_5_0_GCC_32bit-Debug/amount.txt \
    ../build-e-shop-Desktop_Qt_5_5_0_GCC_32bit-Debug/id.txt \
    ../build-e-shop-Desktop_Qt_5_5_0_GCC_32bit-Debug/names.txt \
    ../build-e-shop-Desktop_Qt_5_5_0_GCC_32bit-Debug/prices.txt

HEADERS += \
    product.h \
    admcommands.h \
    usrcommands.h \
    gencommands.h \
    dialogs.h \
    server.h

QMAKE_CXXFLAGS += -std=c++0x -pthread 
LIBS += -pthread
