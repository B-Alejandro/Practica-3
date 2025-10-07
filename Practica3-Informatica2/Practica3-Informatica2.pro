TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        Encriptacion.cpp \
        ManipulacionDeArchivos.cpp \
    Menu.cpp \
    OperacionesUsuario.cpp \
    UtilidadesCadena.cpp \
        main.cpp \
    validaciones.cpp

HEADERS += \
    Encriptacion.h \
    Encriptacion.h \
    ManipulacionDeArchivos.h \
    Menu.h \
    OperacionesUsuario.h \
    Sistema.h \
    UtilidadesCadena.h \
    Validaciones.h
