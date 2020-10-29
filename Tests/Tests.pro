APPLICATION_VERSION="1.0"
VERSION = $$APPLICATION_VERSION
PROJECT_PATH="\"$$PWD\""
BUILD_PATH="\"$$OUT_PWD\""
DEFINES += PROJECT_PATH
DEFINES += BUILD_PATH

QT += testlib
QT -= gui

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_test.cpp \
    ../6ifratorDe6ifrator/cesar_encryptor.cpp \
    ../6ifratorDe6ifrator/cesar_decryptor.cpp
