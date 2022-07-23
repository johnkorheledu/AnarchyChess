QT       += core gui svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bishop.cpp \
    blackqueendialog.cpp \
    king.cpp \
    knight.cpp \
    main.cpp \
    mainwindow.cpp \
    move_option.cpp \
    pawn.cpp \
    piece.cpp \
    queen.cpp \
    rook.cpp \
    tile.cpp \
    whitequeendialog.cpp

HEADERS += \
    bishop.h \
    blackqueendialog.h \
    king.h \
    knight.h \
    mainwindow.h \
    move_option.h \
    pawn.h \
    piece.h \
    queen.h \
    rook.h \
    tile.h \
    whitequeendialog.h

FORMS += \
    blackqueendialog.ui \
    mainwindow.ui \
    whitequeendialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc
