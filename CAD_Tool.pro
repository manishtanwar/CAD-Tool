#-------------------------------------------------
#
# Project created by QtCreator 2018-04-05T22:24:09
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CAD_Tool
TEMPLATE = app
CONFIG += c++11

DESTDIR = bin
OBJECTS_DIR = build
MOC_DIR = build

HEADERS  += \
    include/2d_to_3d.h \
    include/3d_to_2d.h \
    include/body_loop.h \
    include/faceloop_generator.h \
    include/form.h \
    include/Full_plane.h \
    include/general_methods.h \
    include/mainwindow.h \
    include/object_2d.h \
    include/Object_3d.h \
    include/planar_graph_generator.h \
    include/structs.h

SOURCES += \
    src/2d_to_3d.cpp \
    src/3d_to_2d.cpp \
    src/body_loop.cpp \
    src/faceloop_generator.cpp \
    src/form.cpp \
    src/Full_plane.cpp \
    src/general_methods.cpp \
    src/main.cpp \
    src/mainwindow.cpp \
    src/object_2d.cpp \
    src/Object_3d.cpp \
    src/planar_graph_generator.cpp \
    src/structs.cpp

FORMS += \
    include/mainwindow.ui \
    include/form.ui

