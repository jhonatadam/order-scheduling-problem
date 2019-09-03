TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    instance.cpp \
    localsearch.cpp \
    optimizationmethod.cpp \
    solution.cpp

HEADERS += \
    instance.h \
    localsearch.h \
    optimizationmethod.h \
    solution.h
