TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        BinarioChar.cpp \
        Encriptacion.cpp \
        ManipulacionDeArchivos.cpp \
        funcionesAuxiliares.cpp \
        main.cpp \
        menu.cpp \

HEADERS += \
    Sistema.h \
    menu.h
