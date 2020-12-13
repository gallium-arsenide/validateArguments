TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        BetterValidateArguments.cpp \
        SimpleValidateArguments.cpp \
        ValidateArguments.cpp \
        main.cpp

HEADERS += \
    BetterValidateArguments.h \
    SimpleValidateArguments.h \
    ValidateArguments.h
