TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Encriptacion.cpp \
        ManipulacionArchivo.cpp \
        Menu.cpp \
        OperacionUsuario.cpp \
        Validaciones.cpp \
        main.cpp

HEADERS += \
    Encriptacion.h \
    ManipulacionArchivos.h \
    Menu.h \
    OperacionesUsuario.h \
    Validaciones.h
